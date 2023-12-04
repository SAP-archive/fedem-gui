// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmDisplay/FdExtraGraphics.H"
#include "vpmDisplay/FdDB.H"
#include "vpmDisplay/FdBase.H"
#include "vpmDisplay/FdSymbolDefs.H"
#include "vpmDisplay/FdSymbolKit.H"
#include "vpmDisplay/FdTransformKit.H"
#include "vpmDisplay/FdConverter.H"
#include "FFaLib/FFaAlgebra/FFaMat34.H"
#include "FFaLib/FFaAlgebra/FFa3DLocation.H"
#include "FFaLib/FFaGeometry/FFaCylinderGeometry.H"

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/manips/SoCenterballManip.h>
#include <Inventor/manips/SoTrackballManip.h>
#include <Inventor/manips/SoJackManip.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/nodes/SoPolygonOffset.h>


SoSeparator* FdExtraGraphics::DOFHighlightSep = NULL;
SoGroup*     FdExtraGraphics::cornerBox = NULL;
SoSeparator* FdExtraGraphics::directionSep = NULL;
SoSeparator* FdExtraGraphics::CSSep = NULL;
SoSeparator* FdExtraGraphics::lineSep = NULL;
SoSeparator* FdExtraGraphics::our3DLocationSep = NULL;
SoSeparator* FdExtraGraphics::cylSep = NULL;


void FdExtraGraphics::init()
{
  FdExtraGraphics::cornerBox = FdExtraGraphics::makeCornerBoxGraph();
  FdExtraGraphics::cornerBox->ref();
}


void* FdExtraGraphics::showBBox(SoNode* rootOfObjectToSurround)
{
  if (!rootOfObjectToSurround)
    return NULL;

  SbViewportRegion vp;
  SoGetBoundingBoxAction* bboxGetter = new SoGetBoundingBoxAction(vp);
  bboxGetter->apply(rootOfObjectToSurround);
  SbXfBox3f bbox = bboxGetter->getXfBoundingBox();

  SoNode* n = getCornerBoxGraph(&bbox);
  FdDB::getExtraGraphicsSep()->addChild(n);
  delete bboxGetter;

  return (void*)n;
}

void* FdExtraGraphics::showBBox(const FaVec3& min, const FaVec3& max, const FaMat34& where)
{
  SbXfBox3f ivBbox(FdConverter::toSbVec3f(min), FdConverter::toSbVec3f(max));
  ivBbox.setTransform(FdConverter::toSbMatrix(where));

  SoNode* n = getCornerBoxGraph(&ivBbox);
  FdDB::getExtraGraphicsSep()->addChild(n);

  return (void*)n;
}

void FdExtraGraphics::removeBBox(void* bBoxId)
{
  FdDB::getExtraGraphicsSep()->removeChild((SoNode*)bBoxId);
}


SoSeparator* FdExtraGraphics::getCornerBoxGraph(SbXfBox3f* bbox)
{
  SoSeparator* result = new SoSeparator;
  SoTransform* xf     = new SoTransform;
  SoTransform* scale  = new SoTransform;
  SbVec3f max;
  SbVec3f min;

  xf->setMatrix(bbox->getTransform());
  xf->scaleFactor.setValue(SbVec3f(1,1,1));
  bbox->getBounds(min,max);
  scale->translation.setValue(min);
  scale->scaleFactor.setValue(max - min);

  result->addChild(xf);
  result->addChild(scale);
  result->addChild(FdExtraGraphics::cornerBox);

  return result;
}


void FdExtraGraphics::showDOFVisualizing(int DOF, const FaVec3& center, const FaVec3& direction,
                                         SoNode* rootOfObjToSuround)
{
  if (FdExtraGraphics::DOFHighlightSep)
    FdDB::getExtraGraphicsSep()->removeChild(FdExtraGraphics::DOFHighlightSep);

  FdExtraGraphics::DOFHighlightSep = makeDOFVisualizing(DOF,center,direction,rootOfObjToSuround);
  FdDB::getExtraGraphicsSep()->addChild(FdExtraGraphics::DOFHighlightSep);
}

void FdExtraGraphics::hideDOFVisualizing()
{
  FdDB::getExtraGraphicsSep()->removeChild(FdExtraGraphics::DOFHighlightSep);
  FdExtraGraphics::DOFHighlightSep = NULL;
}


static FaVec3 ourCurrentDirection(1.0,0.0,0.0);

void FdExtraGraphics::showDirection(const FaVec3& from, const FaVec3& direction)
{
  if (FdExtraGraphics::directionSep)
    FdDB::getExtraGraphicsSep()->removeChild(FdExtraGraphics::directionSep);

  FdExtraGraphics::directionSep = makeDirectionVisualizing(from, direction);
  FdDB::getExtraGraphicsSep()->addChild(FdExtraGraphics::directionSep);

  ourCurrentDirection = direction;
}

void FdExtraGraphics::hideDirection()
{
  FdDB::getExtraGraphicsSep()->removeChild(FdExtraGraphics::directionSep);
  FdExtraGraphics::directionSep = NULL;
}

void FdExtraGraphics::moveDirection(const FaVec3& newFromPoint)
{
  if (FdExtraGraphics::directionSep)
    FdExtraGraphics::showDirection(newFromPoint, ourCurrentDirection);
}


void FdExtraGraphics::showLine(const FaVec3& from, const FaVec3& to, const FdColor& color)
{
  if (FdExtraGraphics::lineSep)
    FdDB::getExtraGraphicsSep()->removeChild(FdExtraGraphics::lineSep);

  FdExtraGraphics::lineSep = FdExtraGraphics::makeLineVisualizing(from, to, color);
  FdDB::getExtraGraphicsSep()->insertChild(FdExtraGraphics::lineSep, 0);
}

void FdExtraGraphics::hideLine()
{
  FdDB::getExtraGraphicsSep()->removeChild(FdExtraGraphics::lineSep);
  FdExtraGraphics::lineSep = NULL;
}


void FdExtraGraphics::showCylinder(const FaMat34& matrix, const std::vector<FaVec3>& points, bool arcOnly)
{
  FdExtraGraphics::showCylinder(FFaCylinderGeometry(points,arcOnly),matrix);
}

void FdExtraGraphics::showCylinder(const FFaCylinderGeometry& cylinder, const FaMat34& matrix, bool highlight)
{
  if (FdExtraGraphics::cylSep)
    FdDB::getExtraGraphicsSep()->removeChild(FdExtraGraphics::cylSep);

  FdExtraGraphics::cylSep = FdExtraGraphics::makeCylinderVisualizing(cylinder,matrix,highlight);
  FdDB::getExtraGraphicsSep()->addChild(FdExtraGraphics::cylSep);
}

void FdExtraGraphics::hideCylinder()
{
  if (FdExtraGraphics::cylSep)
    FdDB::getExtraGraphicsSep()->removeChild(FdExtraGraphics::cylSep);

  FdExtraGraphics::cylSep = NULL;
}


void FdExtraGraphics::highlight(const FFaGeometryBase* geo, const FaMat34& matrix, bool onOff)
{
  const FFaCylinderGeometry* cyl = dynamic_cast<const FFaCylinderGeometry*>(geo);
  if (!cyl) return;

  if (onOff)
    FdExtraGraphics::showCylinder(*cyl,matrix,true);
  else
    FdExtraGraphics::hideCylinder();
}


void FdExtraGraphics::showCS(const FaMat34& globalCS)
{
  if (FdExtraGraphics::CSSep)
    FdDB::getExtraGraphicsSep()->removeChild(FdExtraGraphics::CSSep);

  SoPolygonOffset* poff = new SoPolygonOffset;
  poff->factor = 2;
  poff->units = 2;
  poff->styles = SoPolygonOffset::LINES;

  FdExtraGraphics::CSSep = new SoSeparator;
  FdTransformKit* xfkit = new FdTransformKit;
  xfkit->setPart("symbol", FdSymbolDefs::getSymbol(FdSymbolDefs::INT_LINK_COORD_SYS));

  SoTransform* xf = SO_GET_PART(xfkit, "firstTrans", SoTransform);
  xf->setMatrix(FdConverter::toSbMatrix(globalCS));
  xfkit->setPart("appearance.material", FdSymbolDefs::getHighlightMaterial());

  FdExtraGraphics::CSSep->addChild(poff);
  FdExtraGraphics::CSSep->addChild(xfkit);
  FdDB::getExtraGraphicsSep()->insertChild(FdExtraGraphics::CSSep, 0);
}

void FdExtraGraphics::hideCS()
{
  FdDB::getExtraGraphicsSep()->removeChild(FdExtraGraphics::CSSep);
  FdExtraGraphics::CSSep = NULL;
}


SoSeparator *FdExtraGraphics::makeDirectionVisualizing(const FaVec3& from, const FaVec3& direction)
{
  SoSeparator* result    = new SoSeparator;
  SoPickStyle* pickStyle = new SoPickStyle;
  SoTransform* transform = new SoTransform;

  float scale = 0.1 * FdDB::getCameraDistance(from);
  transform->translation.setValue(FdConverter::toSbVec3f(from));
  transform->rotation.setValue(SbRotation(SbVec3f(1,0,0),FdConverter::toSbVec3f(direction)));
  transform->scaleFactor.setValue(scale,scale,scale);

  pickStyle->style.setValue(SoPickStyle::UNPICKABLE);
  result->addChild(pickStyle);
  result->addChild(transform);
  result->addChild(FdExtraGraphics::makeArrowGraph());

  return result;
}


static SoMaterial* new_material(float r, float g, float b)
{
  SoMaterial* mat = new SoMaterial;
  mat->diffuseColor.setValue(r,g,b);
  mat->ambientColor.setValue(r,g,b);
  mat->emissiveColor.setValue(r,g,b);
  return mat;
}


SoSeparator* FdExtraGraphics::makeLineVisualizing(const FaVec3& from,
                                                  const FaVec3& to,
                                                  const FdColor& color)
{
  SoSeparator* result = new SoSeparator;
  result->addChild(new_material(color[0], color[1], color[2]));

  SoCoordinate3* coords = new SoCoordinate3;
  coords->point.set1Value(0, (float)from[0], (float)from[1], (float)from[2]);
  coords->point.set1Value(1, (float)to[0], (float)to[1], (float)to[2]);
  result->addChild(coords);

  SoIndexedLineSet* line = new SoIndexedLineSet;
  line->coordIndex.set1Value(0,0);
  line->coordIndex.set1Value(1,1);
  line->coordIndex.set1Value(2,-1);
  result->addChild(line);

  return result;
}


SoSeparator* FdExtraGraphics::makeCylinderVisualizing(const FFaCylinderGeometry& cylinder,
                                                      const FaMat34& globalMatrix, bool highlight)
{
  SoSeparator* result = new SoSeparator;

  // Material
  if (highlight)
    result->addChild(FdSymbolDefs::getHighlightMaterial());
  else
    result->addChild(new_material(1,1,0)); // yellow

  // Transform
  SoTransform* globalTrans = new SoTransform;
  result->addChild(globalTrans);
  globalTrans->setMatrix(FdConverter::toSbMatrix(globalMatrix));

  SoTransform* localTrans = new SoTransform;
  result->addChild(localTrans);
  localTrans->setMatrix(FdConverter::toSbMatrix(cylinder.getTransMatrix()));

  std::pair<double,double> cylEnds = cylinder.getZData();
  std::pair<double,double> angleData = cylinder.getAngleData();

  const int sides = 64;
  const float fullCircle = 2*M_PI;
  float angle = (float)(angleData.second - angleData.first);
  float radius = (float)cylinder.getRadius();
  float deltaAngle = angle/(float)sides;
  if (angle > fullCircle-deltaAngle)
  {
    angle = fullCircle;
    deltaAngle = angle/(float)sides;
  }

  float x, y, z;
  int i, k, nCoords = 0, nLines = 0;
  SoCoordinate3* coords = new SoCoordinate3;
  result->addChild(coords);

  for (k = 0; k < 2; k++) // set coordinates for top and bottom circles
  {
    z = (float)(k == 0 ? cylEnds.first : cylEnds.second);
    for (i = 0; i < sides; i++)
    {
      x = radius * cosf(deltaAngle*i);
      y = radius * sinf(deltaAngle*i);
      coords->point.set1Value(nCoords++, x, y, z);
    }
  }

  // coordinates for center of circles
  x = y = 0.0f;
  float crossLength = radius*0.1f;
  for (k = 0; k < 2; k++)
  {
    z = (float)(k == 0 ? cylEnds.first : cylEnds.second);
    coords->point.set1Value(nCoords++, crossLength, y, z);
    coords->point.set1Value(nCoords++, -crossLength, y, z);
    coords->point.set1Value(nCoords++, x, crossLength, z);
    coords->point.set1Value(nCoords++, x, -crossLength, z);
  }

  // coordinates for center line
  coords->point.set1Value(nCoords++, x, y, (float)cylEnds.first);
  coords->point.set1Value(nCoords, x, y, (float)cylEnds.second);

  // Draw cylinder
  SoIndexedLineSet* line = new SoIndexedLineSet;
  result->addChild(line);

  // center line
  line->coordIndex.set1Value(nLines++, nCoords-1);
  line->coordIndex.set1Value(nLines++, nCoords);
  line->coordIndex.set1Value(nLines++, -1);

  // center of circle
  int temp = nCoords-2; // last of "center of circle" coords
  for (k = 0; k < 4; k++)
  {
    line->coordIndex.set1Value(nLines++, temp--);
    line->coordIndex.set1Value(nLines++, temp--);
    line->coordIndex.set1Value(nLines++, -1);
  }

  // circles
  for (k = 0; k < 2; k++)
  {
    int n = sides*k;
    for (i = 0; i < sides; i++)
      line->coordIndex.set1Value(nLines++,i+n);
    if (angle == fullCircle) // close the whole circle
      line->coordIndex.set1Value(nLines++,n);
    line->coordIndex.set1Value(nLines++,-1);
  }

  if (angle < fullCircle) // cake piece
  {
    //bottom
    line->coordIndex.set1Value(nLines++,0);
    line->coordIndex.set1Value(nLines++,nCoords-1);
    line->coordIndex.set1Value(nLines++,sides-1);
    line->coordIndex.set1Value(nLines++,-1);
    //top
    line->coordIndex.set1Value(nLines++,sides);
    line->coordIndex.set1Value(nLines++,nCoords);
    line->coordIndex.set1Value(nLines++,sides*2-1);
    line->coordIndex.set1Value(nLines++,-1);
    //along cylinder
    line->coordIndex.set1Value(nLines++,0);
    line->coordIndex.set1Value(nLines++,sides);
    line->coordIndex.set1Value(nLines++,-1);

    line->coordIndex.set1Value(nLines++,sides-1);
    line->coordIndex.set1Value(nLines++,sides*2-1);
    line->coordIndex.set1Value(nLines++,-1);
  }
  else // lines along whole cylinder
  {
    line->coordIndex.set1Value(nLines++,0);
    line->coordIndex.set1Value(nLines++,sides);
    line->coordIndex.set1Value(nLines++,-1);
    line->coordIndex.set1Value(nLines++,sides/2);
    line->coordIndex.set1Value(nLines++,sides/2+sides);
    line->coordIndex.set1Value(nLines++,-1);
  }
  return result;
}


SoSeparator* FdExtraGraphics::makeDOFVisualizing(int DOF, const FaVec3& center, const FaVec3& direction,
                                                 SoNode* rootOfObjToSuround)
{
  SoTrackballManip *ballManip;
  SoJackManip *jackManip;
  SoDragger *dragger;

  float scale;
  if (rootOfObjToSuround)
  {
    SbViewportRegion vp;
    SoGetBoundingBoxAction bboxGetter(vp);
    bboxGetter.apply(rootOfObjToSuround);
    SbBox3f bbox = bboxGetter.getBoundingBox();
    if (bbox.isEmpty())
      scale = 2.0f * FdSymbolDefs::getSymbolScale();
    else
    {
      float h, w, d;
      bbox.getSize(h,w,d);
      if (w > h) h = w;
      if (d > h) h = d;
      scale = 0.25f * h;
    }
  }
  else
    scale = 0.07 * FdDB::getCameraDistance(center);

  SoSeparator* result = new SoSeparator;
  SoPickStyle* pickStyle = new SoPickStyle;
  pickStyle->style.setValue(SoPickStyle::UNPICKABLE);

  SoTransform* transform = new SoTransform;
  transform->translation.setValue(FdConverter::toSbVec3f(center));
  transform->rotation.setValue(SbRotation(SbVec3f(1,0,0),
                               FdConverter::toSbVec3f(direction)));
  transform->scaleFactor.setValue(scale,scale,scale);

  result->addChild(pickStyle);
  result->addChild(transform);

  switch (DOF)
    {
    case FdObject::RIGID:
      {
	SoDrawStyle* drawStyle = new SoDrawStyle;
	drawStyle->style.setValue(SoDrawStyle::LINES);
	result->addChild(drawStyle);
	result->addChild(new SoCube);
      }
      break;

    case FdObject::REV:
      {
	ballManip = new SoTrackballManip;
	ballManip->ref();
	dragger = ballManip->getDragger();
	result->addChild(SO_GET_PART(dragger,"XRotator",SoSeparator));
	ballManip->unref();

	SoCoordinate3* xLineCoords = new SoCoordinate3;
	xLineCoords->point.set1Value(0,-1,0,0);
	xLineCoords->point.set1Value(0, 1,0,0);
	result->addChild(xLineCoords);
	result->addChild(new SoLineSet);
      }
      break;

    case FdObject::REV_STRECH:
    case FdObject::REV_CYL:
    case FdObject::REV_PRISM:
    case FdObject::CYL:
      {
	ballManip = new SoTrackballManip;
	ballManip->ref();
	dragger = ballManip->getDragger();
	result->addChild(SO_GET_PART(dragger,"XRotator",SoSeparator));
	ballManip->unref();

	jackManip = new SoJackManip;
	jackManip->ref();
	dragger = jackManip->getDragger();
	result->addChild(SO_GET_PART(dragger,"translator.xFeedback",SoSeparator));
	jackManip->unref();
      }
      break;

    case FdObject::PRISM_STRECH:
    case FdObject::PRISM:
      {
	jackManip = new SoJackManip;
	jackManip->ref();
	dragger = jackManip->getDragger();
	result->addChild(SO_GET_PART(dragger,"translator.xFeedback",SoSeparator));
	jackManip->unref();
      }
      break;

    case FdObject::BALL:
      {
	ballManip = new SoTrackballManip;
	ballManip->ref();
	dragger = ballManip->getDragger();
	result->addChild(SO_GET_PART(dragger,"XRotator",SoSeparator));
	result->addChild(SO_GET_PART(dragger,"YRotator",SoSeparator));
	result->addChild(SO_GET_PART(dragger,"ZRotator",SoSeparator));
	ballManip->unref();
      }
      break;

    case FdObject::BALL_STRECH:
      {
	ballManip = new SoTrackballManip;
	ballManip->ref();
	dragger = ballManip->getDragger();
	result->addChild(SO_GET_PART(dragger,"XRotator",SoSeparator));
	result->addChild(SO_GET_PART(dragger,"YRotator",SoSeparator));
	result->addChild(SO_GET_PART(dragger,"ZRotator",SoSeparator));
	ballManip->unref();

	jackManip = new SoJackManip;
	jackManip->ref();
	dragger = jackManip->getDragger();
	result->addChild(SO_GET_PART(dragger,"translator.xFeedback",SoSeparator));
	jackManip->unref();
      }
      break;

    case FdObject::FREE:
      {
	jackManip = new SoJackManip;
	jackManip->ref();
	dragger = jackManip->getDragger();
	result->addChild(SO_GET_PART(dragger,"translator.xFeedback",SoSeparator));
	result->addChild(SO_GET_PART(dragger,"translator.yFeedback",SoSeparator));
	result->addChild(SO_GET_PART(dragger,"translator.zFeedback",SoSeparator));
	jackManip->unref();
      }
      break;
    }

  return result;
}


SoGroup* FdExtraGraphics::makeCornerBoxGraph()
{
  static float coordsVal[32][3] ={{ 0, 0.19f, 0    },// 0
				  { 0,     0, 0    },// 1
				  { 0.19f, 0, 0    },// 2
				  { 0,     0, 0.19f},// 3
				  { 0.81f, 0, 0    },// 4
				  { 1,     0, 0    },// 5
				  { 1, 0.19f, 0    },// 6
				  { 1,     0, 0.19f},// 7
				  { 1, 0.81f, 0    },// 8
				  { 1,     1, 0    },// 9
				  { 0.81f, 1, 0    },// 10
				  { 1,     1, 0.19f},// 11
				  { 0.19f, 1, 0    },// 12
				  { 0,     1, 0    },// 13
				  { 0, 0.81f, 0    },// 14
				  { 0,     1, 0.19f},// 15
				  { 0, 0.19f, 1    },// 16
				  { 0,     0, 1    },// 17
				  { 0.19f, 0, 1    },// 18
				  { 0,     0, 0.81f},// 19
				  { 0.81f, 0, 1    },// 20
				  { 1,     0, 1    },// 21
				  { 1, 0.19f, 1    },// 22
				  { 1,     0, 0.81f},// 23
				  { 1, 0.81f, 1    },// 24
				  { 1,     1, 1    },// 25			
				  { 0.81f, 1, 1    },// 26
				  { 1,     1, 0.81f},// 27
				  { 0.19f, 1, 1    },// 28
				  { 0,     1, 1    },// 29
				  { 0, 0.81f, 1    },// 30
				  { 0,     1, 0.81f}};// 31

  static int32_t indexes[56] = { 0 , 1, 2,-1,  1, 3,-1,
				 4 , 5, 6,-1,  5, 7,-1,
				 8 , 9,10,-1,  9,11,-1,
				 12,13,14,-1, 13,15,-1,
				 16,17,18,-1, 17,19,-1,
				 20,21,22,-1, 21,23,-1,
				 24,25,26,-1, 25,27,-1,
				 28,29,30,-1, 29,31,-1 };

  SoGroup* result = new SoGroup;
  result->addChild(new SoDrawStyle);
  result->addChild(new_material(1,1,1));

  SoCoordinate3* coords = new SoCoordinate3;
  coords->point.setValues(0,32,coordsVal);
  result->addChild(coords);

  SoIndexedLineSet* box = new SoIndexedLineSet;
  box->coordIndex.setValues(0,56,indexes);
  result->addChild(box);

  return result;
}


SoGroup* FdExtraGraphics::makeArrowGraph()
{
  static float coordsVal[6][3] ={ {0,0,0}, //0
				  {1,0,0}, //1
				  {0.67f,  0,  0.056f},//2
				  {0.67f,  0, -0.056f},//3
				  {0.67f,  0.056f,  0},//4
				  {0.67f, -0.056f,  0}};//5

  static int32_t indexes[15] = { 0 , 1, 2, 4, 1, 3, 5,  1,-1,
				 4 , 3, -1,
				 5 , 2, -1};

  SoGroup* result = new SoGroup;
  result->addChild(new SoDrawStyle);
  result->addChild(new_material(1,1,0));

  SoCoordinate3* coords = new SoCoordinate3;
  coords->point.setValues(0,6,coordsVal);
  result->addChild(coords);

  SoIndexedLineSet* box = new SoIndexedLineSet;
  box->coordIndex.setValues(0,15,indexes);
  result->addChild(box);

  return result;
}


#define FD_BEGIN_LINESHAPE(rootNodeName)		\
{							\
  SoIndexedLineSet * lines = new SoIndexedLineSet;	\
  SoCoordinate3 *coords = new SoCoordinate3;		\
  rootNodeName->addChild(coords);			\
  rootNodeName->addChild(lines);			\
  int idx = 0; int idxCount = 0;			\
  FaVec3 v;

#define FD_LINE(x, y, z)					\
{                                                               \
  coords->point.set1Value(idx, (float)x, (float)y, (float)z);	\
  lines->coordIndex.set1Value(idxCount, idx);			\
  ++idxCount;  ++idx;                                           \
}

// This macro needs the angle to be degrees
#define FD_C_LINE( r, th, l)            \
{                                       \
  tmp[0] = FaVec3(r, th, l);		\
  v = tmp.translation();	        \
  FD_LINE(v[0], v[1], v[2]);            \
}

#define FD_LINE_END                           \
{                                             \
  lines->coordIndex.set1Value(idxCount,  -1); \
  ++idxCount;                                 \
}

#define FD_END_LINESHAPE }


void FdExtraGraphics::show3DLocation(const FaMat34& posRefCS, const FaMat34& rotRefCS, const FFa3DLocation& loc)
{
  if (our3DLocationSep)
    FdExtraGraphics::hide3DLocation();

  our3DLocationSep = new SoSeparator;
  FdDB::getExtraGraphicsSep()->addChild(our3DLocationSep);

  SoPolygonOffset * offset = new SoPolygonOffset;
  offset->styles.setValue(SoPolygonOffset::LINES);
  offset->units.setValue(-1);
  our3DLocationSep->addChild(offset);

  SoSeparator * posSep = new SoSeparator;
  SoSeparator * rotSep = new SoSeparator;
  our3DLocationSep->addChild(posSep);
  our3DLocationSep->addChild(rotSep);

  posSep->addChild(new_material(1,0.5,0.7));
  posSep->addChild(new_material(0.7,0.5,1));

  FaVec3 pos = loc.translation();
  double pmax = pos.length() / 3.0;
  double camToPos      = FdDB::getCameraDistance(pos);
  double camToPosRefCS = FdDB::getCameraDistance(posRefCS.translation());
  double scale = 0.06 * (camToPos < camToPosRefCS ? camToPos : camToPosRefCS);
  // pd - The length of the end-offset used to draw the end arrows
  float pd = static_cast<float>(scale < pmax ? scale : pmax);
  float d = pd;

  // Position

  SoTransform * posXf = new SoTransform;
  posSep->addChild(posXf);
  posXf->setMatrix(FdConverter::toSbMatrix(posRefCS));

  float x = (float)pos[0];
  float y = (float)pos[1];
  float z = (float)pos[2];

  switch (loc.getPosType())
  {
    case FFa3DLocation::CART_X_Y_Z:
      {
        d = x < 0 ? -pd : pd;
        FD_BEGIN_LINESHAPE(posSep);

          if ( abs(x) > 3 * pd )
          {
            // X Arrow start
            FD_LINE( 0, 0, 0);
            FD_LINE( d, d/4, 0);
            FD_LINE( d,-d/4, 0);
            FD_LINE( 0, 0, 0);
            FD_LINE_END;
            // X Line
            FD_LINE( d,0,0);
            FD_LINE( x-d,0,0);
            FD_LINE_END;
            // X Arrow end
            FD_LINE( x,0,0);
            FD_LINE( x-d, d/4,0);
            FD_LINE( x-d,-d/4,0);
            FD_LINE( x,0,0);
            FD_LINE_END;
          }
          else
          {
            // X Arrow start
            FD_LINE( 0, 0, 0);
            FD_LINE( -d, d/4, 0);
            FD_LINE( -d,-d/4, 0);
            FD_LINE( 0, 0, 0);
            FD_LINE_END;
            // X Line
            FD_LINE( -2*d, 0, 0);
            FD_LINE( -d, 0, 0);
            FD_LINE_END;
            FD_LINE( 0, 0, 0);
            FD_LINE( x, 0, 0);
            FD_LINE_END;
            FD_LINE( x+2*d, 0, 0);
            FD_LINE( x+d, 0, 0);
            FD_LINE_END;

            // X Arrow end
            FD_LINE( x,0,0);
            FD_LINE( x+d, d/4,0);
            FD_LINE( x+d,-d/4,0);
            FD_LINE( x,0,0);
            FD_LINE_END;

          }
          d = y < 0 ? -pd : pd;
          if ( abs(y) > 3 * pd )
          {
            // Y Arrow Start
            FD_LINE( x, 0, 0);
            FD_LINE( x-d/4, d, 0);
            FD_LINE( x+d/4, d, 0);
            FD_LINE( x, 0, 0);
            FD_LINE_END;
            // Y Line
            FD_LINE( x,d,0);
            FD_LINE( x,y-d,0);
            FD_LINE_END;
            // Y Arrow end
            FD_LINE( x, y, 0);
            FD_LINE( x-d/4, y-d, 0);
            FD_LINE( x+d/4, y-d, 0);
            FD_LINE( x, y, 0);

            FD_LINE_END;
          }
          else
          {
            // Arrows on outside
            // Y Arrow start
            FD_LINE( x, 0, 0);
            FD_LINE( x-d/4, -d, 0);
            FD_LINE( x+d/4, -d, 0);
            FD_LINE( x, 0, 0);
            FD_LINE_END;
            // Y Line
            FD_LINE( x, -2*d, 0);
            FD_LINE( x, -d, 0);
            FD_LINE_END;
            FD_LINE( x, 0, 0);
            FD_LINE( x, y, 0);
            FD_LINE_END;
            FD_LINE( x, y+2*d, 0);
            FD_LINE( x, y+d, 0);
            FD_LINE_END;

            // Y Arrow end
            FD_LINE( x, y, 0);
            FD_LINE( x+d/4,y+d, 0);
            FD_LINE( x-d/4,y+d, 0);
            FD_LINE( x, y, 0);
            FD_LINE_END;

          }
          d = z < 0 ? -pd : pd;
          if ( abs(z) > 3 * pd )
          {
            // Z Arrow start
            FD_LINE( x, y, 0);
            FD_LINE( x-d/4, y, d);
            FD_LINE( x+d/4, y, d);
            FD_LINE( x, y, 0);

            FD_LINE_END;
            // Z Line
            FD_LINE( x, y, d);
            FD_LINE( x, y, z-d);
            FD_LINE_END;
            // Z Arrow end
            FD_LINE( x , y, z);
            FD_LINE( x-d/4, y, z-d);
            FD_LINE( x+d/4, y, z-d);
            FD_LINE( x , y, z);

            FD_LINE_END;
          }
          else
          {
            // Z Arrow start
            FD_LINE( x, y, 0);
            FD_LINE( x-d/4,y, -d);
            FD_LINE( x+d/4,y, -d);
            FD_LINE( x, y, 0);
            FD_LINE_END;

            // Z Line
            FD_LINE( x, y, -2*d);
            FD_LINE( x, y, -d);
            FD_LINE_END;
            FD_LINE( x, y, 0);
            FD_LINE( x, y, z);
            FD_LINE_END;
            FD_LINE( x, y, z+2*d);
            FD_LINE( x, y, z+d);
            FD_LINE_END;

            // Z Arrow end
            FD_LINE( x, y, z);
            FD_LINE( x+d/4, y,z+d);
            FD_LINE( x-d/4, y,z+d);
            FD_LINE( x, y, z);
            FD_LINE_END;
          }FD_END_LINESHAPE;
        break;
      }
    case FFa3DLocation::CYL_R_XR_Z:
    case FFa3DLocation::CYL_R_ZR_Y:
    case FFa3DLocation::CYL_R_YR_X:
      {
        FFa3DLocation tmp(loc);

        FD_BEGIN_LINESHAPE(posSep);

          // Using the FFa3Dlocation data as cylindrical coorinates
          // directly. The following is approx the same as above,
          // and the FD_C_LINE macro converts from cyl coordinates to
          // cartesian, and builds the line.
          // in addition, the d value needs to be converted to angular value
          // d-Like-angle = d/r

          x = static_cast<float> (loc[0][0]);
          y = static_cast<float> (loc[0][1]); // This is degrees
          z = static_cast<float> (loc[0][2]);

          d = x < 0 ? -pd : pd;
          float da = d * 180 / M_PI; // Adding a conversion to degrees deg = d/r*180/pi = (d*180/pi)/r

          if ( abs(x) > 2 * pd )
          {
            // X Arrow start
            FD_C_LINE( 0, 0, 0);
            FD_C_LINE( d, da/(4*d), 0);
            FD_C_LINE( d,-da/(4*d), 0);
            FD_C_LINE( 0, 0, 0);
            FD_LINE_END;
            // X Line
            FD_C_LINE( d,0,0);
            FD_C_LINE( x-d,0,0);
            FD_LINE_END;
            // X Arrow end
            FD_C_LINE( x,0,0);
            FD_C_LINE( x-d, da/(4*(x-d)),0);
            FD_C_LINE( x-d,-da/(4*(x-d)),0);
            FD_C_LINE( x,0,0);
            FD_LINE_END;
          }
          else
          {
            // X Arrow start
            FD_C_LINE( 0, 0, 0);
            FD_C_LINE( -d, da/(4*-d), 0);
            FD_C_LINE( -d,-da/(4*-d), 0);
            FD_C_LINE( 0, 0, 0);
            FD_LINE_END;
            // X Line
            FD_C_LINE( -2*d, 0, 0);
            FD_C_LINE( -d, 0, 0);
            FD_LINE_END;
            FD_C_LINE( 0, 0, 0);
            FD_C_LINE( x, 0, 0);
            FD_LINE_END;
            FD_C_LINE( x+2*d, 0, 0);
            FD_C_LINE( x+d, 0, 0);
            FD_LINE_END;

            // X Arrow end
            FD_C_LINE( x,0,0);
            FD_C_LINE( x+d, da/(4*(x+d)),0);
            FD_C_LINE( x+d,-da/(4*(x+d)),0);
            FD_C_LINE( x,0,0);
            FD_LINE_END;

          }

          d = y < 0 ? -pd : pd;
          da = d * 180 / M_PI; // Adding a conversion to degrees deg = d/r*180/pi = (d*180/pi)/r

          if ( abs(y) > abs(2 * da / x) )
          {
            // Y Arrow Start
            FD_C_LINE( x, 0, 0);
            FD_C_LINE( x-d/4, da/abs(x-d/4), 0);
            FD_C_LINE( x+d/4, da/abs(x+d/4), 0);
            FD_C_LINE( x, 0, 0);
            FD_LINE_END;

            // Y Line

            //int p = (int)abs((y-2*da/abs(x))*180/(2*M_PI));
            // p is dividing the curve into steps of 2 degrees.
            // Corrected for the arrows in the ends
            int p = (int) abs(( y - 2 * da / abs(x) ) / 2);//*180/(2*M_PI));
            if ( p > 0 )
            {
              for ( int i = 0; i <= p; i++ )
              {
                FD_C_LINE( x, da/x + i*(y-2*da/x)/p, 0);
              }
              FD_LINE_END;
            }
            // Y Arrow end
            FD_C_LINE( x, y, 0);
            FD_C_LINE( x-d/4, y-da/abs(x-d/4), 0);
            FD_C_LINE( x+d/4, y-da/abs(x+d/4), 0);
            FD_C_LINE( x, y, 0);
            FD_LINE_END;

          }
          else
          { // Arrows on outside
            // Y Arrow start
            FD_C_LINE( x, 0, 0);
            FD_C_LINE( x-d/4, -da/abs(x-d/4), 0);
            FD_C_LINE( x+d/4, -da/abs(x+d/4), 0);
            FD_C_LINE( x, 0, 0);
            FD_LINE_END;

            // Y Line

            // p is dividing the curve into steps of 0.5 degrees.
            //int p = (int)abs((da/x)*180/(2*M_PI));
            int p = (int) abs(( da / x ) * 2);//*180/(2*M_PI));
            int i;
            if ( p > 0 )
            {
              for ( i = 0; i <= p; i++ )
              {
                FD_C_LINE( x, -2*da/abs(x) + i*(da/abs(x))/p, 0);
              }
              FD_LINE_END;
            }

            // p is dividing the curve into steps of 2 degrees.
            //p = (int)abs(y*180/(2*M_PI));
            p = (int) abs(y);//*180/(2*M_PI));
            if ( p > 0 )
            {
              for ( i = 0; i <= p; ++i )
              {
                FD_C_LINE( x, i*y/p, 0);
              }
              FD_LINE_END;
            }
            // p is dividing the curve into steps of 0.5 degrees.
            //p = (int)abs((da/x)*180/(2*M_PI));
            p = static_cast<int>(abs(( da / x ) * 2)); //*180/(2*M_PI));
            if ( p > 0 )
            {
              for ( i = 0; i <= p; ++i )
              {
                FD_C_LINE( x, (y+2*da/abs(x)) - i*(da/abs(x))/p , 0);
              }
              FD_LINE_END;
            }
            // Y Arrow end
            FD_C_LINE( x, y, 0);
            FD_C_LINE(x + d/4, y + da/abs(x+d/4), 0);
            FD_C_LINE(x - d/4, y + da/abs(x-d/4), 0);
            FD_C_LINE( x, y, 0);
            FD_LINE_END;

          }
          d = z < 0 ? -pd : pd;
          if ( abs(z) > 2 * pd )
          {
            // Z Arrow start
            FD_C_LINE( x, y, 0);
            FD_C_LINE( x-d/4, y, d);
            FD_C_LINE( x+d/4, y, d);
            FD_C_LINE( x, y, 0);

            FD_LINE_END;
            // Z Line
            FD_C_LINE( x, y, d);
            FD_C_LINE( x, y, z-d);
            FD_LINE_END;
            // Z Arrow end
            FD_C_LINE( x , y, z);
            FD_C_LINE( x-d/4, y, z-d);
            FD_C_LINE( x+d/4, y, z-d);
            FD_C_LINE( x , y, z);

            FD_LINE_END;
          }
          else
          {
            // Z Arrow start
            FD_C_LINE( x, y, 0);
            FD_C_LINE( x-d/4,y, -d);
            FD_C_LINE( x+d/4,y, -d);
            FD_C_LINE( x, y, 0);
            FD_LINE_END;

            // Z Line
            FD_C_LINE( x, y, -2*d);
            FD_C_LINE( x, y, -d);
            FD_LINE_END;
            FD_C_LINE( x, y, 0);
            FD_C_LINE( x, y, z);
            FD_LINE_END;
            FD_C_LINE( x, y, z+2*d);
            FD_C_LINE( x, y, z+d);
            FD_LINE_END;

            // Z Arrow end
            FD_C_LINE( x, y, z);
            FD_C_LINE( x+d/4, y,z+d);
            FD_C_LINE( x-d/4, y,z+d);
            FD_C_LINE( x, y, z);
            FD_LINE_END;
          }

        FD_END_LINESHAPE;
        break;
      }
      default:
        break;
    }

  FaVec3 from = rotRefCS.translation();
  FaVec3 to = posRefCS * pos;

  if ( rotRefCS != FaMat34() )
  {
    FD_BEGIN_LINESHAPE(rotSep);
      FD_LINE(from[0] ,from[1], from[2]);
      FD_LINE(to[0] , to[1], to[2]);
      FD_LINE_END;
    FD_END_LINESHAPE;
  }
  // Rotation

  SoTransform * rotXf = new SoTransform;
  rotSep->addChild(rotXf);
  FaMat34 rot(rotRefCS.direction(), to);
  rotXf->setMatrix(FdConverter::toSbMatrix(rot));

  float s = FdSymbolDefs::getSymbolScale();

  FD_BEGIN_LINESHAPE(rotSep);

    FD_LINE( 1.15*s, 0, 0);
    FD_LINE( 1.65*s, 0, 0);
    FD_LINE_END;
    FD_LINE( 1.75*s, -0.075*s, 0.125*s);
    FD_LINE( 1.75*s, 0.075*s, -0.125*s);
    FD_LINE_END;
    FD_LINE( 1.75*s, 0.075*s, 0.125*s);
    FD_LINE( 1.75*s, -0.075*s, -0.125*s);
    FD_LINE_END;

    FD_LINE( 0, 1.15*s, 0);
    FD_LINE( 0, 1.65*s, 0);
    FD_LINE_END;
    FD_LINE( 0.075*s, 1.75*s, 0.125*s);
    FD_LINE( 0, 1.75*s, 0);
    FD_LINE_END;
    FD_LINE( -0.075*s, 1.75*s, 0.125*s);
    FD_LINE( 0.075*s, 1.75*s, -0.125*s);
    FD_LINE_END;

    FD_LINE( 0, 0, 1.15*s);
    FD_LINE( 0, 0, 1.65*s);
    FD_LINE_END;

    FD_LINE( 0.075*s, -0.125*s, 1.75*s);
    FD_LINE(-0.075*s, -0.125*s, 1.75*s);
    FD_LINE( 0.075*s, 0.125*s, 1.75*s);
    FD_LINE(-0.075*s, 0.125*s, 1.75*s);
    FD_LINE_END;

  FD_END_LINESHAPE;
}


void FdExtraGraphics::hide3DLocation()
{
  if (our3DLocationSep)
    FdDB::getExtraGraphicsSep()->removeChild(our3DLocationSep);
  our3DLocationSep = 0;
}
