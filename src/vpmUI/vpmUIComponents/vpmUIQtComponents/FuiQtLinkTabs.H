// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_LINK_TABS_H
#define FUI_QT_LINK_TABS_H

#include "vpmUI/vpmUIComponents/FuiLinkTabs.H"
#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"

class FuiQtLinkModelSheet : public FFuQtMultUIComponent,
			    public FuiLinkModelSheet
{
 public:
  FuiQtLinkModelSheet(QWidget* parent=0, const char* name = "FuiQtLinkModelSheet");
  virtual ~FuiQtLinkModelSheet() {}

 private:
  virtual void setSensitivity(bool isSensitive)
  {FuiLinkModelSheet::setSensitivity(isSensitive);}
};

class FuiQtLinkOriginSheet : public FFuQtMultUIComponent,
			     public FuiLinkOriginSheet
{
 public:
  FuiQtLinkOriginSheet(QWidget* parent=0, const char* name="FuiQtLinkOriginSheet");
  virtual ~FuiQtLinkOriginSheet() {}

 private:
  virtual void setSensitivity(bool isSensitive)
  {FuiLinkOriginSheet::setSensitivity(isSensitive);}
};

class FuiQtLinkNodeSheet : public FFuQtMultUIComponent,
			   public FuiLinkNodeSheet
{
 public:
  FuiQtLinkNodeSheet(QWidget* parent=0, const char* name="FuiQtLinkNodeSheet");
  virtual ~FuiQtLinkNodeSheet() {}
};

class FuiQtLinkRedOptSheet : public FFuQtMultUIComponent,
			     public FuiLinkRedOptSheet
{
 public:
  FuiQtLinkRedOptSheet(QWidget* parent=0, const char* name="FuiQtLinkRedOptSheet");
  virtual ~FuiQtLinkRedOptSheet() {}

 private:
  virtual void setSensitivity(bool isSensitive)
  {FuiLinkRedOptSheet::setSensitivity(isSensitive);}
};

class FuiQtLinkLoadSheet : public FFuQtMultUIComponent,
			   public FuiLinkLoadSheet
{
 public:
  FuiQtLinkLoadSheet(QWidget* parent=0, const char* name="FuiQtLinkLoadSheet");
  virtual ~FuiQtLinkLoadSheet() {}

 protected:
  virtual void setNoLoadCases(unsigned int nlc);

 private:
  virtual void setSensitivity(bool isSensitive)
  {FuiLinkLoadSheet::setSensitivity(isSensitive);}
};

class FuiQtGenericPartCGSheet : public FFuQtMultUIComponent,
				public FuiGenericPartCGSheet
{
 public:
  FuiQtGenericPartCGSheet(QWidget* parent=0, const char* name="FuiQtGenericPartCGSheet");
  virtual ~FuiQtGenericPartCGSheet() {}

 private:
  virtual void setSensitivity(bool isSensitive)
  {FuiGenericPartCGSheet::setSensitivity(isSensitive);}
};

class FuiQtGenericPartMassSheet : public FFuQtMultUIComponent,
				  public FuiGenericPartMassSheet
{
 public:
  FuiQtGenericPartMassSheet(QWidget* parent=0, const char* name="FuiQtGenericPartMassSheet");
  virtual ~FuiQtGenericPartMassSheet() {}

 private:
  virtual void setSensitivity(bool isSensitive)
  {FuiGenericPartMassSheet::setSensitivity(isSensitive);}
};

class FuiQtGenericPartStiffSheet : public FFuQtMultUIComponent,
				   public FuiGenericPartStiffSheet
{
 public:
  FuiQtGenericPartStiffSheet(QWidget* parent=0, const char* name="FuiQtGenericPartStiffSheet");
  virtual ~FuiQtGenericPartStiffSheet() {}

 private:
  virtual void setSensitivity(bool isSensitive)
  {FuiGenericPartStiffSheet::setSensitivity(isSensitive);}
};

class FuiQtHydrodynamicsSheet : public FFuQtMultUIComponent,
				public FuiHydrodynamicsSheet
{
 public:
  FuiQtHydrodynamicsSheet(QWidget* parent=0, const char* name="FuiQtHydrodynamicsSheet");
  virtual ~FuiQtHydrodynamicsSheet() {}

 private:
  virtual void setSensitivity(bool isSensitive)
  {FuiHydrodynamicsSheet::setSensitivity(isSensitive);}
};

class FuiQtMeshingSheet : public FFuQtMultUIComponent,
			  public FuiMeshingSheet
{
 public:
  FuiQtMeshingSheet(QWidget* parent=0, const char* name="FuiQtMeshingSheet");
  virtual ~FuiQtMeshingSheet() {}

 private:
  virtual void setSensitivity(bool isSensitive)
  {FuiMeshingSheet::setSensitivity(isSensitive);}
};

class FuiQtAdvancedLinkOptsSheet : public FFuQtMultUIComponent,
				   public FuiAdvancedLinkOptsSheet
{
 public:
  FuiQtAdvancedLinkOptsSheet(QWidget* parent=0, const char* name="FuiQtAdvancedLinkOptsSheet");
  virtual ~FuiQtAdvancedLinkOptsSheet() {}

 private:
  virtual void setSensitivity(bool isSensitive)
  {FuiAdvancedLinkOptsSheet::setSensitivity(isSensitive);}
};

class FuiQtNonlinearLinkOptsSheet : public FFuQtMultUIComponent,
				    public FuiNonlinearLinkOptsSheet
{
 public:
  FuiQtNonlinearLinkOptsSheet(QWidget* parent=0, const char* name="FuiQtNonlinearLinkOptsSheet");
  virtual ~FuiQtNonlinearLinkOptsSheet() {}

 private:
  virtual void setSensitivity(bool isSensitive)
  {FuiNonlinearLinkOptsSheet::setSensitivity(isSensitive);}
};

#endif
