// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FapVTFFile.H"
#include "vpmDB/FmPart.H"
#include "FFlLib/FFlIOAdaptors/FFlVTFWriter.H"
#include "FFaLib/FFaString/FFaStringExt.H"
#include "FFaLib/FFaDefinitions/FFaMsg.H"

#ifdef FT_HAS_VTF
#include "VTFAPI.h"
#include "VTOAPIPropertyIDs.h"


bool FapVTFFile::open(const std::string& fileName, VTFFileType fileFormat)
#else
bool FapVTFFile::open(const std::string&, VTFFileType fileFormat)
#endif
{
  iBlock = 0;
  iStep = 0;
  myInfo = 0;
  myTrans = 0;
  myDispl = 0;
  myScalar = 0;
  myFormat = fileFormat;
#ifdef FT_HAS_VTF
  myFile = new VTFAFile();

  // Enable debug info to stderr/console
  myFile->SetOutputDebugError(1);

  bool bExpressFile = myFormat == VTF_EXPRESS;
  bool bBinaryFile  = myFormat != VTF_ASCII;

  if (bExpressFile)
  {
    // Create the Express VTF file
    // Available only in the commercial version of the VTF Express API
    int iVendorCode = 884625072; // FEDEM vendor code (keep this confidential)

    // Specify to use compression
    int iResult = myFile->CreateExpressFile(fileName.c_str(),iVendorCode,1);
    if (iResult == VTFAERR_CANNOT_CREATE_EXPRESS_FILE)
    {
      // Cannot create Express file, must use the GLview VTF writer library
      bExpressFile = false;
      myFormat = VTF_BINARY;
      ListUI <<"===> Export to Express VTF file is not available.\n"
	     <<"     Switching to the open VTF format instead.\n";
    }
    else if (VTFA_SUCCESS(iResult))
      return true;
  }

  // Create the open VTF file, specifying binary file output
  // These formats are always available
  if (!bExpressFile)
    if (VTFA_SUCCESS(myFile->CreateVTFFile(fileName.c_str(),bBinaryFile)))
      return true;

  delete myFile;
  ListUI <<" *** Error creating VTF file "<< fileName <<"\n";
#else
  ListUI <<" *** VTF output is not available in this version\n";
#endif
  myFile = 0;
  return false;
}


bool FapVTFFile::close()
{
  bool retVal = true;
#ifdef FT_HAS_VTF
  if (myTrans)
  {
    if (myFile)
      if (VTFA_FAILURE(myFile->WriteBlock(myTrans)))
      {
	ListUI <<" *** Error writing transformation block to VTF file\n";
	retVal = false;
      }

    delete myTrans;
  }

  if (myDispl)
  {
    if (myFile)
      if (VTFA_FAILURE(myFile->WriteBlock(myDispl)))
      {
	ListUI <<" *** Error writing displacement block to VTF file\n";
	retVal = false;
      }

    delete myDispl;
  }

  if (myScalar)
  {
    if (myFile)
      if (VTFA_FAILURE(myFile->WriteBlock(myScalar)))
      {
	ListUI <<" *** Error writing scalar block to VTF file\n";
	retVal = false;
      }

    delete myScalar;
  }

  if (myInfo)
  {
    if (myFile)
      if (VTFA_FAILURE(myFile->WriteBlock(myInfo)))
      {
	ListUI <<" *** Error writing state information to VTF file\n";
	retVal = false;
      }

    delete myInfo;
  }

  if (myFile)
  {
    if (VTFA_FAILURE(myFile->CloseFile()))
    {
      ListUI <<" *** Error closing VTF file\n";
      retVal = false;
    }
    delete myFile;
  }
#endif
  myTrans = 0;
  myDispl = 0;
  myScalar = 0;
  myInfo = 0;
  myFile = 0;
  return retVal;
}


#ifdef FT_HAS_VTF
bool FapVTFFile::writeGeometry(const std::vector<FmLink*>& links,
			       bool writeFEdata, bool convTo1stOrder)
#else
bool FapVTFFile::writeGeometry(const std::vector<FmLink*>&, bool, bool)
#endif
{
  bool retVal = false;
#ifdef FT_HAS_VTF
  if (!myFile) return retVal;

  size_t i, nParts = links.size();

  // Fetch part ID numbers from the links
  myElmOrder.clear();
  myParts.clear();
  myParts.reserve(nParts);
  for (i = 0; i < nParts; i++)
    myParts.push_back(links[i]->getBaseID());

  // Write VTF geometry definition, assuming one element block for each link
  VTFAGeometryBlock geoBlock;
  if (VTFA_FAILURE(geoBlock.SetGeometryElementBlocks(&myParts.front(),nParts)))
    ListUI <<" *** Error defining VTF geometry block\n";
  else if (VTFA_FAILURE(myFile->WriteBlock(&geoBlock)))
    ListUI <<" *** Error writing VTF geometry block\n";
  else
    retVal = true;

  if (writeFEdata && retVal)
  {
    // Write FE data for each link
    FFaMsg::enableSubSteps(nParts);
    for (i = 0; i < nParts && retVal; i++)
    {
      FFaMsg::setSubStep(1+i);
      if (!links[i]->isOfType(FmPart::getClassTypeID()))
	retVal = links[i]->writeToVTF(*myFile);
      else if (convTo1stOrder)
	retVal = links[i]->writeToVTF(*myFile,&myElmOrder[myParts[i]],&my1stOrdNodes[myParts[i]]);
      else
	retVal = links[i]->writeToVTF(*myFile,&myElmOrder[myParts[i]]);
      if (!retVal)
	ListUI <<" *** Error writing FE data for "<< links[i]->getIdString()
	       <<" to VTF file\n";
    }
    FFaMsg::disableSubSteps();
  }
#endif

  return retVal;
}


#ifdef FT_HAS_VTF
bool FapVTFFile::writeProperties(const FapExpProp& prop)
#else
bool FapVTFFile::writeProperties(const FapExpProp&)
#endif
{
  if (myFormat != VTF_EXPRESS) return true; // Needed for express files only

  bool retVal = false;
#ifdef FT_HAS_VTF
  if (!myFile) return retVal;

  VTFAPropertiesBlockSimple frameProp(VT_CT_FRAME_GENERATOR_SETTINGS);
  frameProp.AddInt(VT_PI_FG_STATE_IDS,1);
  frameProp.AddInt(VT_PI_FG_TRANSFORMATION_RESULT_IDS,1);

  if (prop.deformation || prop.modeShape)
    frameProp.AddInt(VT_PI_FG_DISPLACEMENT_RESULT_ID,1);

  if (prop.modeShape)
    frameProp.AddInt(VT_PI_FG_NUM_MODE_SHAPE_FRAMES,20);

  if (prop.fringe)
    frameProp.AddResultID(VT_PR_FG_FRINGE_RESULT_ID,1,-1);

  if (VTFA_FAILURE(myFile->WriteBlock(&frameProp)))
    ListUI <<" *** Error writing frame generator settings to VTF file\n";
  else
    retVal = true;

  if (prop.fringe && prop.range.first < prop.range.second && retVal)
  {
    VTFAPropertiesBlockSimple scalarProp(VT_CT_SCALAR_SETTINGS);
    scalarProp.SetResultID(1,-1);
    scalarProp.AddBool(VT_PB_SA_AUTO_FULL_RANGE,0);
    if (VTFA_FAILURE(myFile->WriteBlock(&scalarProp)))
    {
      ListUI <<" *** Error writing scalar settings to VTF file\n";
      retVal = false;
    }

    VTFAPropertiesBlockSimple legendProp(VT_CT_COLOR_LEGEND_SETTINGS);
    legendProp.SetLegendID(0,1,-1);
    legendProp.AddFloat(VT_PF_CL_RANGE_MIN,prop.range.first);
    legendProp.AddFloat(VT_PF_CL_RANGE_MAX,prop.range.second);
    if (VTFA_FAILURE(myFile->WriteBlock(&legendProp)))
    {
      ListUI <<" *** Error writing color legend settings to VTF file\n";
      retVal = false;
    }
  }

  if (prop.deformation || prop.modeShape || prop.fringe)
    for (size_t i = 0; i < myParts.size() && retVal; i++)
    {
      VTFAPropertiesBlockSimple partAttr(VT_CT_PART_ATTRIBUTES);
      partAttr.SetPartID(myParts[i]);

      if (prop.deformation || prop.modeShape)
	partAttr.AddBool(VT_PB_PA_DISPLACEMENTS,1);

      if (prop.fringe)
	partAttr.AddBool(VT_PB_PA_DRAW_FRINGE_COLORS,1);

      if (VTFA_FAILURE(myFile->WriteBlock(&partAttr)))
      {
	ListUI <<" *** Error writing part attributes to VTF file\n";
	retVal = false;
      }
    }
#endif

  return retVal;
}


#ifdef FT_HAS_VTF
bool FapVTFFile::writeStep(int stepNo, double time)
#else
bool FapVTFFile::writeStep(int, double)
#endif
{
  bool retVal = false;
#ifdef FT_HAS_VTF
  if (!myInfo) myInfo = new VTFAStateInfoBlock();

  FFaNumStr timeName("Time: %g",time);
  FFaNumStr stepName(" (Step: %d)",stepNo);
  if (VTFA_FAILURE(myInfo->SetStepData(++iStep,(timeName+stepName).c_str(),time,0)))
    ListUI <<" *** Error defining state info block\n";
  else
    retVal = true;
#endif

  return retVal;
}


#ifdef FT_HAS_VTF
bool FapVTFFile::writeTransformations(const std::map<int,FaMat34>& mxs)
#else
bool FapVTFFile::writeTransformations(const std::map<int,FaMat34>&)
#endif
{
  bool retVal = false;
#ifdef FT_HAS_VTF
  if (!myFile) return retVal;

  if (!myTrans)
  {
    myTrans = new VTFATransformationBlock(1);
    myTrans->SetName("Rigid Body Motion");
    myTrans->SetResultID(1);
  }

  int i, j, k;
  float fMat[12];
  std::vector<int> mxID;
  mxID.reserve(mxs.size());
  std::map<int,FaMat34>::const_iterator xit;
  for (xit = mxs.begin(); xit != mxs.end(); xit++)
  {
    // Cast to float
    for (j = k = 0; j < 4; j++)
      for (i = 0; i < 3; i++, k++)
	fMat[k] = xit->second[j][i];

    mxID.push_back(++iBlock);
    VTFAMatrixResultBlock mxBlock(iBlock);
    if (VTFA_FAILURE(mxBlock.SetMatrix(fMat)))
    {
      ListUI <<" *** Error defining matrix result block\n";
      break;
    }

    mxBlock.SetMapToElementBlockID(xit->first);
    if (VTFA_FAILURE(myFile->WriteBlock(&mxBlock)))
    {
      ListUI <<" *** Error writing matrix result block to VTF file\n";
      break;
    }
  }

  if (VTFA_FAILURE(myTrans->SetResultBlocks(&mxID.front(),mxID.size(),iStep)))
    ListUI <<" *** Error defining transformation block\n";
  else if (xit == mxs.end())
    retVal = true;
#endif

  return retVal;
}


#ifdef FT_HAS_VTF
bool FapVTFFile::writeDeformations(int nodeBlockID, const std::vector<FaVec3>& dis)
#else
bool FapVTFFile::writeDeformations(int, const std::vector<FaVec3>&)
#endif
{
  bool retVal = false;
#ifdef FT_HAS_VTF
  if (!myFile) return retVal;

  if (!myDispl)
  {
    myDispl = new VTFADisplacementBlock(1);
    myDispl->SetName("Deformation");
    myDispl->SetResultID(1);
    myDispl->SetRelativeDisplacementResults(1);
  }

  // Cast to float
  size_t i, j;
  float* fdis = new float[3*dis.size()];
  for (i = j = 0; i < dis.size(); i++)
  {
    fdis[j++] = dis[i].x();
    fdis[j++] = dis[i].y();
    fdis[j++] = dis[i].z();
  }

  // Assume the displacement vector has an ordering
  // which corresponds with the node output order
  VTFAResultBlock dBlock(++iBlock,VTFA_DIM_VECTOR,VTFA_RESMAP_NODE,0);
  dBlock.SetMapToBlockID(nodeBlockID);
  if (VTFA_FAILURE(dBlock.SetResults3D(fdis,dis.size())))
    ListUI <<" *** Error defining displacement result block\n";
  else if (VTFA_FAILURE(myFile->WriteBlock(&dBlock)))
    ListUI <<" *** Error writing displacement result block to VTF file\n";
  else if (VTFA_FAILURE(myDispl->AddResultBlock(iBlock,iStep)))
    ListUI <<" *** Error defining displacement block\n";
  else
    retVal = true;

  delete[] fdis;
#endif

  return retVal;
}


#ifdef FT_HAS_VTF
bool FapVTFFile::writeFringes(int neBlockID, const std::vector<double>& values,
			      const std::string& name, bool elmResults)
#else
bool FapVTFFile::writeFringes(int, const std::vector<double>&,
                              const std::string&, bool)
#endif
{
  bool retVal = false;
#ifdef FT_HAS_VTF
  if (!myFile) return retVal;

  if (!myScalar)
  {
    myScalar = new VTFAScalarBlock(1);
    myScalar->SetName(name.c_str());
    myScalar->SetResultID(1);
  }

  // Cast to float, while reordering if necessary
  int i, nval = values.size();
  int maxElms = myElmOrder[neBlockID].size();
  float* fval = new float[nval];
  if (elmResults)
  {
    if (nval > maxElms)
    {
      ListUI <<" *** Invalid dimension on fringe value array "<< nval
	     <<", expected max "<< maxElms
	     <<" for element block "<< neBlockID <<"\n";
      return retVal;
    }

    for (i = 0; i < nval; i++)
    {
      int iel = abs(myElmOrder[neBlockID][i]);
      if (iel > 0 && iel <= nval)
	fval[i] = values[iel-1];
      else if (iel == 0)
	nval = i; // exit loop, no more elements have been saved to VTF
      else if (iel < 0 || iel > maxElms)
      {
	ListUI <<" *** Internal error: Element index "<< iel
	       <<" is out of range [1,"<< maxElms <<"]\n";
	return retVal;
      }
    }
  }
  else
    // Nodal results are assumed to have an ordering
    // already corresponding with the node output order
    for (i = 0; i < nval; i++)
      fval[i] = values[i];

  int resultMapping = elmResults ? VTFA_RESMAP_ELEMENT : VTFA_RESMAP_NODE;
  VTFAResultBlock sBlock(++iBlock,VTFA_DIM_SCALAR,resultMapping,0);
  sBlock.SetMapToBlockID(neBlockID);
  if (VTFA_FAILURE(sBlock.SetResults1D(fval,nval)))
    ListUI <<" *** Error defining scalar result block\n";
  else if (VTFA_FAILURE(myFile->WriteBlock(&sBlock)))
    ListUI <<" *** Error writing scalar result block to VTF file\n";
  else if (VTFA_FAILURE(myScalar->AddResultBlock(iBlock,iStep)))
    ListUI <<" *** Error defining scalar block\n";
  else
    retVal = true;

  delete[] fval;
#endif

  return retVal;
}


#ifdef FT_HAS_VTF
bool FapVTFFile::writeFringes(int neBlockID,
			      const std::vector< std::vector<double> >& values,
			      const std::string& name, bool convTo1stOrder)
#else
bool FapVTFFile::writeFringes(int, const std::vector< std::vector<double> >&,
                              const std::string&, bool)
#endif
{
  bool retVal = false;
#ifdef FT_HAS_VTF
  if (!myFile) return retVal;

  if (!myScalar)
  {
    myScalar = new VTFAScalarBlock(1);
    myScalar->SetName(name.c_str());
    myScalar->SetResultID(1);
  }

  int i, nel = values.size();
  int maxElm = myElmOrder[neBlockID].size();
  if (nel > maxElm)
  {
    ListUI <<" *** Invalid first dimension on fringe values array "<< nel
	   <<", expected max "<< maxElm
	   <<" for element block "<< neBlockID <<"\n";
    return retVal;
  }

  size_t k, nval = 0;
  for (i = 0; i < nel; i++)
    nval += values[i].size();

  // Cast to float, while reordering
  float* fval = new float[nval];
  for (i = 0, k = 0; i < nel; i++)
  {
    int iel = abs(myElmOrder[neBlockID][i]);
    if (iel > 0 && iel <= nel)
    {
      size_t nen = values[--iel].size();
      int element_type = myElmOrder[neBlockID][i] > 0 ? nen : -nen;
      for (size_t j = 0; j < nen; j++)
	switch (element_type)
	  {
	  case -6: // 6-noded triangular shell
	    fval[k+FFlVTFWriter::T6m[j]-1] = values[iel][j];
	    break;
	  case -8: // 8-noded quadrilateral shell
	    fval[k+FFlVTFWriter::Q8m[j]-1] = values[iel][j];
	    break;
	  case 10: // 10-noded tetrahedron
	    fval[k+FFlVTFWriter::T10m[j]-1] = values[iel][j];
	    break;
	  case 15: // 15-noded pentahedron
	    fval[k+FFlVTFWriter::P15m[j]-1] = values[iel][j];
	    break;
	  case 20: // 20-noden hexahedron
	    fval[k+FFlVTFWriter::H20m[j]-1] = values[iel][j];
	    break;
	  default: // all first-order elements
	    fval[k+j] = values[iel][j];
	  }

      if (convTo1stOrder)
	switch (element_type)
	  {
	  case -6: nen = 3; break;
	  case -8: nen = 4; break;
	  case 10: nen = 4; break;
	  case 15: nen = 6; break;
	  case 20: nen = 8; break;
	  }

      k += nen;
    }
    else if (iel == 0)
    {
      nval = k;
      break; // exit loop, no more elements have been saved to VTF
    }
    else if (iel < 0 || iel > maxElm)
    {
      ListUI <<" *** Internal error: Element index "<< iel
	     <<" is out of range [1,"<< maxElm <<"]\n";
      return retVal;
    }
  }

  VTFAResultBlock sBlock(++iBlock,VTFA_DIM_SCALAR,VTFA_RESMAP_ELEMENT_NODE,0);
  sBlock.SetMapToBlockID(neBlockID);
  if (VTFA_FAILURE(sBlock.SetResults1D(fval,nval)))
    ListUI <<" *** Error defining scalar result block\n";
  else if (VTFA_FAILURE(myFile->WriteBlock(&sBlock)))
    ListUI <<" *** Error writing scalar result block to VTF file\n";
  else if (VTFA_FAILURE(myScalar->AddResultBlock(iBlock,iStep)))
    ListUI <<" *** Error defining scalar block\n";
  else
    retVal = true;

  delete[] fval;
#endif

  return retVal;
}


const std::vector<int>& FapVTFFile::get1stOrderNodes(int partID) const
{
  const std::map<int, std::vector<int> >::const_iterator it = my1stOrdNodes.find(partID);
  if (it != my1stOrdNodes.end()) return it->second;

  static std::vector<int> empty;
  return empty;
}
