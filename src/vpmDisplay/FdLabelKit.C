// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmDisplay/FdConverter.H"

#include <Inventor/SoDB.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoText3.h>
#include <Inventor/nodes/SoText2.h>
#ifdef USE_SMALLCHANGE
#include <SmallChange/nodes/SmDepthBuffer.h>
#endif
#include "vpmDisplay/FdLabelKit.H"
#include "vpmDisplay/FdSymbolDefs.H"

SO_KIT_SOURCE(FdLabelKit);


void FdLabelKit::init()
{
  SO_KIT_INIT_CLASS(FdLabelKit, SoBaseKit, "BaseKit");
}

FdLabelKit::FdLabelKit()
{
  this->buildKit();
}

FdLabelKit::FdLabelKit(const std::string& text, const FaVec3& position)
{
  this->buildKit();
  this->setText(text);
  this->setPosition(position);
}

FdLabelKit::FdLabelKit(const std::string& text, const FaVec3& position,
                       const FaVec3& offset)
{
  this->buildKit();
  this->setText(text);
  myOffset = offset;
  myPosition = position;
  this->updateTranslation();
}

void FdLabelKit::buildKit()
{
  SO_KIT_CONSTRUCTOR(FdLabelKit);

  isBuiltIn = TRUE;

  SO_KIT_ADD_CATALOG_ENTRY(separator,   SoSeparator,   FALSE,
			   this,  \x0 , TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(transform,   SoTransform,   FALSE,
			   separator, \x0 , TRUE );
#ifdef USE_SMALLCHANGE
  SO_KIT_ADD_CATALOG_ENTRY(depthBuffer, SmDepthBuffer, FALSE,
			   separator, \x0 , TRUE );
#endif

  SO_KIT_ADD_CATALOG_ENTRY(text2d, SoText2, FALSE, separator, \x0, TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(text3d, SoText3, FALSE, separator, \x0, TRUE );

  SO_KIT_INIT_INSTANCE();

#ifdef USE_SMALLCHANGE
  this->setPart("depthBuffer",FdSymbolDefs::getHighlightDepthBMod());
#endif

  IAm3DText = false;
  this->setText("");
}

void FdLabelKit::setText(const std::string& text)
{
  if (IAm3DText)
    {
      SoText3* textNode = (SoText3*)(this->getPart("text3d",TRUE));
      textNode->string.setValue(text.c_str());
    }
  else
    {
      SoText2* textNode = (SoText2*)(this->getPart("text2d",TRUE));
      textNode->string.setValue(text.c_str());
    }
}

void FdLabelKit::setTo3DText(bool setTo3DText)
{
  SoText2* textNode2 = (SoText2*)(this->getPart("text2d",TRUE));
  SoText3* textNode3 = (SoText3*)(this->getPart("text3d",TRUE));

  if (setTo3DText && !IAm3DText)
    {
      textNode3->string.setValue(textNode2->string[0]);
      this->setPart("text2d", NULL);
    }
  else if (!setTo3DText && IAm3DText)
    {
      textNode2->string.setValue(textNode3->string[0]);
      this->setPart("text3d", NULL);
    }
}

void FdLabelKit::setOffset(const FaVec3& offset)
{
  myOffset = offset;
  this->updateTranslation();
}

void FdLabelKit::setPosition(const FaVec3& point)
{
  myPosition = point;
  this->updateTranslation();
}

void FdLabelKit::updateTranslation()
{
  SoTransform* xf = (SoTransform*)(this->getPart("transform", TRUE));
  xf->translation.setValue(FdConverter::toSbVec3f(myPosition + myOffset));
}
