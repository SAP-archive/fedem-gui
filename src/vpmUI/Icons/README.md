<!---
  SPDX-FileCopyrightText: 2023 SAP SE

  SPDX-License-Identifier: Apache-2.0

  This file is part of FEDEM - https://openfedem.org
--->

# Creating Icon Pixmaps

## Drawing pixmaps

Pixmaps can be drawn using different image editing tools (xpaint, IconEdit,
Photoshop, etc.). However, before the pixmaps can be used, they need to be
"standarized" both in size and type:

The normal pixmap size for icons is 16x16 pixels and 6-12 colors from
a standard pallette. The files should be saved as .xpm files, either directly
or by using, e.g., ImageMagic.

Artistic considerations is of course important, but is not covered here.

## Adding the pixmaps to the application

* Step 1: Defining the name. Each unique pixmap has it's own variable name
  in global scope (ugly, but true). This is defined in the second line of the
  xpm-file, and should have the form
```
  /* XPM */
  static const char* erase_xpm[] = {
  /* columns rows colors chars-per-pixel */
  "16 16 12 1",
  "  c gray0",
    ... };
```
  The file should be saved as <command>.xpm, in this case `erase.xpm`.

* Step 2: Adding to the forward declaration file.
  The newly defined variable should be declared in the file
  `FuiIconPixmaps.H`, in the form:
  ```
  extern const char* erase_xpm[];
  ```

* Step 3: Adding to the main include file.
  The file defining the icon should be included in the file
  `FuiIconPixmapsMain.H`, in the following form:
```
  #include "erase.xpm"
```
