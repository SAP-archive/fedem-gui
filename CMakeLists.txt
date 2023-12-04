# SPDX-FileCopyrightText: 2023 SAP SE
#
# SPDX-License-Identifier: Apache-2.0
#
# This file is part of FEDEM - https://openfedem.org

################################################################################
# This is the top-level cmake project file for the Fedem GUI sources.
################################################################################

cmake_minimum_required ( VERSION 2.8...3.5 )

# Project setup

set ( APPLICATION_ID fedemGui )
set ( DOMAIN_ID FEDEM )
set ( PACKAGE_ID GUI )

option ( BUILD_FWP   "Build Fedem GUI with Windpower support" OFF )
option ( USE_SOLVERS "Build Fedem GUI with solver support" ON )
option ( USE_FORTRAN "Build Fedem GUI with the Fortran library" OFF )
option ( USE_CHSHAPE "Use the ChainShape library for mooring line calculation" ON )
option ( USE_MEMPOOL "Use memory pool for heap allocation in FE library" ON )
option ( USE_PROFILER "Use CPU and Memory profiler" OFF )
mark_as_advanced ( BUILD_FWP USE_FORTRAN USE_CHSHAPE USE_MEMPOOL USE_PROFILER )

if ( USE_FORTRAN )
  project ( ${APPLICATION_ID} CXX C Fortran )
else ( USE_FORTRAN )
  project ( ${APPLICATION_ID} CXX C )
endif ( USE_FORTRAN )
message ( STATUS "Generating build project for ${PROJECT_SOURCE_DIR}" )

set ( MDB_DIR ${PROJECT_SOURCE_DIR}/fedem-mdb )

find_path ( _MODULES FedemConfig.cmake
            PATHS $ENV{CMAKE_MODULES}
            "${MDB_DIR}/fedem-foundation/cmake/Modules/"
          )
if ( _MODULES )
  message ( STATUS "NOTE : Using ${_MODULES}" )
  list ( APPEND CMAKE_MODULE_PATH ${_MODULES} )
else ( _MODULES )
  message ( STATUS "ERROR : Missing path to FedemConfig.cmake" )
  message ( FATAL_ERROR "Set environment variable CMAKE_MODULES and try again" )
endif ( _MODULES )
set ( _MODULES "${PROJECT_SOURCE_DIR}/cmake/Modules" )
if ( WIN32 AND IS_DIRECTORY ${_MODULES} )
  message ( STATUS "NOTE : Using ${_MODULES}" )
  list ( APPEND CMAKE_MODULE_PATH ${_MODULES} )
endif ( WIN32 AND IS_DIRECTORY ${_MODULES} )
unset ( _MODULES CACHE )

include ( FedemConfig )

add_subdirectory ( src )
