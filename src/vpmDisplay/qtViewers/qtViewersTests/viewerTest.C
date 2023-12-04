// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <QApplication>

#include "vpmDisplay/qtViewers/FdQtViewer.H"
#include "SoQtRenderArea.H"
#include "SoQt.H"

#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoText3.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoRotationXYZ.h>
#include <Inventor/sensors/SoTimerSensor.h>
//#include <Inventor/engines/SoTimeCounter.h>
//#include <Inventor/lock/SoLockMgr.h>


void timerCB(void* aXf, SoSensor*)
{
  static float angle = 0.0f;
  angle += 0.1f;
  ((SoRotationXYZ*)aXf)->angle.setValue(angle);
}


int main(int argc, char** argv)
{
  QApplication* a = new QApplication(argc,argv);
  SoQt::init();

  SoSeparator* root = new SoSeparator;
  root->ref();

  // Add a camera, light, and material
  SoPerspectiveCamera* myCamera = new SoPerspectiveCamera;
  root->addChild(myCamera);
  root->addChild(new SoDirectionalLight);

  //SoTimeCounter* eng = new SoTimeCounter;
  //xf->angle.connectFrom(&(eng->output));

  SoMaterial* myMaterial = new SoMaterial;
  myMaterial->diffuseColor.setValue(1.0,0.0,0.0);
  root->addChild(myMaterial);

  // Create a Text3 object, and connect to the realTime field
  SoText3* myText = new SoText3;
  myText->string.connectFrom(SoDB::getGlobalField("realTime"));
  root->addChild(myText);

  SoRotationXYZ* xf = new SoRotationXYZ;
  root->addChild(xf);
  root->addChild(new SoCone);

  SoTimerSensor aSensor(timerCB,(void*)xf);
  aSensor.setInterval(SbTime(2.0));
  aSensor.schedule();
  //SoQtRenderArea* myRenderArea = new SoQtRenderArea();
  FdQtViewer* myRenderArea = new FdQtViewer;
  myCamera->viewAll(root,myRenderArea->getSize());
  myRenderArea->setSceneGraph(root);
  myRenderArea->setTitle("Date & Time");
  myRenderArea->show();

  a->setMainWidget(myRenderArea);
  return a->exec();
}
