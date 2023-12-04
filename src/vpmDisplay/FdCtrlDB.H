// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

/***********************************************************************
 * CLASS: FdCtrlDB
 * AUTHOR: Magnus Svanberg
 * LAST MODIFIED: 6 Okt 1997
 **********************************************************************/

#ifndef FD_CTRL_DB_H
#define FD_CTRL_DB_H

#include <vector>

class SoHandleEventAction;
class SoEventCallback;
class SoSeparator;
class SbVec2f;
class SbVec3f;

class FdObject;
class FdCtrlElement;
class FdCtrlKit;
class FdQtViewer;

class FmCtrlElementBase;
class FmIsRenderedBase;

struct ctrlViewData;


class FdCtrlDB
{
public:
  static void init();
  static void start(bool useGUI);
  static void openCtrl();
  static void closeCtrl();

  static ctrlViewData getView();
  static void setView(const ctrlViewData& cvData);

  static FdCtrlKit   *getCtrlKit();
  static SoSeparator *getCtrlExtraGraphicsRoot();
  static FdObject    *getPickedObject();
  static void setCreatedElem(FmCtrlElementBase* createElem);
  static FdQtViewer* getCtrlViewer(){return ctrlViewer;}

  static SbVec3f getNewVec(const SbVec2f& currPos, bool ignoreSnap = false);

  static void updateMode(int newMode, int oldMode);
  static void updateNeutralType(int newNeutralType, int oldNeutralMode);
  static void zoomTo(FmIsRenderedBase* elmOrLine);

private:
  static FdObject* pickObject(bool single, SoHandleEventAction* evHaAction);

  //Manipulation events
  static void selectCB(void *, SoEventCallback *);

  static void moveElemCB(void *, SoEventCallback *);
  static void moveGroupCB(void *, SoEventCallback *);

  static void createElemCB(void *, SoEventCallback *);
  static void deleteObjectCB(void *, SoEventCallback *);
  static void rotateElemCB(void *, SoEventCallback *);

  static void drawLineCB(void *, SoEventCallback *);
  static void moveLineCB(void *, SoEventCallback *);
  static void addLinePointCB(void *, SoEventCallback *);
  static void removeLinePointCB(void *, SoEventCallback *);

  //Adminstrate events
  static void adminEventCB(void *,SoEventCallback *);

  //Init and start variable
  static FdQtViewer *ctrlViewer;
  static SoSeparator *ctrlRoot;//Top node in the ctrl scengraph.
  static SoSeparator * ourExtraGraphicsSep;
  static FdCtrlKit *ctrlKit;

  //Callback node.
  static SoEventCallback *manipEventCbNode;
  static SoEventCallback *adminEventCbNode;

  //adminCB
  static bool cancel;

  //creatCB
  static FdCtrlElement *newFdElement;
  static bool isNewElemVisible;

  //SelectCB variables
  static FdObject *pickedObject;
  static int pickedElemDetail;
  static int pickedPortNumber;
  static int lineDetail;

  //Line variables
  static FdCtrlElement *startLineElem;
  static FdCtrlElement *endLineElem;
  static int point;

  //Move group variables
  static std::vector<FdCtrlElement*> selectedElements;
  static std::vector<SbVec3f>        elemTransArray;
};

#endif
