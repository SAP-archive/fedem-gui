// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUICTRLMODES_H
#define FUICTRLMODES_H


class FuiCtrlModes 
{
  
public:

  enum funcMode{NEUTRAL_MODE,
		CREATE_MODE,
		ROTATE_MODE,
		DELETE_MODE,
		ADDLINEPOINT_MODE,
		REMOVELINEPOINT_MODE,		
		MOVEGROUP_MODE};

  enum neutralMode{EXAM_NEUTRAL,
		   MOVEELEM_NEUTRAL,
		   DRAW_NEUTRAL,
		   MOVELINE_NEUTRAL};
		   



  static void setMode(int newMode);
  static int getMode(){ return mode;}

  static void setState(int newState);
  static int getState(){return state;}

  static void setNeutralType(int newType);
  static int getNeutralType(){ return neutralType;}
  
  static void setNeutralState(int newState);
  static int getNeutralState(){return neutralState;}

  static void done();
  static void cancel();

  static void setCtrlModellerState(bool isOpen);
  static bool isCtrlModellerOpen();

protected:

  static int mode;
  static int state;

  static int neutralType;
  static int neutralState;

  static void setTip();

  static void neutralModeDone();
  static void createModeDone();
  static void deleteModeDone();
  static void rotateModeDone();
  static void addLinePointModeDone();
  static void removeLinePointModeDone();
  static void moveGroupModeDone();

private:
  static bool ctrlModellerOpen;
};

#endif
