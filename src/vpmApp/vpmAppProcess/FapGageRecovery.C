// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppProcess/FapGageRecovery.H"
#include "vpmApp/vpmAppProcess/FapSolverID.H"

#include "vpmDB/FmDB.H"
#include "vpmDB/FmFileSys.H"
#include "vpmDB/FmAnalysis.H"
#include "vpmDB/FmGageOptions.H"
#include "vpmDB/FmStrainRosette.H"
#include "vpmDB/FmMechanism.H"
#include "vpmDB/FmPart.H"

#include "FFaLib/FFaCmdLineArg/FFaOptionFileCreator.H"
#include "FFaLib/FFaOS/FFaFilePath.H"
#include "FFaLib/FFaDefinitions/FFaMsg.H"


/*! fedem_gage options:
  -Bmatfile                      Name of B-matrix file
  -Bramsize                      In-core size (MB) of displacement recovery matrix
                                 < 0: Use the same as in the reducer (default)
                                 = 0: Store full matrix in core
  -binSize                       Bin size for stress cycle counting [MPa]
  -consolemsg                    Output error messages to console
  -cwd                           Change working directory
  -dac_sampleinc                 Sampling increment for dac output files
  -debug                         Debug print switch
  -deformation                   Save nodal deformations to results database
  -dispfile                      Name of gravitation displacement file
  -eigfile                       Name of eigenvector file
  -fao                           Read additional options from this file
  -fatigue                       Perform damage calculation on the gage stresses
  -fco                           Read calculation options from this file
  -flushinc                      Time between each database file flush
                                 < 0.0: Do not flush results database (let the OS decide)
                                 = 0.0: Flush at each time step, no external buffers
                                 > 0.0: Flush at specified time interval, use external buffers
  -fop                           Read output options from this file
  -frsfile                       Name of solver results database file
  -fsifile                       Name of solver input file
  -gate                          Stress gate value for the damage calculation [MPa]
  -help                          Print out this help text
  -licenseinfo                   Print out license information at startup
  -licensepath                   License file directory
  -linkId                        Part base-ID number
  -linkfile                      Name of part input file
  -littleEndian                  Use Little Endian formatting of DAC files
  -nullify_start_rosettestrains  Set start strains to zero for the rosettes
  -rdbfile                       Name of strain gage results database file
  -rdbinc                        Increment number for the results database file
  -resfile                       Name of result output file
  -rosfile                       Name of strain rosette input file
  -samfile                       Name of SAM data file
  -statm                         Start time
  -stotm                         Stop time
  -stressToMPaScale              Scale factor to convert stresses to MPa
  -terminal                      File unit number for terminal output
  -tinc                          Time increment (= 0.0: process all time steps)
  -version                       Print out program version
  -writeAsciiFiles               Write rosette results to ASCII files
*/


FapGageRecovery::FapGageRecovery(FmPart* aPart, FmSimulationEvent* event,
				 bool preBatch)
  : FapRecoveryBase(aPart,event)
{
  mySolverName = "fedem_gage";
  mySubTask = "timehist_gage_rcy";
  myGroupID = FapSolverID::FAP_GAGE;
  amIPreparingForBatch = preBatch;
}


int FapGageRecovery::createInput(std::string& rdbPath)
{
#ifdef FAP_DEBUG
  std::cout <<"FapGageRecovery::createInput()"<< std::endl;
#endif

  // Check if this part has any strain rosettes
  if (!myWorkPart->hasStrainRosettes())
  {
    ListUI <<"===> "<< myWorkPart->getIdString(true)
           <<" does not have any strain rosettes.\n";
    return FAP_RESULTS_OK;
  }

  // Check the dependencies for this part
  int depVal = this->checkDependencies();
  if (depVal != FAP_READY_TO_RUN)
    return depVal;

  // Get paths to all directories accessed by this process
  std::string mechRDBPath, partPath;
  if (!this->getInputAndRunDirs(mechRDBPath,&partPath,&rdbPath))
  {
    FFaMsg::dialog("Failed to set up directory structure for recovery process.\n"
                   "Check Output List for details.",FFaMsg::ERROR);
    return FAP_NOT_EXECUTABLE;
  }

  std::string partFile = this->getFEDataFile(partPath);
  if (partFile.empty())
    return FAP_NOT_EXECUTABLE;

  // Calculation options
  FFaOptionFileCreator fcoArgs(rdbPath + mySolverName + ".fco");
  fcoArgs.add("-linkId",   myWorkPart->getBaseID());
  fcoArgs.add("-linkfile", FFaFilePath::getRelativeFilename(rdbPath, partFile));
  fcoArgs.add("-Bmatfile", FFaFilePath::getRelativeFilename(rdbPath, partPath + myWorkPart->BMatFile.getValue()));
  if (myWorkPart->nGenModes.getValue() > 0)
    fcoArgs.add("-eigfile",FFaFilePath::getRelativeFilename(rdbPath, partPath + myWorkPart->EMatFile.getValue()));
  else if (myWorkPart->nGenModes.getValue() < 0)
    fcoArgs.add("-dispfile",FFaFilePath::getRelativeFilename(rdbPath, partPath + myWorkPart->DMatFile.getValue()));
  fcoArgs.add("-samfile",  FFaFilePath::getRelativeFilename(rdbPath, partPath + myWorkPart->SAMdataFile.getValue()));
  fcoArgs.add("-fsifile",  FFaFilePath::getRelativeFilename(rdbPath, mechRDBPath + "fedem_solver.fsi"));

  // Output strain rosettes defined in the model to a solver input file
  std::string rosFile("fedem_gage.fsi");
  if (!FmStrainRosette::writeSolverFile(rdbPath+rosFile,myWorkPart))
    return FAP_NOT_EXECUTABLE;

  FmGageOptions* gage = FmDB::getGageOptions();
  fcoArgs.add("-rosfile", rosFile);
  fcoArgs.add("-frsfile", "<"+getFRSfiles("timehist_prim")+">", false);

  if (gage->fatigue.getValue())
  {
    fcoArgs.add("-fatigue", 1);
    double scale = 1.0e-6;
    if (myWorkMech->modelDatabaseUnits.getValue().convert(scale,"FORCE/AREA"))
      fcoArgs.add("-stressToMPaScale", scale);
    fcoArgs.add("-binSize", gage->binSize.getValue()*scale);
  }

  fcoArgs.writeOptFile();

  // Output options
  FFaOptionFileCreator fopArgs(rdbPath + mySolverName + ".fop");
  fopArgs.add("-resfile",mySolverName + ".res");
  fopArgs.add("-rdbfile",FFaFilePath::getBaseName(partFile,true) + ".frs");
  fopArgs.add("-rdbinc",FmFileSys::getNextIncrement(rdbPath,"frs"));
  fopArgs.add("-statm",gage->startTime.getValue());
  fopArgs.add("-stotm",gage->stopTime.getValue());
  fopArgs.add("-tinc",gage->allTimeSteps.getValue() ? 0.0 : gage->timeIncr.getValue());
  if (gage->autoDacExport.getValue())
    fopArgs.add("-dac_sampleinc", gage->dacSampleRate.getValue());
  else
    fopArgs.add("-dac_sampleinc", -1.0);

  fopArgs.writeOptFile();

  // Additional options, if any
  std::string addOptions = gage->addOptions.getValue();
  if (!addOptions.empty())
  {
    FFaOptionFileCreator faoArgs(rdbPath + mySolverName + ".fao");
    faoArgs.addComment("Additional user defined options to " + mySolverName);
    faoArgs.add(addOptions,"",false);
    faoArgs.writeOptFile();
  }

  return FAP_READY_TO_RUN;
}


int FapGageRecovery::startProcess(const std::string& rdbPath)
{
#ifdef FAP_DEBUG
  std::cout <<"FapGageRecovery::startProcess()"<< std::endl;
#endif

  return this->startRecovery("Strain Gages",rdbPath,
                             FmDB::getGageOptions()->addOptions.getValue());
}
