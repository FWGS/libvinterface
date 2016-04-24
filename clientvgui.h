#pragma once
#include "interface.h"



class IClientVGUI : public IBaseInterface {
public:
	virtual void Initialize(CreateInterfaceFn *, int) { }
	virtual void Start(void) { }
	virtual void SetParent(unsigned int) {}
	virtual bool UseVGUI1(void) {}
	virtual void HideScoreBoard(void){}
	virtual void HideAllVGUIMenu(void){}
	virtual void ActivateClientUI(void){}
	virtual void HideClientUI(void){}
	virtual void Shutdown(void){}
};

/*
class IKeyValues : public IBaseInterface {
public:
	virtual void RegisterSizeofKeyValues(int) {}
	virtual void * AllocKeyValuesMemory(int) { return 0; }
	virtual void FreeKeyValuesMemory(void *) {}
	virtual int GetSymbolForString(const char *) { return 0; }
	virtual const char * GetStringForSymbol(int) { return 0; }
	virtual void GetLocalizedFromANSI(const char *, wchar_t *, int) {}
	virtual void GetANSIFromLocalized(const wchar_t *, char *, int) {}
	virtual void AddKeyValuesToMemoryLeakList(void *, int) {}
	virtual void RemoveKeyValuesFromMemoryLeakList(void *) {}
};

class IAppSystem {};
namespace vgui2{
typedef unsigned int VPANEL;
typedef unsigned long HPanel;
typedef int HContext;
typedef unsigned long StringIndex_t;
typedef unsigned long HScheme;
typedef unsigned char Color[4];
typedef unsigned long HFont;
typedef unsigned long HCursor;
typedef unsigned long HTexture;
typedef int KeyCode;
typedef int MouseCode;

class IVGui : public IBaseInterface, public IAppSystem {
public:
	virtual bool Init(CreateInterfaceFn *, int) {}
	virtual void Shutdown(void) {}
	virtual void Start(void) {}
	virtual void Stop(void) {}
	virtual bool IsRunning(void) {}
	virtual void RunFrame(void) {}
	virtual void ShutdownMessage(unsigned int) {}
	virtual vgui2::VPANEL AllocPanel(void) {}
	virtual void FreePanel(vgui2::VPANEL) {}
	virtual void DPrintf(const char *, ...) {}
	virtual void DPrintf2(const char *, ...) {}
	virtual void SpewAllActivePanelNames(void) {}
	virtual vgui2::HPanel PanelToHandle(vgui2::VPANEL) {}
	virtual vgui2::VPANEL HandleToPanel(vgui2::HPanel) {}
	virtual void MarkPanelForDeletion(vgui2::VPANEL) {}
	virtual void AddTickSignal(vgui2::VPANEL, int) {}
	virtual void RemoveTickSignal(vgui2::VPANEL) {}
	virtual void PostMessage(vgui2::VPANEL, void *, vgui2::VPANEL, float) {}
	virtual vgui2::HContext CreateContext(void) {}
	virtual void DestroyContext(vgui2::HContext) {}
	virtual void AssociatePanelWithContext(vgui2::HContext, vgui2::VPANEL) {}
	virtual void ActivateContext(vgui2::HContext) {}
	virtual void SetSleep(bool) {}
	virtual bool GetShouldVGuiControlSleep(void) {}
};

class ILocalize : public IBaseInterface {
public:
	virtual bool AddFile(IFileSystem *, const char *) {}
	virtual void RemoveAll(void) {}
	virtual wchar_t * Find(const char *) {}
	virtual int ConvertANSIToUnicode(const char *, wchar_t *, int) {}
	virtual int ConvertUnicodeToANSI(const wchar_t *, char *, int) {}
	virtual vgui2::StringIndex_t FindIndex(const char *) {}
	virtual void ConstructString(wchar_t *, int, wchar_t *, int, ...) {}
	virtual void ConstructString(wchar_t *, int, const char *, void *) {}
	virtual void ConstructString(wchar_t *, int, vgui2::StringIndex_t, void *) {}
	virtual const char * GetNameByIndex(vgui2::StringIndex_t) {}
	virtual wchar_t * GetValueByIndex(vgui2::StringIndex_t) {}
	virtual vgui2::StringIndex_t GetFirstStringIndex(void) {}
	virtual vgui2::StringIndex_t GetNextStringIndex(vgui2::StringIndex_t) {}
	virtual void AddString(const char *, wchar_t *, const char *) {}
	virtual void SetValueByIndex(vgui2::StringIndex_t, wchar_t *) {}
	virtual bool SaveToFile(IFileSystem *, const char *) {}
	virtual int GetLocalizationFileCount(void) {}
	virtual const char * GetLocalizationFileName(int) {}
	virtual const char * GetFileNameByIndex(vgui2::StringIndex_t) {}
	virtual void ReloadLocalizationFiles(IFileSystem *) {}
};

class IPanel : public IBaseInterface {
public:
	virtual void Init(vgui2::VPANEL, void *) {}
	virtual void SetPos(vgui2::VPANEL, int, int) {}
	virtual void GetPos(vgui2::VPANEL, int &, int &) {}
	virtual void SetSize(vgui2::VPANEL, int, int) {}
	virtual void GetSize(vgui2::VPANEL, int &, int &) {}
	virtual void SetMinimumSize(vgui2::VPANEL, int, int) {}
	virtual void GetMinimumSize(vgui2::VPANEL, int &, int &) {}
	virtual void SetZPos(vgui2::VPANEL, int) {}
	virtual int GetZPos(vgui2::VPANEL) {}
	virtual void GetAbsPos(vgui2::VPANEL, int &, int &) {}
	virtual void GetClipRect(vgui2::VPANEL, int &, int &, int &, int &) {}
	virtual void SetInset(vgui2::VPANEL, int, int, int, int) {}
	virtual void GetInset(vgui2::VPANEL, int &, int &, int &, int &) {}
	virtual void SetVisible(vgui2::VPANEL, bool) {}
	virtual bool IsVisible(vgui2::VPANEL) {}
	virtual void SetParent(vgui2::VPANEL, vgui2::VPANEL) {}
	virtual int GetChildCount(vgui2::VPANEL) {}
	virtual vgui2::VPANEL GetChild(vgui2::VPANEL, int) {}
	virtual vgui2::VPANEL GetParent(vgui2::VPANEL) {}
	virtual void MoveToFront(vgui2::VPANEL) {}
	virtual void MoveToBack(vgui2::VPANEL) {}
	virtual bool HasParent(vgui2::VPANEL, vgui2::VPANEL) {}
	virtual bool IsPopup(vgui2::VPANEL) {}
	virtual void SetPopup(vgui2::VPANEL, bool) {}
	virtual bool Render_GetPopupVisible(vgui2::VPANEL) {}
	virtual void Render_SetPopupVisible(vgui2::VPANEL, bool) {}
	virtual vgui2::HScheme GetScheme(vgui2::VPANEL) {}
	virtual bool IsProportional(vgui2::VPANEL) {}
	virtual bool IsAutoDeleteSet(vgui2::VPANEL) {}
	virtual void DeletePanel(vgui2::VPANEL) {}
	virtual void SetKeyBoardInputEnabled(vgui2::VPANEL, bool) {}
	virtual void SetMouseInputEnabled(vgui2::VPANEL, bool) {}
	virtual bool IsKeyBoardInputEnabled(vgui2::VPANEL) {}
	virtual bool IsMouseInputEnabled(vgui2::VPANEL) {}
	virtual void Solve(vgui2::VPANEL) {}
	virtual const char * GetName(vgui2::VPANEL) {}
	virtual const char * GetClassName(vgui2::VPANEL) {}
	virtual void SendMessage(vgui2::VPANEL, void *, vgui2::VPANEL) {}
	virtual void Think(vgui2::VPANEL) {}
	virtual void PerformApplySchemeSettings(vgui2::VPANEL) {}
	virtual void PaintTraverse(vgui2::VPANEL, bool, bool) {}
	virtual void Repaint(vgui2::VPANEL) {}
	virtual vgui2::VPANEL IsWithinTraverse(vgui2::VPANEL, int, int, bool) {}
	virtual void OnChildAdded(vgui2::VPANEL, vgui2::VPANEL) {}
	virtual void OnSizeChanged(vgui2::VPANEL, int, int) {}
	virtual void InternalFocusChanged(vgui2::VPANEL, bool) {}
	virtual bool RequestInfo(vgui2::VPANEL, void *) {}
	virtual void RequestFocus(vgui2::VPANEL, int) {}
	virtual bool RequestFocusPrev(vgui2::VPANEL, vgui2::VPANEL) {}
	virtual bool RequestFocusNext(vgui2::VPANEL, vgui2::VPANEL) {}
	virtual vgui2::VPANEL GetCurrentKeyFocus(vgui2::VPANEL) {}
	virtual int GetTabPosition(vgui2::VPANEL) {}
	virtual void * Plat(vgui2::VPANEL) {}
	virtual void SetPlat(vgui2::VPANEL, void *) {}
	virtual void * GetPanel(vgui2::VPANEL, const char *) {}
	virtual bool IsEnabled(vgui2::VPANEL) {}
	virtual void SetEnabled(vgui2::VPANEL, bool) {}
};



class ISurface : public IBaseInterface, public IAppSystem {
public:
	virtual void Shutdown(void) {}
	virtual void RunFrame(void) {}
	virtual vgui2::VPANEL GetEmbeddedPanel(void) {}
	virtual void SetEmbeddedPanel(vgui2::VPANEL) {}
	virtual void PushMakeCurrent(vgui2::VPANEL, bool) {}
	virtual void PopMakeCurrent(vgui2::VPANEL) {}
	virtual void DrawSetColor(int, int, int, int) {}
	virtual void DrawSetColor(Color) {}
	virtual void DrawFilledRect(int, int, int, int) {}
	virtual void DrawOutlinedRect(int, int, int, int) {}
	virtual void DrawLine(int, int, int, int) {}
	virtual void DrawPolyLine(int *, int *, int) {}
	virtual void DrawSetTextFont(vgui2::HFont) {}
	virtual void DrawSetTextColor(int, int, int, int) {}
	virtual void DrawSetTextColor(Color) {}
	virtual void DrawSetTextPos(int, int) {}
	virtual void DrawGetTextPos(int &, int &) {}
	virtual void DrawPrintText(const wchar_t *, int) {}
	virtual void DrawUnicodeChar(wchar_t) {}
	virtual void DrawUnicodeCharAdd(wchar_t) {}
	virtual void DrawFlushText(void) {}
	virtual void * CreateHTMLWindow(void *, vgui2::VPANEL) {}
	virtual void PaintHTMLWindow(void *) {}
	virtual void DeleteHTMLWindow(void *) {}
	virtual void DrawSetTextureFile(int, const char *, int, bool) {}
	virtual void DrawSetTextureRGBA(int, const unsigned char *, int, int, int, bool) {}
	virtual void DrawSetTexture(int) {}
	virtual void DrawGetTextureSize(int, int &, int &) {}
	virtual void DrawTexturedRect(int, int, int, int) {}
	virtual bool IsTextureIDValid(int) {}

	virtual int CreateNewTextureID(bool) {}
	virtual void GetScreenSize(int &, int &) {}
	virtual void SetAsTopMost(vgui2::VPANEL, bool) {}
	virtual void BringToFront(vgui2::VPANEL) {}
	virtual void SetForegroundWindow(vgui2::VPANEL) {}
	virtual void SetPanelVisible(vgui2::VPANEL, bool) {}
	virtual void SetMinimized(vgui2::VPANEL, bool) {}
	virtual bool IsMinimized(vgui2::VPANEL) {}
	virtual void FlashWindow(vgui2::VPANEL, bool) {}
	virtual void SetTitle(vgui2::VPANEL, const wchar_t *) {}
	virtual void SetAsToolBar(vgui2::VPANEL, bool) {}
	virtual void CreatePopup(vgui2::VPANEL, bool, bool, bool, bool, bool) {}
	virtual void SwapBuffers(vgui2::VPANEL) {}
	virtual void Invalidate(vgui2::VPANEL) {}
	virtual void SetCursor(vgui2::HCursor) {}
	virtual bool IsCursorVisible(void) {}
	virtual void ApplyChanges(void) {}
	virtual bool IsWithin(int, int) {}
	virtual bool HasFocus(void) {}
	virtual bool SupportsFeature(int) {}
	virtual void RestrictPaintToSinglePanel(vgui2::VPANEL) {}
	virtual void SetModalPanel(vgui2::VPANEL) {}
	virtual vgui2::VPANEL GetModalPanel(void) {}
	virtual void UnlockCursor(void) {}
	virtual void LockCursor(void) {}
	virtual void SetTranslateExtendedKeys(bool) {}
	virtual vgui2::VPANEL GetTopmostPopup(void) {}
	virtual void SetTopLevelFocus(vgui2::VPANEL) {}
	virtual vgui2::HFont CreateFont(void) {}
	virtual bool AddGlyphSetToFont(vgui2::HFont, const char *, int, int, int, int, int, int, int) {}
	virtual bool AddCustomFontFile(const char *) {}
	virtual int GetFontTall(vgui2::HFont) {}

	virtual void GetCharABCwide(vgui2::HFont, int, int &, int &, int &) {}
	virtual int GetCharacterWidth(vgui2::HFont, int) {}
	virtual void GetTextSize(vgui2::HFont, const wchar_t *, int &, int &) {}
	virtual vgui2::VPANEL GetNotifyPanel(void) {}
	virtual void SetNotifyIcon(vgui2::VPANEL, vgui2::HTexture, vgui2::VPANEL, const char *) {}
	virtual void PlaySound(const char *) {}
	virtual int GetPopupCount(void) {}
	virtual vgui2::VPANEL GetPopup(int) {}
	virtual bool ShouldPaintChildPanel(vgui2::VPANEL) {}
	virtual bool RecreateContext(vgui2::VPANEL) {}
	virtual void AddPanel(vgui2::VPANEL) {}
	virtual void ReleasePanel(vgui2::VPANEL) {}
	virtual void MovePopupToFront(vgui2::VPANEL) {}
	virtual void MovePopupToBack(vgui2::VPANEL) {}
	virtual void SolveTraverse(vgui2::VPANEL, bool) {}
	virtual void PaintTraverse(vgui2::VPANEL) {}
	virtual void EnableMouseCapture(vgui2::VPANEL, bool) {}
	virtual void GetWorkspaceBounds(int &, int &, int &, int &) {}
	virtual void GetAbsoluteWindowBounds(int &, int &, int &, int &) {}
	virtual void GetProportionalBase(int &, int &) {}
	virtual void CalculateMouseVisible(void) {}
	virtual bool NeedKBInput(void) {}
	virtual bool HasCursorPosFunctions(void) {}
	virtual void SurfaceGetCursorPos(int &, int &) {}
	virtual void SurfaceSetCursorPos(int, int) {}
	virtual void DrawTexturedPolygon(void *, int) {}
	virtual int GetFontAscent(vgui2::HFont, wchar_t) {}
	virtual void SetAllowHTMLJavaScript(bool) {}
	virtual void SetLanguage(const char *) {}
	virtual const char * GetLanguage(void) {}
	virtual bool DeleteTextureByID(int) {}
	virtual void DrawUpdateRegionTextureBGRA(int, int, int, const unsigned char *, int, int) {}

	virtual void DrawSetTextureBGRA(int, const unsigned char *, int, int) {}
	virtual void CreateBrowser(vgui2::VPANEL, void *, bool, const char *) {}
	virtual void RemoveBrowser(vgui2::VPANEL, void *) {}
	virtual void * AccessChromeHTMLController(void) {}
};

class ISchemeManager : public IBaseInterface {
public:
	virtual vgui2::HScheme LoadSchemeFromFile(const char *, const char *) {}
	virtual void ReloadSchemes(void) {}
	virtual vgui2::HScheme GetDefaultScheme(void) {}
	virtual vgui2::HScheme GetScheme(const char *) {}
	virtual void * GetImage(const char *, bool) {}
	virtual vgui2::HTexture GetImageID(const char *, bool) {}
	virtual void * GetIScheme(vgui2::HScheme) {}
	virtual void Shutdown(bool) {}
	virtual int GetProportionalScaledValue(int) {}
	virtual int GetProportionalNormalizedValue(int) {}
};
class ISystem : public IBaseInterface {
public:
	virtual void Shutdown(void) {}
	virtual void RunFrame(void) {}
	virtual void ShellExecute(const char *, const char *) {}
	virtual double GetFrameTime(void) {}
	virtual double GetCurrentTime(void) {}
	virtual long GetTimeMillis(void) {}
	virtual int GetClipboardTextCount(void) {}
	virtual void SetClipboardText(const char *, int) {}
	virtual void SetClipboardText(const wchar_t *, int) {}
	virtual int GetClipboardText(int, char *, int) {}
	virtual int GetClipboardText(int, wchar_t *, int) {}
	virtual bool SetRegistryString(const char *, const char *) {}
	virtual bool GetRegistryString(const char *, char *, int) {}
	virtual bool SetRegistryInteger(const char *, int) {}
	virtual bool GetRegistryInteger(const char *, int &) {}
	virtual void * GetUserConfigFileData(const char *, int) {}
	virtual void SetUserConfigFile(const char *, const char *) {}
	virtual void SaveUserConfigFile(void) {}
	virtual bool SetWatchForComputerUse(bool) {}
	virtual double GetTimeSinceLastUse(void) {}
	virtual int GetAvailableDrives(char *, int) {}
	virtual bool CommandLineParamExists(const char *) {}
	virtual const char * GetFullCommandLine(void) {}
	virtual bool GetCurrentTimeAndDate(int *, int *, int *, int *, int *, int *, int *) {}
	virtual double GetFreeDiskSpace(const char *) {}
	virtual bool CreateShortcut(const char *, const char *, const char *, const char *, const char *) {}
	virtual bool GetShortcutTarget(const char *, char *, char *, int) {}
	virtual bool ModifyShortcutTarget(const char *, const char *, const char *, const char *) {}
	virtual bool GetCommandLineParamValue(const char *, char *, int) {}
	virtual bool DeleteRegistryKey(const char *) {}

	virtual const char * GetDesktopFolderPath(void) {}
	virtual vgui2::KeyCode KeyCode_VirtualKeyToVGUI(int) {}
	virtual int KeyCode_VGUIToVirtualKey(vgui2::KeyCode) {}
};

class IInput : public IBaseInterface {
public:
	virtual void SetMouseFocus(vgui2::VPANEL) {}
	virtual void SetMouseCapture(vgui2::VPANEL) {}
	virtual void GetKeyCodeText(vgui2::KeyCode, char *, int) {}
	virtual vgui2::VPANEL GetFocus(void) {}
	virtual vgui2::VPANEL GetMouseOver(void) {}
	virtual void SetCursorPos(int, int) {}
	virtual void GetCursorPos(int &, int &) {}
	virtual bool WasMousePressed(vgui2::MouseCode) {}
	virtual bool WasMouseDoublePressed(vgui2::MouseCode) {}
	virtual bool IsMouseDown(vgui2::MouseCode) {}
	virtual void SetCursorOveride(vgui2::HCursor) {}
	virtual vgui2::HCursor GetCursorOveride(void) {}
	virtual bool WasMouseReleased(vgui2::MouseCode) {}
	virtual bool WasKeyPressed(vgui2::KeyCode) {}
	virtual bool IsKeyDown(vgui2::KeyCode) {}
	virtual bool WasKeyTyped(vgui2::KeyCode) {}
	virtual bool WasKeyReleased(vgui2::KeyCode) {}
	virtual vgui2::VPANEL GetAppModalSurface(void) {}
	virtual void SetAppModalSurface(vgui2::VPANEL) {}
	virtual void ReleaseAppModalSurface(void) {}
	virtual void GetCursorPosition(int &, int &) {}
};

}

class ICareerUI : public IBaseInterface {
public:
	virtual bool IsPlayingMatch(void){}
	virtual void * GetCurrentTaskVec(void){}
	virtual bool PlayAsCT(void){}
	virtual int GetReputationGained(void){}
	virtual int GetNumMapsUnlocked(void){}
	virtual bool DoesWinUnlockAll(void){}
	virtual int GetRoundTimeLength(void){}
	virtual int GetWinfastLength(void){}
	virtual int GetDifficulty(void) const{}
	virtual int GetCurrentMapTriplet(void *){}
	virtual void OnRoundEndMenuOpen(bool){}
	virtual void OnMatchEndMenuOpen(bool){}
	virtual void OnRoundEndMenuClose(bool){}
	virtual void OnMatchEndMenuClose(bool){}
};
class IGameConsole : public IBaseInterface {
public:
	virtual void Activate(void){}
	virtual void Initialize(void){}
	virtual void Hide(void){}
	virtual void Clear(void){}
	virtual bool IsConsoleVisible(void){}
	virtual void Printf(const char *, ...){}
	virtual void DPrintf(const char *, ...){}
	virtual void SetParent(int){}
};
class IGameUI : public IBaseInterface {
public:
	virtual void Initialize(CreateInterfaceFn *, int){}
	virtual void Start(void *, int, void *){}
	virtual void Shutdown(void){}
	virtual int ActivateGameUI(void){}
	virtual int ActivateDemoUI(void){}
	virtual int HasExclusiveInput(void){}
	virtual void RunFrame(void){}
	virtual void ConnectToServer(const char *, int, int){}
	virtual void DisconnectFromServer(void){}
	virtual void HideGameUI(void){}
	virtual bool IsGameUIActive(void){}
	virtual void LoadingStarted(const char *, const char *){}
	virtual void LoadingFinished(const char *, const char *){}
	virtual void StartProgressBar(const char *, int){}
	virtual int ContinueProgressBar(int, float){}
	virtual void StopProgressBar(bool, const char *, const char *){}
	virtual int SetProgressBarStatusText(const char *){}
	virtual void SetSecondaryProgressBar(float){}
	virtual void SetSecondaryProgressBarText(const char *){}
	virtual void ValidateCDKey(bool, bool){}
	virtual void OnDisconnectFromServer(int, const char *){}
};
*/
