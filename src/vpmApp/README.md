<!---
  SPDX-FileCopyrightText: 2023 SAP SE

  SPDX-License-Identifier: Apache-2.0

  This file is part of FEDEM - https://openfedem.org
--->

# Working with the application framework

## Creating a command

The command structure in Fedem is based on function callbacks
contained in "Command Items" (`FFuaCmdItem`). These command containers
store icons, text, tool-tips, sensitivity callbacks and invoke callbacks.

## Adding a new command

A new command should be added in the file-context where it is easy
to find it for later references. See the different classes that inherit
`FapCmdBase` for examples.

In the selected file, add the invoke callback command and the
sensitivity check command:

```
  class FapDBCreateCmds : public FapCmdsBase
  {
  private:
    ...
    static void createGenericDBObject();
    static void getCreateGenericDBObjectSensitivity(bool& sensitivity);
    ...
  };
```

The sensitivity command is used to check if the button/command should
be selectable or greyed out. The checks usually are if there is results,
if the application is in a certain mode, etc.

In the implementation file, a few updates is needed:

* Step 1: Initialization.
  Each new command item should be initialized in the `init()` method in the implementation file:
```
  cmdItem = new FFuaCmdItem("cmdId_dBCreate_GenericDBObject");
  cmdItem->setSmallIcon(generic_xpm);
  cmdItem->setText("Generic DB Object");
  cmdItem->setToolTip("Create a Generic DB Object");
  cmdItem->setActivatedCB(FFaDynCB0S(FapDBCreateCmds::createGenericDBObject));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapDBCreateCmds::getCreateGenericDBObjectSensitivity,bool&));
```
  The connection between the initialization and the callback/sensitivity commands are the
  `set[...]CB` methods. These ensure that when a commandItem is invoked (either from the
  menuBar, right-mouse-click or keyboard shortcut), the correct action is taken.
  Note: The `setSmallIcon` initialization is used when you have a pixmap for the icon.
  The icon is needed when the command is going to be in a toolbar,
  but as long as it only stays in menu-bars, it is not needed.

* Step 2: Implement callbacks.
  The callback methods are implemented in the .C file,
  and for the Generic DB object, this is quite easy:
```
  void FapDBCreateCmds::createGenericDBObject()
  {
    FmGenericDBObject* obj = new FmGenericDBObject();
    obj->connect();
    FapDBCreateCmds::updateUI(obj);
  }

  void FapDBCreateCmds::getCreateGenericDBObjectSensitivity(bool& sensitivity)
  {
    sensitivity = FapCmdsBase::isModelEditable();
  }
```

Other commands may be more advanced, and the existing implementations can be used as examples.
