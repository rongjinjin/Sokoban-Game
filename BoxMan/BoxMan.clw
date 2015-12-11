; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSelectDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "BoxMan.h"

ClassCount=5
Class1=CBoxManApp
Class2=CBoxManDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_SELECT_DLG
Resource2=IDR_MAINFRAME
Resource3=IDD_HELP_DLG
Resource4=IDD_ABOUTBOX
Class4=CHelpDlg
Resource5=IDD_BOXMAN_DIALOG
Class5=CSelectDlg
Resource6=MAIN_MENU

[CLS:CBoxManApp]
Type=0
HeaderFile=BoxMan.h
ImplementationFile=BoxMan.cpp
Filter=N

[CLS:CBoxManDlg]
Type=0
HeaderFile=BoxManDlg.h
ImplementationFile=BoxManDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDR_SELECT_LEVEL

[CLS:CAboutDlg]
Type=0
HeaderFile=BoxManDlg.h
ImplementationFile=BoxManDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_BOXMAN_DIALOG]
Type=1
Class=CBoxManDlg
ControlCount=0

[MNU:MAIN_MENU]
Type=1
Class=?
Command1=IDR_START_GAME
Command2=IDR_EXIT_GAME
Command3=IDR_SELECT_LEVEL
Command4=IDR_PLAY_MUSIC
Command5=IDR_HELP
Command6=IDR_ABOUT
CommandCount=6

[DLG:IDD_HELP_DLG]
Type=1
Class=CHelpDlg
ControlCount=3
Control1=65535,button,1342177287
Control2=65535,static,1342308352
Control3=IDOK,button,1342242816

[CLS:CHelpDlg]
Type=0
HeaderFile=HelpDlg.h
ImplementationFile=HelpDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=65535
VirtualFilter=dWC

[DLG:IDD_SELECT_DLG]
Type=1
Class=CSelectDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308864
Control3=IDC_LEVEL,edit,1350639745

[CLS:CSelectDlg]
Type=0
HeaderFile=SelectDlg.h
ImplementationFile=SelectDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSelectDlg
VirtualFilter=dWC

