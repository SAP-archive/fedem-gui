<!---
  SPDX-FileCopyrightText: 2023 SAP SE

  SPDX-License-Identifier: Apache-2.0

  This file is part of FEDEM - https://openfedem.org
--->

# Open FEDEM Changelog

## [fedem-8.0.2] (2024-02-29)

### :rocket: Added

- A "Recent model" sub-menu is added in the "File" menu, from where (up to)
  the 10 last opened models in the current session can be reopened.
- If the model contains Strain Rosette elements which are used by Sensors,
  The "Perform strain rosette recovery during dynamics simulation" toggle
  is automatically enabled for FE Parts containing such Strain Rosette elements.

### :bug: Fixed

- If a template file is not available the default model name is not set and the
  current working directory is attempted cleaned with strange console messages.
- The command for opening the Users Guide is missing in the "Help" menu.
- The GUI crashes if selecting "Generic DB Object" from the "Mechanism" menu.
- The GUI crashes if an invalid expression with unbalanced parantheses
  is entered for Math Expression functions.
- The COM Type library for Fedem is missing.

## [fedem-8.0.1] (2024-01-25)

### :rocket: Added

- The "Marine" menu with hydrodynamics features is back in the GUI.

### :bug: Fixed

- Graph view shows only the first point in each curve when plotting time history results.
- Curve plotting is deactivated and Curve/Graph properties are hidden.
- Incorrect default location of file browser on "Open" and "Save As...".
- False error messages on failure to delete files when doing "Save As...".

## fedem-8.0.0 (2023-12-21)

### :rocket: Added

- First open source version of FEDEM, including GUI and solvers on Windows platform.

[fedem-8.0.1]: https://github.com/SAP/fedem-gui/compare/fedem-8.0.0...fedem-8.0.1
