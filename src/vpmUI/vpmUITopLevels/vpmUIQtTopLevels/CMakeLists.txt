# SPDX-FileCopyrightText: 2023 SAP SE
#
# SPDX-License-Identifier: Apache-2.0
#
# This file is part of FEDEM - https://openfedem.org

# Builds the LIB_ID library
set ( LIB_ID vpmUIQtTopLevels )

if ( USE_FORTRAN )
  string ( APPEND CMAKE_CXX_FLAGS " -DFT_HAS_PREVIEW" )
endif ( USE_FORTRAN )
if ( USE_EXT_CTRLSYS )
  string ( APPEND CMAKE_CXX_FLAGS " -DFT_HAS_EXTCTRL" )
endif ( USE_EXT_CTRLSYS )


## Files with header and source with same name
set ( COMPONENT_FILE_LIST  FuiQtAdvAnalysisOptions FuiQtAnimationControl FuiQtAnimExportSetup
                           FuiQtAppearance FuiQtCtrlModeller FuiQtCtrlGridAttributes
                           FuiQtCSSelector
                           FuiQtEigenOptions FuiQtFppOptions FuiQtGageOptions
                           FuiQtLinkRamSettings
                           FuiQtMainWindow FuiQtMiniFileBrowser FuiQtModeller
                           FuiQtModelManager FuiQtModelPreferences FuiQtOutputList
                           FuiQtPlugins FuiQtPreferences FuiQtProperties
                           FuiQtRDBSelector
                           FuiQtRepeatCurve FuiQtStressOptions FuiQtViewSettings
                           FuiQtSeaEnvironment FuiQtEventDefinition
                           FuiQtSplitBeam FuiQtCreateBeamstringPair FuiQtObjectBrowser
                           FuiQtMooringLine FuiQtModelExport )

if ( BUILD_FWP )
  list ( APPEND COMPONENT_FILE_LIST FuiQtAirEnvironment FuiQtAirfoilDefinition FuiQtBladeDefinition
                                    FuiQtCreateTurbineAssembly FuiQtCreateTurbineTower FuiQtTurbWind )
endif ( BUILD_FWP )

if ( Qwt_LIBRARY )
  list ( APPEND COMPONENT_FILE_LIST FuiQtGraphView FuiQtRDBMEFatigue )
endif ( Qwt_LIBRARY )

if ( USE_NCODE_INTERFACE )
  list ( APPEND COMPONENT_FILE_LIST FuiQtDutyCycleOptions )
endif ( USE_NCODE_INTERFACE )


## Pure header files, i.e., header files without a corresponding source file
set ( HEADER_FILE_LIST )
## Pure implementation files, i.e., source files without corresponding header
set ( SOURCE_FILE_LIST FuiQt FuiQtMsg )


foreach ( FILE ${COMPONENT_FILE_LIST} )
  set ( CPP_SOURCE_FILES ${CPP_SOURCE_FILES} ${FILE}.C )
  set ( HPP_HEADER_FILES ${HPP_HEADER_FILES} ${FILE}.H )
endforeach ( FILE ${COMPONENT_FILE_LIST} )


foreach ( FILE ${HEADER_FILE_LIST} )
  set ( HPP_HEADER_FILES ${HPP_HEADER_FILES} ${FILE}.H )
endforeach ( FILE ${HEADER_FILE_LIST} )


foreach ( FILE ${SOURCE_FILE_LIST} )
  set ( CPP_SOURCE_FILES ${CPP_SOURCE_FILES} ${FILE}.C )
endforeach ( FILE ${SOURCE_FILE_LIST} )


## Header files to be moc'ed
set ( QT_MOC_HEADER_FILE_LIST FuiQtEventDefinition FuiQtModelExport )
if ( BUILD_FWP )
  list ( APPEND QT_MOC_HEADER_FILE_LIST FuiQtAirfoilDefinition FuiQtBladeDefinition FuiQtTurbWind )
endif ( BUILD_FWP )

foreach ( FILE ${QT_MOC_HEADER_FILE_LIST} )
  set ( QT_MOC_HEADER_FILES ${QT_MOC_HEADER_FILES} ${FILE}.H )
endforeach ( FILE ${QT_MOC_HEADER_FILE_LIST} )


include_directories ( ${CMAKE_CURRENT_BINARY_DIR} )
# Named moc_<filename>.cxx where input is filname.H
QT4_WRAP_CPP ( QT_MOC_SOURCE_FILES ${QT_MOC_HEADER_FILES} )

set ( HEADER_FILES ${HPP_HEADER_FILES} )
set ( SOURCE_FILES ${CPP_SOURCE_FILES} ${QT_MOC_SOURCE_FILES} )


#
# Dependencies and system libraries
#

find_package ( Qt4 REQUIRED )
include ( ${QT_USE_FILE} )

if ( WIN AND Coin_library )
  string ( APPEND CMAKE_CXX_FLAGS " -DCOIN_DLL -DSOQT_DLL" )
  include_directories ( "$ENV{COIN_ROOT}/include" )
endif ( WIN AND Coin_library )

set ( FT_KERNEL_LIBRARIES vpmDB )
set ( FT_COMMON_LIBRARIES )
set ( FT_GUI_LIBRARIES vpmUITopLevels vpmUIQtComponents FFuQtComponents FFuQtBaseClasses FFuComponents )
if ( BUILD_FWP )
  list ( APPEND FT_GUI_LIBRARIES FFuInputTables )
endif ( BUILD_FWP )
set ( DEPENDENCY_LIST ${FT_GUI_LIBRARIES} ${FT_KERNEL_LIBRARIES} ${FT_COMMON_LIBRARIES} )

message ( STATUS "Building library ${LIB_ID}" )
add_library ( ${LIB_ID} ${SOURCE_FILES} ${HEADER_FILES} )
target_link_libraries ( ${LIB_ID} ${DEPENDENCY_LIST} )
