// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Inventor/SoDB.h>
#include <Inventor/nodes/SoSeparator.h>

#include <Inventor/nodes/SoFont.h>
#include <Inventor/nodes/SoText3.h>
#include <Inventor/nodes/SoText2.h>
#include <Inventor/nodes/SoTransform.h>

#include "vpmDisplay/FdAppearanceKit.H"
#include "vpmDisplay/FdCtrlElemKit.H"
#include "vpmDisplay/FdCtrlSymbolKit.H"
#include "vpmDisplay/FdBackPointer.H"

SO_KIT_SOURCE(FdCtrlElemKit);


FdCtrlElemKit::FdCtrlElemKit()
{
  SO_KIT_CONSTRUCTOR(FdCtrlElemKit);

  isBuiltIn = TRUE;

  SO_KIT_ADD_CATALOG_ENTRY(elemSep,     SoSeparator,     TRUE, this,     \x0 ,TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(appearance,  FdAppearanceKit, TRUE, elemSep,  \x0 ,TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(elemTrans,   SoTransform,     TRUE, elemSep,  \x0 ,TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(body,        FdCtrlSymbolKit, TRUE, elemSep,  \x0 ,TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(textRotation,SoTransform,     TRUE, elemSep,  \x0 ,TRUE );

  SO_KIT_ADD_CATALOG_ENTRY(textSep,     SoSeparator,     TRUE, elemSep,  \x0 ,TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(textFont,    SoFont,          TRUE, textSep,  \x0 ,TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(textTrans,   SoTransform,     TRUE, textSep,  \x0 ,TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(text,        SoText3,         TRUE, textSep,  \x0 ,TRUE );

  SO_KIT_ADD_CATALOG_ENTRY(moreText,    SoSeparator,     TRUE, elemSep,  \x0 ,TRUE );

  SO_KIT_ADD_CATALOG_ENTRY(backPt,      FdBackPointer,   TRUE, elemSep,  \x0 ,TRUE );

  SO_KIT_INIT_INSTANCE();
}


void FdCtrlElemKit::init()
{
  SO_KIT_INIT_CLASS(FdCtrlElemKit, SoBaseKit, "BaseKit");
}


void* FdCtrlElemKit::addText(const std::string& someText, float x, float y,
                             const std::string& justification,
                             const std::string& fontname,
                             float size, bool is3DText)
{
  static std::string staticText;

  staticText = someText;
  SoSeparator* sep = new SoSeparator;

  // Text position.

  SoTransform* textTransform = new SoTransform;
  textTransform->translation.setValue(SbVec3f(x,y,0.0f));
  sep->addChild(textTransform);

  // Element text font.

  SoFont* font = new SoFont;
  font->name.setValue(fontname.c_str());
  font->size.setValue(size);
  sep->addChild(font);

  // Element text.

  if (is3DText)
    {
      SoText3* elemText = new SoText3;
      elemText->justification.setValue(justification.c_str());
      elemText->string.setValue(staticText.c_str());
      sep->addChild(elemText);
    }
  else
    {
      SoText2* elemText = new SoText2;
      elemText->justification.setValue(justification.c_str());
      elemText->string.setValue(staticText.c_str());
    }

  SO_GET_PART(this,"moreText",SoSeparator)->addChild(sep);
  return sep;
}


void FdCtrlElemKit::removeText(void* id)
{
  SO_GET_PART(this,"moreText",SoSeparator)->removeChild((SoNode*)id);
}
