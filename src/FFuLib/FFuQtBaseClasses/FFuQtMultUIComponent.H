// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_MULT_UI_COMPONENT_H
#define FFU_QT_MULT_UI_COMPONENT_H

#include "FFuLib/FFuQtBaseClasses/FFuQtComponentBase.H"
#include "FFuLib/FFuBase/FFuMultUIComponent.H"

#include <QWidget>

class QEvent;
class QResizeEvent;


class FFuQtMultUIComponent : public QWidget, virtual public FFuMultUIComponent,
			     public FFuQtComponentBase
{
public:
  // The default constructor should only be used
  // by the temporary motif UIComponent class
  FFuQtMultUIComponent() { this->setWidget(this); }

  // The window flags argument f can be set to customize
  // the window frame of a top-level widget (i.e. parent must be NULL).
  FFuQtMultUIComponent(QWidget* parent,
                       const char* name,
                       Qt::WindowFlags f = Qt::Widget);
  FFuQtMultUIComponent(QWidget* parent,
		       int xpos = 100, int ypos  = 100,
		       int width= 100, int height= 100,
		       const char* name = "FFuQtMultUIComponent",
		       Qt::WindowFlags f = Qt::Widget);
  virtual ~FFuQtMultUIComponent() {}

protected:
  virtual bool event(QEvent* e);
  virtual void setVisible(bool visible);

private:
  virtual void resizeEvent(QResizeEvent* e);
};

#endif
