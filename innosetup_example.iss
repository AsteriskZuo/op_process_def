; 脚本由 Inno Setup 脚本向导 生成！
; 有关创建 Inno Setup 脚本文件的详细资料请查阅帮助文档！
#define MyAppName "GoCom"
#define MyAppGroupName "企业融合通信平台"
#define MyAppVersion "7.4.1.478"
#define MyAppPublisher ""
#define MyAppURL ""
#define MyAppExeName "GoCom.exe"
#define MyAppDefaultPath "GoCom"
[Setup]
; 注: AppId的值为单独标识该应用程序。
; 不要为其他安装程序使用相同的AppId值。
; (生成新的GUID，点击 工具|在IDE中生成GUID。)
AppId={{65B7C0CD-E131-4B7D-B3BE-E932DFDF5025}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppDefaultPath}
DefaultGroupName={#MyAppGroupName}
OutputDir=output                                                                                                               
OutputBaseFilename=GoCom_{#MyAppVersion}
Compression=lzma
SolidCompression=yes
;WizardImageFile=gocom.bmp
;WizardSmallImageFile=gocom_s.bmp

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl" 


[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; 
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}";

[Files]
Source: "op_process_def2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\src\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "src\Resources\SEGUIEMJ_0.TTF"; DestDir: "{fonts}"; FontInstall: "Segoe UI Emoji"; Flags: onlyifdoesntexist uninsneveruninstall

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\Bin\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\Bin\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\Bin\{#MyAppExeName}"; Tasks: quicklaunchicon

[UninstallDelete]
Type: files; Name: "{app}\op_process_def2.dll"

[Run]  
;Filename: "{app}\{#ConfInstallName}"; Description: "{cm:LaunchProgram,{#StringChange(ConfName, "&", "&&")}}"; Flags: runascurrentuser skipifsilent
;Filename: "{app}\DirectX\{#ConfInstallName}"; Description:"GetWindowsVersion and $FFFF"; Check : IsWindowsXPOrLater
Filename: "{app}\Bin\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, "&", "&&")}}";  Flags: nowait postinstall skipifsilent


[Code]
function KillProcessFromNameC(pname: String; isKillTree: Boolean): Boolean;
external 'KillProcessFromNameC@files:op_process_def2.dll stdcall setuponly';

function FindProcessFromNameC(pname: String): Boolean;
external 'FindProcessFromNameC@files:op_process_def2.dll stdcall setuponly';

function KillProcessFromNameCForUninstall(pname: String; isKillTree: Boolean): Boolean;
external 'KillProcessFromNameC@{app}\op_process_def2.dll stdcall uninstallonly';

function FindProcessFromNameCForUninstall(pname: String): Boolean;
external 'FindProcessFromNameC@{app}\op_process_def2.dll stdcall uninstallonly';


{   This function is deprecated, please use the curstepchanged function.2018.05.21        }
//procedure CurInstallProgressChanged (CurProgress, MaxProgress: Integer);
//var BoostParam : String;
//begin
//  if CurProgress = MaxProgress then
//  begin
//    if RegValueExists(HKEY_CURRENT_USER, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Run', 'GoCom') then
//      begin
//        BoostParam := ExpandConstant('{app}') + '\GoCom.exe';
//        RegWriteStringValue(HKEY_CURRENT_USER, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Run', 'GoCom', BoostParam);
//      end;
//  end;
//end;



procedure CurStepChanged(CurStep: TSetupStep);
var BoostParam : String;
begin
  if CurStep = ssPostInstall then
    begin
      if RegValueExists(HKEY_CURRENT_USER, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Run', 'GoCom') then
        begin
          BoostParam := ExpandConstant('{app}') + '\GoCom.exe';
          RegWriteStringValue(HKEY_CURRENT_USER, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Run', 'GoCom', BoostParam);
        end;
    end;
end;

procedure InitializeUninstallProgressForm ();
begin
  if RegValueExists(HKEY_CURRENT_USER, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Run', 'GoCom') then
    begin
      RegDeleteValue(HKEY_CURRENT_USER, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Run', 'GoCom');
    end;
end;


const maxcount = 10;
type ExecList = array[1..maxcount] of String;
function PrepareToInstall(var NeedsRestart: Boolean): String;
var ret : Boolean;
var lt : ExecList;
var i : Integer;
begin
  lt[1] := 'CrashReporter.exe';
  lt[2] := 'CustomProtal.exe';
  lt[3] := 'EmbedExplorer.exe';
  lt[4] := 'GoCom.exe';
  lt[5] := 'GRemoteC.exe';
  lt[6] := 'GRemoteS.exe';
  lt[7] := 'Modifylnk.exe';
  lt[8] := 'Online_Update.exe';
  lt[9] := 'PseudoGoCom.exe';
  lt[10] := 'wow_helper.exe';
  for i := 1 to maxcount do
  begin
    ret := FindProcessFromNameC(lt[i]);
    if ret then
      begin
        MsgBox('Please close program ' + lt[i] + ' first.', mbConfirmation, MB_OK);
        Result := lt[i];
        break;
      end
  end;
  if i > maxcount then
    begin
      Result := '';
    end;
end;

function InitializeUninstall(): Boolean;
var ret : Boolean;
var lt : ExecList;
var i : Integer;
begin
  lt[1] := 'CrashReporter.exe';
  lt[2] := 'CustomProtal.exe';
  lt[3] := 'EmbedExplorer.exe';
  lt[4] := 'GoCom.exe';
  lt[5] := 'GRemoteC.exe';
  lt[6] := 'GRemoteS.exe';
  lt[7] := 'Modifylnk.exe';
  lt[8] := 'Online_Update.exe';
  lt[9] := 'PseudoGoCom.exe';
  lt[10] := 'wow_helper.exe';
  for i := 1 to maxcount do
  begin
    ret := FindProcessFromNameCForUninstall(lt[i]);
    if ret then
      begin
        MsgBox('Please close program ' + lt[i] + ' first.', mbConfirmation, MB_OK);
        Result := False;
        break;
      end
  end;
  if i > maxcount then
    begin
      Result := True;
      UnloadDLL(ExpandConstant('{app}\op_process_def2.dll'));
      //DeleteFile(ExpandConstant('{app}\op_process_def2.dll'));
    end;
end;












