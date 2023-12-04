// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_SYMBOL_DEFS_H
#define FD_SYMBOL_DEFS_H

#include <Inventor/SbBasic.h>
#include <array>

typedef std::array<float,3> FdColor;

class SoMaterial;
class SoTransform;
class SoDrawStyle;
#ifdef USE_SMALLCHANGE
class SmDepthBuffer;
#endif
class FdSymbolKit;


class FdSymbolDefs
{
public:

  enum symbolsType { COORD_SYST,
		     LINK_COORD_SYS,
		     INT_LINK_COORD_SYS,
		     CENTER_OF_GRAVITY,
		     FORCE,
		     TORQUE,
		     AXIAL_DAMPER,
		     AXIAL_SPRING,
		     SENSOR,

		     S_SINGLE_GAGE,
		     S_DOUBLE_GAGE_90,
		     S_TRIPLE_GAGE_60,
		     S_TRIPLE_GAGE_45,
		     L_SINGLE_GAGE,
		     L_DOUBLE_GAGE_90,
		     L_TRIPLE_GAGE_60,
		     L_TRIPLE_GAGE_45,

		     HIGHER_PAIR,

		     REVJOINT,
		     REVJOINT_MASTER,
		     REVJOINT_SLAVE,

		     BALLJOINT,
		     BALLJOINT_MASTER,
		     BALLJOINT_SLAVE,

		     LINJOINT_MASTER,
		     LINJOINT_LINE,
		     LINPRISM_SLAVE,
		     LINCYL_SLAVE,

		     FREEJOINT,
		     FREEJOINT_SLAVE,
		     FREEJOINT_LINE,

		     RIGIDJOINT,
		     RIGIDJOINT_MASTER,
		     RIGIDJOINT_SLAVE,

		     CAMJOINT_MASTER,
		     CAMJOINT_SLAVE,

		     STICKER,
		     POINT,
		     REFCS,

		     SYMBOL_COUNT };

  static void init();

  static FdSymbolKit* getSymbol(symbolsType symbolIndex);

  static void setSymbolScale(float scale);
  static void setSymbolLineWidth(int width);
  static float getSymbolScale();

  static SoDrawStyle* getGlobalSymbolStyle();
  static SoDrawStyle* getHighlightSymbolStyle();
#ifdef USE_SMALLCHANGE
  static SmDepthBuffer* getHighlightDepthBMod();
#endif

  static SoMaterial* getHighlightMaterial() { return highlightMaterial; }
  static SoMaterial* getDefaultMaterial() { return defaultMaterial; }
  static SoMaterial* getTriadMaterial() { return triadMaterial; }
  static SoMaterial* getGndTriadMaterial() { return gndTriadMaterial; }
  static SoMaterial* getJointMaterial() { return jointMaterial; }
  static SoMaterial* getSprDaMaterial() { return sprDaMaterial; }
  static SoMaterial* getStickerMaterial() { return stickerMaterial; }
  static SoMaterial* getLoadMaterial() { return loadMaterial; }
  static SoMaterial* getHPMaterial() { return HPMaterial; }
  static SoMaterial* getLinkCoordSysMaterial() { return linkCoordSysMaterial; }
  static SoMaterial* getRefPlaneMaterial() { return refPlaneMaterial; }
  static SoMaterial* getSensorMaterial() { return sensorMaterial; }
  static SoMaterial* getStrainRosetteMaterial() { return strainRosetteMaterial; }

  static void makeMaterialHighlight(SoMaterial* material);
  static void setSymbolMaterialColor(SoMaterial* material, const FdColor& color);

  // Methods to set symbol colors:

  static void setDefaultColor(const FdColor& color);
  static void setSensorColor(const FdColor& color);
  static void setTriadColor(const FdColor& color);
  static void setGndTriadColor(const FdColor& color);
  static void setJointColor(const FdColor& color);
  static void setSprDaColor(const FdColor& color);
  static void setStickerColor(const FdColor& color);
  static void setLoadColor(const FdColor& color);
  static void setHPColor(const FdColor& color);
  static void setLinkCoordSysColor(const FdColor& color);
  static void setRefPlaneColor(const FdColor& color);
  static void setStrainRosetteColor(const FdColor& color);

  // Materials

private:
  static SoMaterial  *highlightMaterial;
  static SoMaterial  *defaultMaterial;
  static SoMaterial  *triadMaterial;
  static SoMaterial  *gndTriadMaterial;
  static SoMaterial  *jointMaterial;
  static SoMaterial  *sprDaMaterial;
  static SoMaterial  *stickerMaterial;
  static SoMaterial  *loadMaterial;
  static SoMaterial  *HPMaterial;
  static SoMaterial  *linkCoordSysMaterial;
  static SoMaterial  *refPlaneMaterial;
  static SoMaterial  *sensorMaterial;
  static SoMaterial  *strainRosetteMaterial;

  // Scale pointers

  static SoTransform *GlobalSymbolScale;
  static SoTransform *GlobalAxialSymbolScale;

  // Style

  static SoDrawStyle *GlobalSymbolStyle;

  //////////////////////////////////////////////////
  //
  // Symbol Library:
  //
  ///////////////////////////////////////////////////

  static FdSymbolKit* Symbols[SYMBOL_COUNT];

  // Symbol initialization

  static FdSymbolKit *makeCoordSyst();
  static FdSymbolKit *makeLinkCoordSyst();
  static FdSymbolKit *makeInternalLinkCoordSyst();
  static FdSymbolKit *makeCenterOfGravity();

  static FdSymbolKit *makeForce();
  static FdSymbolKit *makeTorque();
  static FdSymbolKit *makeAxialDamper();
  static FdSymbolKit *makeAxialSpring();
  static FdSymbolKit *makeSensor();

  static FdSymbolKit *makeSmallSingleGage();
  static FdSymbolKit *makeSmallDoubleGage90();
  static FdSymbolKit *makeSmallTripleGage60();
  static FdSymbolKit *makeSmallTripleGage45();

  static FdSymbolKit *makeLargeSingleGage();
  static FdSymbolKit *makeLargeDoubleGage90();
  static FdSymbolKit *makeLargeTripleGage60();
  static FdSymbolKit *makeLargeTripleGage45();

  static FdSymbolKit *makeRevJoint();
  static FdSymbolKit *makeRevJointMaster();
  static FdSymbolKit *makeRevJointSlave();

  static FdSymbolKit *makeBallJoint();
  static FdSymbolKit *makeBallJointMaster();
  static FdSymbolKit *makeBallJointSlave();

  static FdSymbolKit *makeLinJointMaster();
  static FdSymbolKit *makeLinJointLine();
  static FdSymbolKit *makeLinPrismSlave();
  static FdSymbolKit *makeLinCylSlave();

  static FdSymbolKit *makeFreeJoint();
  static FdSymbolKit *makeFreeJointSlave();
  static FdSymbolKit *makeSimpleLine();

  static FdSymbolKit *makeRigidJoint();
  static FdSymbolKit *makeRigidJointMaster();
  static FdSymbolKit *makeRigidJointSlave();

  static FdSymbolKit *makeCamJointMaster();
  static FdSymbolKit *makeCamJointSlave();

  static FdSymbolKit *makeSticker();
  static FdSymbolKit *makePoint();
  static FdSymbolKit *makeRefCS();

  static FdSymbolKit* make_symbol(const float* XYZ, const int32_t* index,
                                  int nCoord, int nIndex, char scale = 'G');
};

#endif
