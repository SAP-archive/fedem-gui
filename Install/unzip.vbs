' SPDX-FileCopyrightText: 2023 SAP SE
'
' SPDX-License-Identifier: Apache-2.0
'
' This file is part of FEDEM - https://openfedem.org

' Get command-line arguments
Set objArgs  = wScript.Arguments
Set FileSys  = CreateObject("Scripting.FileSystemObject")
InputZipFile = FileSys.GetAbsolutePathName(objArgs(0))
OutputFolder = FileSys.GetAbsolutePathName(objArgs(1))
' If the extraction location does not exist, create it
If NOT FileSys.FolderExists(OutputFolder) Then
  FileSys.CreateFolder(OutputFolder)
End If
' Extract the contents of the zip file
set objShell = CreateObject("Shell.Application")
set AllFiles = objShell.NameSpace(InputZipFile).items
objShell.NameSpace(OutputFolder).CopyHere(AllFiles)
Set FileSys  = Nothing
Set objShell = Nothing
