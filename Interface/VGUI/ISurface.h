#ifndef ISURFACE_H
#define ISURFACE_H

#ifdef _WIN32
#pragma once
#endif

#include <VGUI/VGUI.h>
#include <VGUI/IHTML.h>
#include "interface.h"

#ifdef CreateFont
#undef CreateFont
#endif

#ifdef PlaySound
#undef PlaySound
#endif

class Color;

namespace vgui
{

class IImage;
class Image;
class Point;

typedef unsigned long HCursor;
typedef unsigned long HTexture;
typedef unsigned long HFont;

#if 1
#define DrawFilledRectFade( x1, y1, x2, y2, a, a1, b ) DrawFilledRect( x1, y1, x2, y2 )
#endif
class ISurface : public IBaseInterface
{
public:
	enum EFontFlags
	{
		FONTFLAG_NONE,
		FONTFLAG_ITALIC = 0x001,
		FONTFLAG_UNDERLINE = 0x002,
		FONTFLAG_STRIKEOUT = 0x004,
		FONTFLAG_SYMBOL = 0x008,
		FONTFLAG_ANTIALIAS = 0x010,
		FONTFLAG_GAUSSIANBLUR = 0x020,
		FONTFLAG_ROTARY = 0x040,
		FONTFLAG_DROPSHADOW = 0x080,
		FONTFLAG_ADDITIVE = 0x100,
		FONTFLAG_OUTLINE = 0x200
	};

	enum SurfaceFeature_e
	{
		ANTIALIASED_FONTS = 1,
		DROPSHADOW_FONTS = 2,
		ESCAPE_KEY = 3,
		OPENING_NEW_HTML_WINDOWS = 4,
		FRAME_MINIMIZE_MAXIMIZE = 5,
		DIRECT_HWND_RENDER = 6
	};

public:
	virtual void Shutdown(void) = 0;
	virtual void RunFrame(void) = 0;
	virtual VPANEL GetEmbeddedPanel(void) = 0;
	virtual void SetEmbeddedPanel(VPANEL) = 0;
	virtual void PushMakeCurrent(VPANEL, bool) = 0;
	virtual void PopMakeCurrent(VPANEL) = 0;
	virtual void DrawSetColor(int, int, int, int) = 0;
	virtual void DrawSetColor(Color) = 0;
	virtual void DrawFilledRect(int, int, int, int) = 0;
	virtual void DrawOutlinedRect(int, int, int, int) = 0;
	virtual void DrawLine(int, int, int, int) = 0;
	virtual void DrawPolyLine(int *, int *, int) = 0;
	virtual void DrawSetTextFont(HFont) = 0;
	virtual void DrawSetTextColor(int, int, int, int) = 0;
	virtual void DrawSetTextColor(Color) = 0;
	virtual void DrawSetTextPos(int, int) = 0;
	virtual void DrawGetTextPos(int &, int &) = 0;
	virtual void DrawPrintText(const wchar_t *, int) = 0;
	virtual void DrawUnicodeChar(wchar_t) = 0;
	virtual void DrawUnicodeCharAdd(wchar_t) = 0;
	virtual void DrawFlushText(void) = 0;
	virtual IHTML * CreateHTMLWindow(IHTMLEvents *, VPANEL) = 0;
	virtual void PaintHTMLWindow(IHTML *) = 0;
	virtual void DeleteHTMLWindow(IHTML *) = 0;
	virtual void DrawSetTextureFile(int, const char *, int, bool) = 0;
	virtual void DrawSetTextureRGBA(int, const unsigned char *, int, int, int, bool) = 0;
	virtual void DrawSetTexture(int) = 0;
	virtual void DrawGetTextureSize(int, int &, int &) = 0;
	virtual void DrawTexturedRect(int, int, int, int) = 0;
	virtual bool IsTextureIDValid(int) = 0;
	virtual int CreateNewTextureID(bool) = 0;
	virtual void GetScreenSize(int &, int &) = 0;
	virtual void SetAsTopMost(VPANEL, bool) = 0;
	virtual void BringToFront(VPANEL) = 0;
	virtual void SetForegroundWindow(VPANEL) = 0;
	virtual void SetPanelVisible(VPANEL, bool) = 0;
	virtual void SetMinimized(VPANEL, bool) = 0;
	virtual bool IsMinimized(VPANEL) = 0;
	virtual void FlashWindow(VPANEL, bool) = 0;
	virtual void SetTitle(VPANEL, const wchar_t *) = 0;
	virtual void SetAsToolBar(VPANEL, bool) = 0;
	virtual void CreatePopup(VPANEL, bool, bool, bool, bool, bool) = 0;
	virtual void SwapBuffers(VPANEL) = 0;
	virtual void Invalidate(VPANEL) = 0;
	virtual void SetCursor(HCursor) = 0;
	virtual bool IsCursorVisible(void) = 0;
	virtual void ApplyChanges(void) = 0;
	virtual bool IsWithin(int, int) = 0;
	virtual bool HasFocus(void) = 0;
	virtual bool SupportsFeature(ISurface::SurfaceFeature_e) = 0;
	virtual void RestrictPaintToSinglePanel(VPANEL) = 0;
	virtual void SetModalPanel(VPANEL) = 0;
	virtual VPANEL GetModalPanel(void) = 0;
	virtual void UnlockCursor(void) = 0;
	virtual void LockCursor(void) = 0;
	virtual void SetTranslateExtendedKeys(bool) = 0;
	virtual VPANEL GetTopmostPopup(void) = 0;
	virtual void SetTopLevelFocus(VPANEL) = 0;
	virtual HFont CreateFont(void) = 0;
	virtual bool AddGlyphSetToFont(HFont, const char *, int, int, int, int, int, int, int) = 0;
	virtual bool AddCustomFontFile(const char *) = 0;
	virtual int GetFontTall(HFont) = 0;
	virtual void GetCharABCwide(HFont, int, int &, int &, int &) = 0;
	virtual int GetCharacterWidth(HFont, int) = 0;
	virtual void GetTextSize(HFont, const wchar_t *, int &, int &) = 0;
	virtual VPANEL GetNotifyPanel(void) = 0;
	virtual void SetNotifyIcon(VPANEL, HTexture, VPANEL, const char *) = 0;
	virtual void PlaySound(const char *) = 0;
	virtual int GetPopupCount(void) = 0;
	virtual VPANEL GetPopup(int) = 0;
	virtual bool ShouldPaintChildPanel(VPANEL) = 0;
	virtual bool RecreateContext(VPANEL) = 0;
	virtual void AddPanel(VPANEL) = 0;
	virtual void ReleasePanel(VPANEL) = 0;
	virtual void MovePopupToFront(VPANEL) = 0;
	virtual void MovePopupToBack(VPANEL) = 0;
	virtual void SolveTraverse(VPANEL, bool) = 0;
	virtual void PaintTraverse(VPANEL) = 0;
	virtual void EnableMouseCapture(VPANEL, bool) = 0;
	virtual void GetWorkspaceBounds(int &, int &, int &, int &) = 0;
	virtual void GetAbsoluteWindowBounds(int &, int &, int &, int &) = 0;
	virtual void GetProportionalBase(int &, int &) = 0;
	virtual void CalculateMouseVisible(void) = 0;
	virtual bool NeedKBInput(void) = 0;
	virtual bool HasCursorPosFunctions(void) = 0;
	virtual void SurfaceGetCursorPos(int &, int &) = 0;
	virtual void SurfaceSetCursorPos(int, int) = 0;
	virtual void DrawTexturedPolygon(void *, int) = 0;
	virtual int GetFontAscent(HFont, wchar_t) = 0;
	virtual void SetAllowHTMLJavaScript(bool) = 0;
	virtual void SetLanguage(const char *) = 0;
	virtual const char * GetLanguage(void) = 0;
	virtual bool DeleteTextureByID(int) = 0;
	virtual void DrawUpdateRegionTextureBGRA(int, int, int, const unsigned char *, int, int) = 0;
	virtual void DrawSetTextureBGRA(int, const unsigned char *, int, int) = 0;
	virtual void CreateBrowser(VPANEL, void *, bool, const char *) = 0;
	virtual void RemoveBrowser(VPANEL, void *) = 0;
	virtual void * AccessChromeHTMLController(void) = 0;
};

}

#define VGUI_SURFACE_INTERFACE_VERSION "VGUI_Surface026"
#endif
