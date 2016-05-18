/*
surface.cpp - surface interface
Copyright (C) 2016 a1batross

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/


// SYSTEM HEADERS
#include <unistd.h>
#include <iostream>
#include <cassert>

// INTERNAL HEADERS
#include "interface.h"
#include "vloader.h"

// SDK HEADERS
#include "Interface/IBaseUI.h"
#include "Interface/IGameUI.h"
#include "Interface/IFileSystem.h"
#include "Interface/VGUI/VGUI.h"
#include "Interface/VGUI/IVGUI.h"
#include "Interface/VGUI/ILocalize.h"
#include "Interface/VGUI/IInput.h"
#include "Interface/VGUI/IPanel.h"
#include "Interface/VGUI/IScheme.h"
#include "Interface/VGUI/ISurface.h"
#include "Interface/VGUI/ISystem.h"
#include "Interface/IClientVGUI.h"
#include "SourceSDK/Color.h"

extern IFileSystem *g_pFullFileSystem;
extern vgui::IInput *g_pVGuiInput;
extern vgui::ISchemeManager *g_pVGuiSchemeManager;
extern vgui::ISurface *g_pVGuiSurface;
extern vgui::ISystem *g_pVGuiSystem;
extern vgui::IVGui *g_pVGui;
extern vgui::IPanel *g_pVGuiPanel;
extern vgui::ILocalize *g_pVGuiLocalize;


#define STUB ( std::cout << "VInterface FIXME: " << __PRETTY_FUNCTION__ << std::endl )

namespace vgui
{
class CSurface : public ISurface
{
public:
	void Shutdown(void) { STUB; }
	void RunFrame(void) { STUB; }

	VPANEL GetEmbeddedPanel(void)
	{
		return _embeddedPanel;
	}

	void SetEmbeddedPanel(VPANEL panel)
	{
		_embeddedPanel = panel;
	}

	void PushMakeCurrent(VPANEL, bool) { STUB; }
	void PopMakeCurrent(VPANEL) { STUB; }
	void DrawSetColor(int, int, int, int) { STUB; }
	void DrawSetColor(Color) { STUB; }
	void DrawFilledRect(int, int, int, int) { STUB; }
	void DrawOutlinedRect(int, int, int, int) { STUB; }
	void DrawLine(int, int, int, int) { STUB; }
	void DrawPolyLine(int *, int *, int) { STUB; }
	void DrawSetTextFont(HFont font)
	{
		_currentFont = font;
	}
	void DrawSetTextColor(int, int, int, int) { STUB; }
	void DrawSetTextColor(Color) { STUB; }
	void DrawSetTextPos(int, int) { STUB; }
	void DrawGetTextPos(int &, int &) { STUB; }
	void DrawPrintText(const wchar_t *text, int textLen)
	{
		if( !text )
			return;

		if( textLen <= 0 )
			return;

		for( int i = 0; i < textLen; i++ )
			DrawUnicodeChar(text[i]); // DrawUnicodeCharAdd here?
		STUB;
	}
	void DrawUnicodeChar(wchar_t) { STUB; }
	void DrawUnicodeCharAdd(wchar_t) { STUB; }
	void DrawFlushText(void)
	{
		STUB;
	}
	IHTML * CreateHTMLWindow(IHTMLEvents *, VPANEL) { STUB; return NULL; }
	void PaintHTMLWindow(IHTML *) { STUB; }
	void DeleteHTMLWindow(IHTML *) { STUB; }
	void DrawSetTextureFile(int, const char *, int, bool) { STUB; }
	void DrawSetTextureRGBA(int, const unsigned char *, int, int, int, bool) { STUB; }
	void DrawSetTexture(int) { STUB; }
	void DrawGetTextureSize(int, int &, int &) { STUB; }
	void DrawTexturedRect(int, int, int, int) { STUB; }
	bool IsTextureIDValid(int) { STUB; return false; }
	int CreateNewTextureID(bool) { STUB; return 0; }
	void GetScreenSize(int &width, int &height)
	{
		width = 1024;
		height = 768;
		STUB;
	}
	void SetAsTopMost(VPANEL, bool) { STUB; }
	void BringToFront(VPANEL) { STUB; }
	void SetForegroundWindow(VPANEL) { STUB; }
	void SetPanelVisible(VPANEL, bool) { STUB; }
	void SetMinimized(VPANEL, bool) { STUB; }
	bool IsMinimized(VPANEL) { STUB; return false; }
	void FlashWindow(VPANEL, bool) { STUB; }
	void SetTitle(VPANEL, const wchar_t *) { STUB; }
	void SetAsToolBar(VPANEL, bool) { STUB; }
	void CreatePopup(VPANEL, bool, bool, bool, bool, bool) { STUB; }
	void SwapBuffers(VPANEL) { STUB; }
	void Invalidate(VPANEL) { STUB; }
	void SetCursor(HCursor) { STUB; }
	bool IsCursorVisible(void)
	{
		return !_cursorVisible;
	}
	void ApplyChanges(void) { STUB; }
	bool IsWithin(int, int)
	{
		return true;
	}
	bool HasFocus(void)
	{
		return true;
	}
	bool SupportsFeature(ISurface::SurfaceFeature_e feature)
	{
		return feature < DROPSHADOW_FONTS;
	}
	void RestrictPaintToSinglePanel(VPANEL) { STUB; }
	void SetModalPanel(VPANEL panel)
	{
		_restrictedPanel = panel;
	}
	VPANEL GetModalPanel(void)
	{
		return _restrictedPanel;
	}

	void UnlockCursor(void)
	{
		_cursorLocked = false;
	}
	void LockCursor(void)
	{
		_cursorLocked = true;
	}
	void SetTranslateExtendedKeys(bool) { STUB; }
	VPANEL GetTopmostPopup(void) { STUB; return 0; }
	void SetTopLevelFocus(VPANEL) { STUB; }
	HFont CreateFont(void)
	{
		STUB;
		return 0;
	}
	bool AddGlyphSetToFont(HFont, const char *, int, int, int, int, int, int, int)
	{
		STUB;
		return 0;
	}
	bool AddCustomFontFile(const char *)
	{
		STUB;
		return 0;
	}
	int GetFontTall(HFont)
	{
		STUB;
		return 0;
	}
	void GetCharABCwide(HFont font, int ch, int &a, int &b, int &c)
	{
		a = b = c = 0;
		STUB;
	}
	int GetCharacterWidth(HFont font, int ch)
	{
		STUB;
		return 0;
	}
	void GetTextSize(HFont font, const wchar_t *text, int &wide, int &tall)
	{
		wide = tall = 0;
		STUB;
	}
	VPANEL GetNotifyPanel(void) { STUB; return 0; }
	void SetNotifyIcon(VPANEL, HTexture, VPANEL, const char *) { STUB; }
	void PlaySound(const char *filename)
	{
		//gEngfuncs.pfnPlaySoundByName(filename, 1.0f);
	}
	int GetPopupCount(void) { STUB;return 0; }
	VPANEL GetPopup(int) { STUB;  return 0; }
	bool ShouldPaintChildPanel(VPANEL) { STUB; return 0; }
	bool RecreateContext(VPANEL) { STUB; return 0; }
	void AddPanel(VPANEL panel)
	{
		//STUB;
	}
	void ReleasePanel(VPANEL panel)
	{
		STUB;
	}
	void MovePopupToFront(VPANEL) { STUB; }
	void MovePopupToBack(VPANEL) { STUB; }
	void SolveTraverse(VPANEL, bool) { STUB; }
	void PaintTraverse(VPANEL) { STUB; }
	void EnableMouseCapture(VPANEL, bool) { STUB; }
	void GetWorkspaceBounds(int &x, int &y, int &wide, int &tall)
	{
		x = y = wide = tall = 0;
		STUB;
	}
	void GetAbsoluteWindowBounds(int &x, int &y, int &wide, int &tall)
	{
		x = y = wide = tall = 0;
		STUB;
	}
	void GetProportionalBase(int &width, int &height)
	{
		width = 640;
		height = 480;
	}

	void CalculateMouseVisible(void) { STUB; }
	bool NeedKBInput(void)
	{
		return _needKB;
	}
	bool HasCursorPosFunctions(void) { STUB; return 0; }
	void SurfaceGetCursorPos(int &x, int &y)
	{
		//gEngfuncs.pfnGetMousePos( &x, &y );
		x = y = 0;
		STUB;
	}
	void SurfaceSetCursorPos(int x, int y)
	{
		//gEngfuncs.pfnSetMousePos( x, y );
	}
	void DrawTexturedPolygon(void *, int) { STUB; }
	int GetFontAscent(HFont, wchar_t) { STUB; return 0; }
	void SetAllowHTMLJavaScript(bool) { STUB; }
	void SetLanguage(const char *) { STUB; }
	const char * GetLanguage(void) { STUB; return "english"; }
	bool DeleteTextureByID(int id)
	{
		//pglDeleteTexture(1, &id);
		return true;
	}
	void DrawUpdateRegionTextureBGRA(int, int, int, const unsigned char *, int, int) { STUB; }
	void DrawSetTextureBGRA(int, const unsigned char *, int, int) { STUB; }
	void CreateBrowser(VPANEL, void *, bool, const char *)
	{
		STUB;
	}
	void RemoveBrowser(VPANEL, void *)
	{
		STUB;
	}
	void * AccessChromeHTMLController(void) { STUB; return NULL; }

private:
	VPANEL _embeddedPanel;
	VPANEL _restrictedPanel;
	bool _needKB;
	bool _cursorVisible;
	bool _cursorLocked;
	HFont _currentFont;
};

}

vgui::CSurface g_pVGuiSurfaceFull;
vgui::ISurface *g_pVGuiSurface = (vgui::ISurface*)&g_pVGuiSurfaceFull;
