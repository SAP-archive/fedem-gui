// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

/***********************************************************************
 *
 * CLASS: FdCtrSymDef
 * AUTHOR: Magnus Svanberg
 * LAST MODIFIED: 19 sept 1997
 *
 * DESCRIPTION:
 * The class describes the graphic symbols of the control system.
 *
 **********************************************************************/

#ifndef FD_CTRL_SYM_DEF_H
#define FD_CTRL_SYM_DEF_H

class FdCtrlSymbolKit;
class SoMaterial;


class FdCtrlSymDef
{
public:
  static void init();

  static SoMaterial* getDefaultMaterial()  { return defaultMaterial; }
  static SoMaterial* getBackMaterial()     { return backMaterial; }
  static SoMaterial* getHighlightMaterial(){ return highlightMaterial; }

  static FdCtrlSymbolKit *std3pSym();
  static FdCtrlSymbolKit *std2pSym();

  static FdCtrlSymbolKit *adderSym();
  static FdCtrlSymbolKit *comparatorSym();
  static FdCtrlSymbolKit *outputSym();
  static FdCtrlSymbolKit *inputSym();
  static FdCtrlSymbolKit *deadZoneSym();
  static FdCtrlSymbolKit *amplifierSym();
  static FdCtrlSymbolKit *sampleHoldSym();
  static FdCtrlSymbolKit *limDerivatorSym();
  static FdCtrlSymbolKit *multiplierSym();
  static FdCtrlSymbolKit *logicalSwitchSym();
  static FdCtrlSymbolKit *hysteresisSym();
  static FdCtrlSymbolKit *limitationSym();

private:
  static FdCtrlSymbolKit* createSymbol(const float* coords,int numCoords,
                                       const int32_t* lineIndex, int numIndex,
                                       float XWidth, float YWidth,
                                       int nInPorts = 1, int nOutPorts = 1);
  static SoSeparator* createPortSymbol(bool inPort);

  static SoMaterial* defaultMaterial;
  static SoMaterial* backMaterial;
  static SoMaterial* highlightMaterial;

  static SoSeparator* outPortSymbol;
  static SoSeparator* inPortSymbol;
};

#endif
