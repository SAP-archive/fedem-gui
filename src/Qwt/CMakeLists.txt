# SPDX-FileCopyrightText: 2023 SAP SE
#
# SPDX-License-Identifier: Apache-2.0
#
# This file is part of FEDEM - https://openfedem.org

# Library setup

set ( LIB_ID Qwt )
set ( UNIT_ID ${DOMAIN_ID}_${PACKAGE_ID}_${LIB_ID} )

message ( STATUS "INFORMATION : Processing unit ${UNIT_ID}" )


## Files with header and source with same name
set ( COMPONENT_FILE_LIST
	src/qwt_plot_item
	src/qwt_legend_data
	src/qwt_plot_dict
	src/qwt_text
	src/qwt_plot_layout
	src/qwt_scale_map
	src/qwt_scale_div
	src/qwt_abstract_scale_draw
	src/qwt_scale_engine
	src/qwt_painter
	src/qwt_text_engine
	src/qwt_interval
	src/qwt_graphic
	src/qwt_scale_draw
	src/qwt_color_map
	src/qwt_transform
	src/qwt_null_paintdevice
	src/qwt_clipper
	src/qwt_graphic
	src/qwt_painter_command

	src/qwt_plot_grid
	src/qwt_plot_zoomer
	src/qwt_event_pattern
	src/qwt_picker
	src/qwt_plot_picker
	src/qwt_picker_machine
	src/qwt_widget_overlay
	src/qwt_plot_marker

	src/qwt_plot_curve
	src/qwt_series_data
	src/qwt_plot_seriesitem
	src/qwt_series_data
	src/qwt_point_data
	src/qwt_curve_fitter
	src/qwt_symbol
	src/qwt_point_mapper
	src/qwt_spline
	src/qwt_pixel_matrix

	src/qwt_plot
	src/qwt_scale_widget
	src/qwt_text_label
	src/qwt_legend
	src/qwt_plot_canvas
	src/qwt_abstract_legend
	src/qwt_legend_label
	src/qwt_dyngrid_layout

	src/qwt_panner
	src/qwt_plot_panner
)

## Pure header files, i.e., header files without a corresponding source file
set ( HEADER_FILE_LIST
	src/qwt
	src/qwt_global
)

## Pure implementation files, i.e., source files without corresponding header
set ( SOURCE_FILE_LIST
	src/qwt_plot_axis
)

## Header files to be moc'ed
set ( QT_MOC_HEADER_FILE_LIST
	src/qwt_dyngrid_layout
	src/qwt_legend_label
	src/qwt_plot_canvas
	src/qwt_legend
	src/qwt_scale_widget
	src/qwt_plot
	src/qwt_text_label
	src/qwt_abstract_legend
	src/qwt_plot_zoomer
	src/qwt_picker
	src/qwt_plot_picker
	src/qwt_panner
	src/qwt_plot_panner
     )


find_package ( Qt4 )
if ( Qt4_FOUND )
  include ( ${QT_USE_FILE} )

  foreach ( FILE ${QT_MOC_HEADER_FILE_LIST} )
    list ( APPEND QT_MOC_HEADER_FILES ${FILE}.h )
  endforeach ( FILE ${QT_MOC_HEADER_FILE_LIST} )

  include_directories ( ${CMAKE_CURRENT_BINARY_DIR} )
  # Named moc_<filename>.cxx where input is filname.H
  QT4_WRAP_CPP ( QT_MOC_SOURCE_FILES ${QT_MOC_HEADER_FILES} )

  foreach ( FILE ${COMPONENT_FILE_LIST} )
    list ( APPEND CPP_SOURCE_FILES ${FILE}.cpp )
    list ( APPEND HPP_HEADER_FILES ${FILE}.h )
  endforeach ( FILE ${COMPONENT_FILE_LIST} )

  foreach ( FILE ${HEADER_FILE_LIST} )
    list ( APPEND HPP_HEADER_FILES ${FILE}.h )
  endforeach ( FILE ${HEADER_FILE_LIST} )

  foreach ( FILE ${SOURCE_FILE_LIST} )
    list ( APPEND CPP_SOURCE_FILES ${FILE}.cpp )
  endforeach ( FILE ${SOURCE_FILE_LIST} )

  set ( HEADER_FILES ${HPP_HEADER_FILES} )
  set ( SOURCE_FILES ${CPP_SOURCE_FILES} ${QT_MOC_SOURCE_FILES} )

  string ( APPEND CMAKE_CXX_FLAGS " -DQWT_NO_SVG" )

  add_library ( ${LIB_ID} ${SOURCE_FILES} ${HEADER_FILES} )

else ( Qt4_FOUND )
  message ( STATUS "NOTE : Qt4 installation not found, skipping Qwt building" )
endif ( Qt4_FOUND )
