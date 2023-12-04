# SPDX-FileCopyrightText: 2023 SAP SE
#
# SPDX-License-Identifier: Apache-2.0
#
# This file is part of FEDEM - https://openfedem.org

set ( SUBFOLDER_LIST components )

if ( BUILD_FWP )
  list ( APPEND SUBFOLDER_LIST inputTables mvcModels )
endif ( BUILD_FWP )

foreach ( FOLDER ${SUBFOLDER_LIST} )
  add_subdirectory ( ${FOLDER} )
endforeach ( FOLDER ${SUBFOLDER_LIST} )
