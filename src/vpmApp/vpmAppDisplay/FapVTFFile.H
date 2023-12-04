// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_VTF_FILE_H
#define FAP_VTF_FILE_H

#include "vpmDB/FmVTFType.H"
#include <string>
#include <vector>
#include <map>

class FmLink;
class FaVec3;
class FaMat34;
class VTFAFile;
class VTFAStateInfoBlock;
class VTFATransformationBlock;
class VTFADisplacementBlock;
class VTFAScalarBlock;


struct FapExpProp
{
  bool deformation;
  bool modeShape;
  bool fringe;
  std::pair<double,double> range;
  FapExpProp() { deformation = modeShape = fringe = false; }
};


class FapVTFFile
{
public:
  FapVTFFile() { myFile = 0; myInfo = 0; myTrans = 0; myDispl = 0; myScalar = 0;
                 iBlock = 0; iStep = 0; }
  FapVTFFile(const std::string& fName, VTFFileType type) { this->open(fName,type); }
  ~FapVTFFile() { this->close(); }

  bool open(const std::string& fileName, VTFFileType fileFormat);
  bool close();

  bool writeGeometry(const std::vector<FmLink*>& links,
                     bool writeFEdata = true, bool convTo1stOrder = false);
  bool writeProperties(const FapExpProp& prop = FapExpProp());

  bool writeStep(int stepNo, double time);
  bool writeTransformations(const std::map<int,FaMat34>& mxs);
  bool writeDeformations(int nodeBlockID, const std::vector<FaVec3>& dis);
  bool writeFringes(int neBlockID, const std::vector<double>& values,
                    const std::string& name, bool elmResults = false);
  bool writeFringes(int neBlockID,
                    const std::vector< std::vector<double> >& values,
                    const std::string& name, bool convTo1stOrder = false);

  const std::vector<int>& get1stOrderNodes(int partID) const;

private:
  VTFAFile*                myFile;
  VTFAStateInfoBlock*      myInfo;
  VTFATransformationBlock* myTrans;
  VTFADisplacementBlock*   myDispl;
  VTFAScalarBlock*         myScalar;

  VTFFileType myFormat;
  std::vector<int> myParts;

  std::map< int,std::vector<int> > myElmOrder;
  std::map< int,std::vector<int> > my1stOrdNodes;

  int iBlock;
  int iStep;
};

#endif
