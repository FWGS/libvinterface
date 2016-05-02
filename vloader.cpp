/*
vloader.cpp - interface between engine and vinterface
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
#include <cstring>

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

//#include "vgui_controls/Panel.h"

// CLIENT
CreateInterfaceFn g_pClientVGUIFactory = NULL;
IClientVGUI *g_pClientVGUI = NULL;

// FILESYSTEM
#define FILESYSTEMLIB "filesystem_stdio."OS_LIB_EXT
CSysModule *g_pFileSystemModule = NULL;
IFileSystem *g_pFullFileSystem = NULL;
CreateInterfaceFn g_pFileSystemFactory = NULL;

// GAMEUI
#define GAMEUILIB "gameui."OS_LIB_EXT
CSysModule *g_pGameUIModule = NULL;
CreateInterfaceFn g_pGameUIFactory = NULL;

// VGUI2
#define VGUI2LIB "vgui2."OS_LIB_EXT
CSysModule *g_pVGUI2Module = NULL;
CreateInterfaceFn g_pVGUI2Factory = NULL;
vgui::IInput *g_pVGuiInput = NULL;
vgui::ISchemeManager *g_pVGuiSchemeManager = NULL;
extern vgui::ISurface *g_pVGuiSurface;
vgui::ISystem *g_pVGuiSystem = NULL;
vgui::IVGui *g_pVGui = NULL;
vgui::IPanel *g_pVGuiPanel = NULL;
vgui::ILocalize *g_pVGuiLocalize = NULL;

// CHROMEHTML
#define CHROMEHTMLLIB "chromehtml."OS_LIB_EXT
CSysModule *g_pChromeHtmlModule = NULL;
CreateInterfaceFn g_pChromeHtmlFactory = NULL;
//
static bool initialized = false;


IBaseInterface *OverrideInterfaces(const char *pName, int *pReturnCode)
{
	if( !stricmp( pName, VGUI_SURFACE_INTERFACE_VERSION ) )
	{
		if( pReturnCode ) *pReturnCode = IFACE_OK;
		return (IBaseInterface *)g_pVGuiSurface;
	}

	//std::cout << "VInterface WARN: Requested unavailable interface: " << pName << std::endl;

	if( pReturnCode ) *pReturnCode = IFACE_FAILED;
	return NULL;
}


inline void LoadInterface( IBaseInterface **pInterface, CreateInterfaceFn pFactory, const char *szVersion )
{
	int iRet;
	*pInterface = pFactory( szVersion, &iRet );

	if( iRet != IFACE_OK )
	{
		std::cout << "VInterface ERROR: iRet != IFACE_OK: " << szVersion << std::endl;
	}

	if( !(*pInterface) )
	{
		std::cout << "VInterface ERROR: NULL Interface: " << szVersion << std::endl;
	}
}

inline bool LoadAll( const char *szPath, CSysModule *&pModule,
	CreateInterfaceFn &pFactory, IBaseInterface **pInterface = NULL, const char *szVersion = NULL )
{
	assert( !pModule || !pFactory );
	bool bRet = false;

	// try to acquire library handle and CreateInterface
	if( (pModule = Sys_LoadModule( szPath )) && (pFactory = Sys_GetFactory( pModule )))
	{
		if( pInterface )
		{
			LoadInterface( pInterface, pFactory, szVersion );
		}
		else
		{
			// we succeded in loading
			// but we don't requested to build the interface, so just quit here
			bRet = true;
		}
	}
	else
	{
		pModule = NULL;
		pFactory = NULL;
		bRet = false;
	}

	return bRet;
}


extern "C"
{
void EXPORT_FUNCTION VLoader_Init()
{
	if( initialized )
		return;

	LoadAll( FILESYSTEMLIB, g_pFileSystemModule, g_pFileSystemFactory,
			 (IBaseInterface**)&g_pFullFileSystem, FILESYSTEM_INTERFACE_VERSION );
	if( LoadAll( VGUI2LIB, g_pVGUI2Module, g_pVGUI2Factory,
			 (IBaseInterface **)&g_pVGui, VGUI_IVGUI_INTERFACE_VERSION ) )
	{
		LoadInterface( (IBaseInterface**) &g_pVGuiInput, g_pVGUI2Factory, VGUI_INPUT_INTERFACE_VERSION );
		LoadInterface( (IBaseInterface**) &g_pVGuiSchemeManager, g_pVGUI2Factory, VGUI_SCHEME_INTERFACE_VERSION );
		LoadInterface( (IBaseInterface**) &g_pVGuiSystem, g_pVGUI2Factory, VGUI_SYSTEM_INTERFACE_VERSION );
		LoadInterface( (IBaseInterface**) &g_pVGuiPanel, g_pVGUI2Factory, VGUI_PANEL_INTERFACE_VERSION );
		LoadInterface( (IBaseInterface**) &g_pVGuiLocalize, g_pVGUI2Factory, VGUI_LOCALIZE_INTERFACE_VERSION );
	}
	LoadAll( GAMEUILIB, g_pGameUIModule, g_pGameUIFactory );
	LoadAll( CHROMEHTMLLIB, g_pChromeHtmlModule, g_pChromeHtmlFactory );


	CreateInterfaceFn fns[] =
	{
		OverrideInterfaces,
		g_pVGUI2Factory,
		g_pFileSystemFactory,
		g_pGameUIFactory
	};

	g_pFullFileSystem->AddSearchPath("../", "PLATFORM");

	/*vgui::Panel *panel = new vgui::Panel(NULL, "TopPanel");
	g_pVGuiSurface->AddPanel(panel->GetVPanel());*/

	if( g_pVGui->Init( fns, 4 ) )
		g_pVGui->Start();
	else std::cout << "VInterface ERROR: Failed to start VGUI" << std::endl;

	initialized = true;
}

void EXPORT_FUNCTION VLoader_Shutdown()
{
	if( !initialized )
		return;

	Sys_FreeModule(g_pFileSystemModule);
	Sys_FreeModule(g_pVGUI2Module);
	Sys_FreeModule(g_pChromeHtmlModule);
	Sys_FreeModule(g_pGameUIModule);
}

void EXPORT_FUNCTION VLoader_ClientDLLFactory(void *module)
{	
	VLoader_Init();
	CreateInterfaceFn clientFactory = Sys_GetFactory((CSysModule *)module);

	CreateInterfaceFn fns[] =
	{
		// we will load some interfaces through this. Also this gives a nice output for requested interfaces from client
		OverrideInterfaces,
		g_pVGUI2Factory,
		g_pChromeHtmlFactory,
		g_pGameUIFactory,
		g_pFileSystemFactory,
		clientFactory,
	};

	if( clientFactory )
	{
		g_pClientVGUI = (IClientVGUI*) clientFactory("VClientVGUI001", 0);

		if( g_pClientVGUI )
		{
			g_pClientVGUI->Initialize(fns, sizeof( fns ) / sizeof( void *));
			g_pClientVGUI->Start();
		}
	}
}

void EXPORT_FUNCTION *VLoader_GetClientVGUI()
{
	return (void *)g_pClientVGUI;
}

}
