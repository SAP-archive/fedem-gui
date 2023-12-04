# SPDX-FileCopyrightText: 2023 SAP SE
#
# SPDX-License-Identifier: Apache-2.0
#
# This file is part of FEDEM - https://openfedem.org

# Builds the LIB_ID library
set ( LIB_ID FFdCadModel )

if ( WIN AND Coin_library )
  string ( APPEND CMAKE_CXX_FLAGS " -DCOIN_DLL" )
  include_directories ( "$ENV{COIN_ROOT}/include" )
endif ( WIN AND Coin_library )


## Files with header and source with same name
set ( COMPONENT_FILE_LIST FdCadHandler FdCadEdge FdCadFace
                          FdCadSolid FdCadSolidWire
    )
## Pure header files, i.e., header files without a corresponding source file
set ( HEADER_FILE_LIST FdCadInfo FFdUtils/FFdLook )
## Pure implementation files, i.e., source files without corresponding header
set ( SOURCE_FILE_LIST )


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


message ( STATUS "Building library ${LIB_ID}" )
add_library ( ${LIB_ID} ${CPP_SOURCE_FILES} ${HPP_HEADER_FILES} )
target_link_libraries ( ${LIB_ID} FFaAlgebra FFaContainers ${Coin_library} )
