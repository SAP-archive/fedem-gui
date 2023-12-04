// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FapCGeoFile.H"
#include "vpmDB/FmPart.H"
#include "vpmDB/FmBeam.H"
#include "vpmDB/FmDB.H"

#ifdef USE_INVENTOR
#include "FFdCadModel/FdCadHandler.H"
#include "FFdCadModel/FdCadSolid.H"
#include "FFdCadModel/FdCadFace.H"
#include "vpmDisplay/FdBeam.H"
#include "vpmDisplay/FdFEModel.H"
#include "vpmDisplay/FdFEModelKit.H"
#include "vpmDisplay/FdDB.H"
#endif

#include <fstream>
#include <vector>
#include <array>

#ifdef USE_INVENTOR
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodekits/SoBaseKit.h>
#endif

#ifdef STB_IMAGE
#define STBI_ONLY_JPEG
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)
#include "stb_image.h"
#endif

#ifdef FT_HAS_VRML_READER
#define VRML_READER_IMPLEMENTATION
#include "VTFXExporter/VRMLReader.H"
#else
struct VRMLVec2 { float x, y; };
struct VRMLVec3 { float x, y, z; };
#endif


struct GeoPart
{
  bool Quads = false;
  int compId = 0;
  int numVertices = 0;
  int numIndices = 0;
  int numTextureCoords = 0;
  float alpha = 0.0f;
  std::array<float,3> color = { 0.0f, 0.0f, 0.0f };
  std::vector<VRMLVec3> vertices;
  std::vector<VRMLVec2> textureCoordinates;
  std::vector<int> indices;
  unsigned char* texture = NULL;
  int textureIndex = -1;
  int textureWidth = 0;
  int textureHeight = 0;

  void addVertex(const FaVec3& v) { vertices.push_back({(float)v.x(),(float)v.y(),(float)v.z()}); }
};


void getBeamGeomtries(std::vector<GeoPart>&);
void getCADGeometries(std::vector<GeoPart>&);


bool FapCGeo::writeGeometry(const std::string& fileName)
{
  std::vector<GeoPart> geoParts;

  getBeamGeomtries(geoParts);
  getCADGeometries(geoParts);

  int Magic = 2072003; //12072001;
  int PartCount = geoParts.size();
  int TextureCount = 0;
  for (const GeoPart& part : geoParts)
    if (part.textureIndex != -1)
      TextureCount++;

  // Write file
  std::ofstream cgeoFile(fileName, std::ios::out | std::ios::binary);
  cgeoFile.write((char*)&Magic, sizeof(int));
  cgeoFile.write((char*)&TextureCount, sizeof(int));
  cgeoFile.write((char*)&PartCount, sizeof(int));

  //Textures
  for (const GeoPart& part : geoParts)
    if (part.texture)
    {
      cgeoFile.write((char*)&part.textureIndex, sizeof(int));
      cgeoFile.write((char*)&part.textureWidth, sizeof(int));
      cgeoFile.write((char*)&part.textureHeight, sizeof(int));
      int wrapMode = 1;
      cgeoFile.write((char*)&wrapMode, sizeof(int));
      int minFilter = 2;
      cgeoFile.write((char*)&minFilter, sizeof(int));
      int magFilter = 2;
      cgeoFile.write((char*)&magFilter, sizeof(int));
      //Write pixel data
      for (int j = 0; j < part.textureWidth*part.textureHeight; j++)
      {
        unsigned char r = part.texture[j * 3];
        unsigned char g = part.texture[j * 3 + 1];
        unsigned char b = part.texture[j * 3 + 2];
        unsigned char a = 255;
        int intPixel = (int)(r) << 24 | (int)(g) << 16 | (int)(b) << 8 | a;
        cgeoFile.write((char*)&intPixel, sizeof(int));
      }
    }

  for (const GeoPart& part : geoParts)
  {
    cgeoFile.write((char*)&part.compId, sizeof(int));

    int intColor = ((int)(part.color[0] * 255.0f) << 24 |
                    (int)(part.color[1] * 255.0f) << 16 |
                    (int)(part.color[2] * 255.0f) << 8 |
                    (int)(part.alpha * 255.0f));
    cgeoFile.write((char*)&intColor, sizeof(int));

    int numVertices = part.numVertices;
    cgeoFile.write((char*)&numVertices, sizeof(int));
    int HasNormals = 0;
    cgeoFile.write((char*)&HasNormals, sizeof(int));
    int TextureIndex = part.textureIndex;
    cgeoFile.write((char*)&TextureIndex, sizeof(int));
    int NumPrimitives = part.Quads ? part.numIndices / 4 : part.numIndices / 3;
    cgeoFile.write((char*)&NumPrimitives, sizeof(int));
    int VerticesPerPrimitive = part.Quads ? 4 : 3;
    cgeoFile.write((char*)&VerticesPerPrimitive, sizeof(int));

    //vertices
    for (int j = 0; j < part.numVertices; j++)
    {
      cgeoFile.write((char*)&part.vertices[j].x, sizeof(float));
      cgeoFile.write((char*)&part.vertices[j].y, sizeof(float));
      cgeoFile.write((char*)&part.vertices[j].z, sizeof(float));
    }

    //TextureCoordinates
    if (part.texture && part.numTextureCoords == part.numVertices)
      for (int j = 0; j < part.numTextureCoords; j++)
      {
        cgeoFile.write((char*)&part.textureCoordinates[j].x, sizeof(float));
        cgeoFile.write((char*)&part.textureCoordinates[j].y, sizeof(float));
      }

    //indices
    for (int j = 0; j < part.numIndices; j++)
      cgeoFile.write((char*)&part.indices[j], sizeof(int));

    delete part.texture;
  }

  cgeoFile.close();

  return true;
}


void getCADGeometries(std::vector<GeoPart>& geoParts)
{
#ifdef USE_INVENTOR
  std::vector<FmPart*> fmParts;
  FmDB::getAllParts(fmParts);
#ifdef STB_IMAGE
  int textureCounter = 0;
#endif

  for (FmPart* thePart : fmParts)
  {
    double scaleF = 1.0;
    thePart->visDataFileUnitConverter.getValue().convert(scaleF, "LENGTH");

    switch (FdDB::getCadFileType(thePart->visDataFile.getValue()))
    {
    case FdDB::FD_VRML_FILE:
    {
#ifdef FT_HAS_VRML_READER
      FaVec3 partTransl = thePart->getGlobalCS().translation();
      FaMat33 partRotMat = thePart->getGlobalCS().direction();

      std::ifstream input(thePart->visDataFile.getValue());
      VRMLModel model = VRML_ReadModel(input);

      bool ShapesToIndividualParts = true;
      for (const VRMLTransform& transform : model.transforms)
        for (const VRMLShape& shape : transform.shapes)
          if (shape.appearance.texture != "")
            ShapesToIndividualParts = true;

      if (ShapesToIndividualParts)
      {
        for (const VRMLTransform& transform : model.transforms)
        {
          FaVec3 translation(transform.translation.x, transform.translation.y, transform.translation.z);

          float u = transform.rotationVec.x;
          float v = transform.rotationVec.y;
          float w = transform.rotationVec.z;
          float angle = transform.rotation;

          float u2 = u * u;
          float v2 = v * v;
          float w2 = w * w;
          float L  = u2 + v2 + w2;

          FaMat33 vrmlRotMat;

          vrmlRotMat[0][0] = (u2 + (v2 + w2) * cos(angle)) / L;
          vrmlRotMat[0][1] = (u * v * (1 - cos(angle)) - w * sqrt(L) * sin(angle)) / L;
          vrmlRotMat[0][2] = (u * w * (1 - cos(angle)) + v * sqrt(L) * sin(angle)) / L;

          vrmlRotMat[1][0] = (u * v * (1 - cos(angle)) + w * sqrt(L) * sin(angle)) / L;
          vrmlRotMat[1][1] = (v2 + (u2 + w2) * cos(angle)) / L;
          vrmlRotMat[1][2] = (v * w * (1 - cos(angle)) - u * sqrt(L) * sin(angle)) / L;

          vrmlRotMat[2][0] = (u * w * (1 - cos(angle)) - v * sqrt(L) * sin(angle)) / L;
          vrmlRotMat[2][1] = (v * w * (1 - cos(angle)) + u * sqrt(L) * sin(angle)) / L;
          vrmlRotMat[2][2] = (w2 + (u2 + v2) * cos(angle)) / L;

          for (const VRMLShape& shape : transform.shapes)
          {
            GeoPart geoPart;
            geoPart.color = thePart->getRGBColor();
            geoPart.alpha = 1.0 - thePart->getTransparency();
            geoPart.compId = thePart->getTag() != "" ? std::stoi(thePart->getTag()) : thePart->getBaseID();

            geoPart.Quads = shape.faceSet.Quads;
            geoPart.numVertices = shape.faceSet.coordinates->size();
            geoPart.numIndices = shape.faceSet.elements->size();
            geoPart.numTextureCoords = shape.faceSet.textureCoordinates->size();

            //Vertices
            geoPart.vertices.reserve(geoPart.numVertices);
            for (const VRMLVec3& coords : *shape.faceSet.coordinates)
            {
              FaVec3 point(coords.x*scaleF, coords.y*scaleF, coords.z*scaleF);
              geoPart.addVertex(vrmlRotMat * point + translation);
            }

            //Textures
            geoPart.textureCoordinates = *shape.faceSet.textureCoordinates;

            //indices
            geoPart.indices = *shape.faceSet.elements;

            //read textures
            if (!shape.appearance.texture.empty())
            {
#if defined(STB_IMAGE)
              int n;
              geoPart.texture = stbi_load(shape.appearance.texture.c_str(),
                                          &geoPart.textureHeight,
                                          &geoPart.textureWidth, &n, 3);
              geoPart.textureIndex = textureCounter++;
#endif
            }

            geoPart.color = { shape.appearance.material.diffuseColor.x, shape.appearance.material.diffuseColor.y, shape.appearance.material.diffuseColor.z };

            geoParts.push_back(geoPart);
          }
        }
      }
      else
      {
        GeoPart geoPart;
        geoPart.color = thePart->getRGBColor();
        geoPart.alpha = 1.0 - thePart->getTransparency();
        geoPart.compId = thePart->getTag() != "" ? std::stoi(thePart->getTag()) : thePart->getBaseID();

        //Count total vertices and primitives
        for (const VRMLTransform& transform : model.transforms)
          for (const VRMLShape& shape : transform.shapes)
          {
            geoPart.Quads = shape.faceSet.Quads;
            geoPart.color = { shape.appearance.material.diffuseColor.x, shape.appearance.material.diffuseColor.y, shape.appearance.material.diffuseColor.z };

            geoPart.numVertices += shape.faceSet.coordinates->size();
            geoPart.numIndices += shape.faceSet.elements->size();
          }

        //Vertices
        geoPart.vertices.reserve(geoPart.numVertices);
        for (const VRMLTransform& transform : model.transforms)
        {
          double scaleTransformX = scaleF * transform.scale.x;
          double scaleTransformY = scaleF * transform.scale.y;
          double scaleTransformZ = scaleF * transform.scale.z;

          FaVec3 translation(transform.translation.x*scaleTransformX,
                             transform.translation.y*scaleTransformY,
                             transform.translation.z*scaleTransformZ);

          float u = transform.rotationVec.x;
          float v = transform.rotationVec.y;
          float w = transform.rotationVec.z;
          float angle = transform.rotation;

          float L = (u*u + v * v + w * w);
          float u2 = u * u;
          float v2 = v * v;
          float w2 = w * w;

          FaMat33 vrmlRotMat;

          vrmlRotMat[0][0] = (u2 + (v2 + w2) * cos(angle)) / L;
          vrmlRotMat[0][1] = (u * v * (1 - cos(angle)) - w * sqrt(L) * sin(angle)) / L;
          vrmlRotMat[0][2] = (u * w * (1 - cos(angle)) + v * sqrt(L) * sin(angle)) / L;

          vrmlRotMat[1][0] = (u * v * (1 - cos(angle)) + w * sqrt(L) * sin(angle)) / L;
          vrmlRotMat[1][1] = (v2 + (u2 + w2) * cos(angle)) / L;
          vrmlRotMat[1][2] = (v * w * (1 - cos(angle)) - u * sqrt(L) * sin(angle)) / L;

          vrmlRotMat[2][0] = (u * w * (1 - cos(angle)) - v * sqrt(L) * sin(angle)) / L;
          vrmlRotMat[2][1] = (v * w * (1 - cos(angle)) + u * sqrt(L) * sin(angle)) / L;
          vrmlRotMat[2][2] = (w2 + (u2 + v2) * cos(angle)) / L;

          for (const VRMLShape& shape : transform.shapes)
            for (const VRMLVec3& coords : *shape.faceSet.coordinates)
            {
              FaVec3 point(coords.x*scaleTransformX, coords.y*scaleTransformY, coords.z*scaleTransformZ);
              geoPart.addVertex(partRotMat * vrmlRotMat*point + partTransl + translation);
            }
        }

        //indices
        geoPart.indices.reserve(geoPart.numIndices);
        int vertexOffset = 0;
        for (const VRMLTransform& transform : model.transforms)
          for (const VRMLShape& shape : transform.shapes)
          {
            for (int k : *shape.faceSet.elements)
              geoPart.indices.push_back(k + vertexOffset);
            vertexOffset += shape.faceSet.coordinates->size();
          }

        geoParts.push_back(geoPart);
      }

      VRML_ClearModel(&model);
#else
      std::cerr <<"  ** FapCGeo::writeGeometry: VRML-models currently unsupported."
                <<"\n     "<< thePart->getIdString(true) <<" ignored."<< std::endl;
#endif
      break;
    }
    case FdDB::FD_OBJ_FILE:
    {
      GeoPart geoPart;
      geoPart.color = thePart->getRGBColor();
      geoPart.alpha = 1.0 - thePart->getTransparency();
      geoPart.compId = !thePart->getTag().empty() ? std::stoi(thePart->getTag()) : thePart->getBaseID();

      FdCadPart* cadPart = ((FdLink*)thePart->getFdPointer())->getCadHandler()->getCadPart();
      if (cadPart->size() > 0)
      {
        FdCadSolid* body = cadPart->getSolid(0).first;
        int numNodes = body ? body->getNumChildren() : 0;
        SoCoordinate3* coords = NULL;

        for (int i = 0; !coords && i < numNodes; i++)
          if (body->getChild(i)->isOfType(SoCoordinate3::getClassTypeId()))
          {
            coords = static_cast<SoCoordinate3*>(body->getChild(i));
            geoPart.numVertices = coords->point.getNum();
          }

        FaVec3 transl = thePart->getGlobalCS().translation();
        FaMat33 rotMat = thePart->getGlobalCS().direction();

        //Vertices
        geoPart.vertices.reserve(geoPart.numVertices);
        for (int j = 0; j < geoPart.numVertices; ++j)
        {
          FaVec3 point(coords->point[j][0], coords->point[j][1], coords->point[j][2]);
          geoPart.addVertex(rotMat * point + transl);
        }

        //indices
        std::vector<int>& indices = geoPart.indices;
        for (int i = 0; i < numNodes; i++)
          if (body->getChild(i)->isOfType(FdCadFace::getClassTypeId()))
          {
            FdCadFace* face = static_cast<FdCadFace*>(body->getChild(i));
            int faceNodes[3];
            int nodeCounter = 0;
            for (int i = 0; i < face->coordIndex.getNum(); i++)
              if (nodeCounter < 3)
                faceNodes[nodeCounter++] = face->coordIndex[i];
              else
              {
                indices.push_back(faceNodes[0]);
                indices.push_back(faceNodes[1]);
                indices.push_back(faceNodes[2]);

                nodeCounter = 0;
                geoPart.numIndices += 3;
              }
          }

        geoParts.push_back(geoPart);
      }
      break;
    }
    default:
      break;
    }
  }
#else
  geoParts.clear();
#endif
}


void getBeamGeomtries(std::vector<GeoPart>& geoParts)
{
#ifdef USE_INVENTOR
  std::vector<FmBeam*> beams;
  FmDB::getAllBeams(beams);

  for (FmBeam* theBeam : beams)
  {
    GeoPart geoPart;
    geoPart.color = theBeam->getRGBColor();
    geoPart.alpha = 1.0 - theBeam->getTransparency();
    geoPart.compId = !theBeam->getTag().empty() ? std::stoi(theBeam->getTag()) : theBeam->getBaseID();

    FdCadPart* cadPart = ((FdBeam*)theBeam->getFdPointer())->getCadHandler()->getCadPart();
    if (cadPart->size() > 0)
    {
      FdCadSolid* body = cadPart->getSolid(0).first;
      int numNodes = body ? body->getNumChildren() : 0;
      SoCoordinate3* coords = NULL;

      for (int i = 0; !coords && i < numNodes; i++)
        if (body->getChild(i)->isOfType(SoCoordinate3::getClassTypeId()))
        {
          coords = static_cast<SoCoordinate3*>(body->getChild(i));
          geoPart.numVertices = coords->point.getNum();
        }

      FaVec3 transl = theBeam->getGlobalCS().translation();
      FaMat33 rotMat = theBeam->getGlobalOrientation();

      //Vertices
      geoPart.vertices.reserve(geoPart.numVertices);
      for (int j = 0; j < geoPart.numVertices; ++j)
      {
        FaVec3 point(coords->point[j][0], coords->point[j][1], coords->point[j][2]);
        geoPart.addVertex(rotMat * point + transl);
      }

      //indices
      std::vector<int>& indices = geoPart.indices;
      for (int i = 0; i < numNodes; i++)
        if (body->getChild(i)->isOfType(FdCadFace::getClassTypeId()))
        {
          FdCadFace* face = static_cast<FdCadFace*>(body->getChild(i));
          int faceNodes[4];
          int nodeCounter = 0;
          for (int i = 0; i < face->coordIndex.getNum(); i++)
            if (nodeCounter < 4)
              faceNodes[nodeCounter++] = face->coordIndex[i];
            else
            {
              indices.push_back(faceNodes[0]);
              indices.push_back(faceNodes[1]);
              indices.push_back(faceNodes[3]);
              indices.push_back(faceNodes[1]);
              indices.push_back(faceNodes[2]);
              indices.push_back(faceNodes[3]);

              nodeCounter = 0;
              geoPart.numIndices += 6;
            }
        }

      geoParts.push_back(geoPart);
    }
  }
#else
  geoParts.clear();
#endif
}
