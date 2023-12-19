' SPDX-FileCopyrightText: 2023 SAP SE
'
' SPDX-License-Identifier: Apache-2.0
'
' This file is part of FEDEM - https://openfedem.org

' Get command-line arguments
Set objArgs = wScript.Arguments
Set FileSys = CreateObject("Scripting.FileSystemObject")
InputFolder = FileSys.GetAbsolutePathName(objArgs(0))
OutputFile  = FileSys.GetAbsolutePathName(objArgs(1))
WaitTime    = objArgs(2)
' If the output file already exists, delete it
If FileSys.FileExists(OutputFile) Then
  FileSys.DeleteFile(OutputFile)
End If
' Create an empty ZIP file
CreateObject("Scripting.FileSystemObject").CreateTextFile(OutputFile,True).Write "PK" & Chr(5) & Chr(6) & String(18,vbNullChar)
' Put all files in the InputFolder into the ZIP file
wScript.echo "Creating",OutputFile,"with files from",InputFolder
Set csShell = CreateObject("Shell.Application")
Set sources = csShell.NameSpace(InputFolder).Items
csShell.NameSpace(OutputFile).CopyHere(sources)
' Required to let the ZIP command execute
wScript.Sleep WaitTime
Set FileSys = Nothing
Set csShell = Nothing
