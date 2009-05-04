; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{5B0D20D7-AA12-4FC8-9A4A-AF722F430738}
AppName=EOS Camera Movie Record
AppVerName=EOS Camera Movie Record 0.1.8 Beta 2
AppPublisher=Chernov A.A.
AppPublisherURL=http://valexvir.narod.ru/
AppSupportURL=http://valexvir.narod.ru/
AppUpdatesURL=http://valexvir.narod.ru/
DefaultDirName={pf}\eos_movrec
DefaultGroupName=EOS Camera Movie Record
AllowNoIcons=yes
OutputDir=dist
OutputBaseFilename=eos_movrec-0.1.8_beta2-setup
Compression=lzma
SolidCompression=yes

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "D:\develop\mingw\eos_movrec\dist\eos_movrec\DPPDLL.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\develop\mingw\eos_movrec\dist\eos_movrec\DPPLibCom.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\develop\mingw\eos_movrec\dist\eos_movrec\DPPRSC.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\develop\mingw\eos_movrec\dist\eos_movrec\EDSDK.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\develop\mingw\eos_movrec\dist\eos_movrec\EdsImage.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\develop\mingw\eos_movrec\dist\eos_movrec\eos_movrec.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\develop\mingw\eos_movrec\dist\eos_movrec\libjpeg-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\develop\mingw\eos_movrec\dist\eos_movrec\libpng-3.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\develop\mingw\eos_movrec\dist\eos_movrec\mingwm10.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\develop\mingw\eos_movrec\dist\eos_movrec\MLib.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\develop\mingw\eos_movrec\dist\eos_movrec\qt.conf"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\develop\mingw\eos_movrec\dist\eos_movrec\QtCore4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\develop\mingw\eos_movrec\dist\eos_movrec\QtGui4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\develop\mingw\eos_movrec\dist\eos_movrec\Ucs32P.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\develop\mingw\eos_movrec\dist\eos_movrec\libz-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\develop\mingw\eos_movrec\dist\eos_movrec\plugins\imageformats\qjpeg4.dll"; DestDir: "{app}\plugins\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\develop\mingw\eos_movrec\dist\eos_movrec\License.txt"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\EOS Camera Movie Record"; Filename: "{app}\eos_movrec.exe"
Name: "{group}\{cm:ProgramOnTheWeb,EOS Camera Movie Record}"; Filename: "http://valexvir.narod.ru/"
Name: "{group}\{cm:UninstallProgram,EOS Camera Movie Record}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\EOS Camera Movie Record"; Filename: "{app}\eos_movrec.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\eos_movrec.exe"; Description: "{cm:LaunchProgram,EOS Camera Movie Record}"; Flags: nowait postinstall skipifsilent

