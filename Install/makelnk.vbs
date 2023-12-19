' SPDX-FileCopyrightText: 2023 SAP SE
'
' SPDX-License-Identifier: Apache-2.0
'
' This file is part of FEDEM - https://openfedem.org

' Create a desktop shortcut
Set WSSh = wScript.CreateObject("WScript.Shell")
FVersion = wScript.Arguments(0)
userHome = WSSh.ExpandEnvironmentStrings("%USERPROFILE%")
linkFile = userHome & "\Desktop\Fedem.lnk"
' If the output file already exists, delete it
Set FSys = CreateObject("Scripting.FileSystemObject")
If FSys.FileExists(linkFile) Then
  FSys.DeleteFile(linkFile)
End If
' Create the new link
Set link = WSSh.CreateShortcut(linkFile)
link.Description      = "Fedem GUI " & FVersion
link.TargetPath       = "C:\Program Files\SAP\Fedem-" & FVersion & "\Fedem.exe"
link.WorkingDirectory = userHome
link.Save
Set Fsys = Nothing
Set WSSh = Nothing
