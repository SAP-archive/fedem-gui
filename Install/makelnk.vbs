' SPDX-FileCopyrightText: 2023 SAP SE
'
' SPDX-License-Identifier: Apache-2.0
'
' This file is part of FEDEM - https://openfedem.org

Set WSSh = wScript.CreateObject("WScript.Shell")
FVersion = wScript.Arguments(0)
instHome = wScript.Arguments(1)
linkType = wScript.Arguments(2)
userHome = WSSh.ExpandEnvironmentStrings("%USERPROFILE%")
If linkType = "D" Then
' Create Desktop shortcut
  linkFile = userHome & "\Desktop\Fedem.lnk"
Else
' Create Start menu shortcut
  appData = WSSh.ExpandEnvironmentStrings("%APPDATA%")
  startDir = appData & "\Microsoft\Windows\Start Menu\Programs"
  ' Define the location of the shortcut
  linkFile = startDir & "\Fedem.lnk"
End If
' If the output file already exists, delete it
Set FSys = CreateObject("Scripting.FileSystemObject")
If FSys.FileExists(linkFile) Then
  FSys.DeleteFile(linkFile)
End If
' Create the new link
Set link = WSSh.CreateShortcut(linkFile)
link.Description      = "Fedem R" & FVersion
link.TargetPath       = instHome & "\Fedem.exe"
link.WorkingDirectory = userHome
link.Save
Set Fsys = Nothing
Set WSSh = Nothing
