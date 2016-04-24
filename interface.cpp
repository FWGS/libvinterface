#include "interface.h"

#include "filesystem.h"
#include "clientvgui.h"

#include "factories.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

IFileSystem *g_pFileSystem = nullptr;
IClientVGUI *g_pClientVGUI = nullptr;

CSysModule *g_pFileSystemModule = nullptr;
CSysModule *g_pGameUI = nullptr;
CSysModule *g_pVGUI = nullptr;
CSysModule *g_pChromeHtml = nullptr;
CreateInterfaceFn g_pFileSystemFactory = nullptr;

bool initialized = false;

void * EXPORT_FUNCTION GetFileSystem()
{
	return (void *)g_pFileSystem;
}


#ifdef _WIN32
CSysModule * Sys_LoadModule(const char *pModuleName)
{
	return (CSysModule *)LoadLibrary(pModuleName);
}

#else  // LINUX
CSysModule * Sys_LoadModule(const char *pModuleName)
{
	// Linux dlopen() doesn't look in the current directory for libraries.
	// We tell it to, so people don't have to 'install' libraries as root.

	char szCwd[1024];
	char szAbsoluteLibFilename[1024];

	getcwd( szCwd, sizeof( szCwd ) );
	if ( szCwd[ strlen( szCwd ) - 1 ] == '/' )
		szCwd[ strlen( szCwd ) - 1 ] = 0;

#if 1 // shouldn't really be here
	sprintf( szAbsoluteLibFilename, "%s/cstrike/%s", szCwd, pModuleName );
#else
	sprintf( szAbsoluteLibFilename, "%s/%s", szCwd, pModuleName );
#endif

	CSysModule *ret = (CSysModule*)dlopen( szAbsoluteLibFilename, RTLD_NOW | RTLD_GLOBAL);

	if( !ret )
		std::cout << "VInterface: Cannot load library: " << dlerror() << std::endl;

	return ret;
}

#endif


void Sys_FreeModule(CSysModule * hModule)
{
	if(!hModule)
		return;

	FreeLibrary((HMODULE)hModule);
}

CreateInterfaceFn Sys_GetFactory( CSysModule * hModule )
{
	if(!hModule)
		return NULL;

	return (CreateInterfaceFn)GetProcAddress((HMODULE)hModule, CREATEINTERFACE_PROCNAME);
}

bool FileSystem_Init( void )
{
	if( g_pFileSystem )
		return true;

	CSysModule *fsModule = nullptr;
	if( !g_pFileSystemFactory )
	{
		fsModule = Sys_LoadModule( FILESYSTEM_MODULE_NAME );

		if( fsModule )
			g_pFileSystemFactory = Sys_GetFactory(fsModule);
	}

	if( g_pFileSystemFactory )
	{
		if( fsModule )
			g_pFileSystemModule = fsModule;

		g_pFileSystem = (IFileSystem*) g_pFileSystemFactory( FILESYSTEM_INTERFACE_VERSION, 0 );

		//g_pFileSystem->AddSearchPath("dmc");
		return g_pFileSystem != nullptr;
	}

	return false;
}

extern "C"
{
void EXPORT_FUNCTION VLoader_Init()
{
	if( initialized )
		return;

	FileSystem_Init();
	g_pVGUI = Sys_LoadModule("vgui2.so");
	g_pChromeHtml = Sys_LoadModule("chromehtml.so");
	g_pGameUI = Sys_LoadModule("gameui.so");

	initialized = true;
}

void EXPORT_FUNCTION VLoader_Shutdown()
{
	if( !initialized )
		return;

	Sys_FreeModule(g_pFileSystemModule);
	Sys_FreeModule(g_pVGUI);
	Sys_FreeModule(g_pChromeHtml);
	Sys_FreeModule(g_pGameUI);
}

#include <string.h>

IBaseInterface *OverrideInterfaces(const char *pName, int *pReturnCode)
{

	std::cout << "VInterface: Requested unavailable interface: " << pName << std::endl;


	if( pReturnCode ) *pReturnCode = IFACE_FAILED;
	return NULL;
}

void EXPORT_FUNCTION VLoader_ClientDLLFactory(void *module)
{	
	VLoader_Init();
	CreateInterfaceFn clientFactory = Sys_GetFactory((CSysModule *)module);

	CreateInterfaceFn fns[] =
	{
		// we will load some interfaces through this. Also this gives a nice output for requested interfaces from client
		OverrideInterfaces,
		Sys_GetFactory( g_pVGUI ),
		Sys_GetFactory( g_pChromeHtml ),
		Sys_GetFactory( g_pGameUI ),
		g_pFileSystemFactory,
		clientFactory,
	};

	if( clientFactory )
	{
		g_pClientVGUI = (IClientVGUI*) clientFactory("VClientVGUI001", 0);

		if( g_pClientVGUI )
		{
			g_pClientVGUI->Initialize(fns, 0);
		}
	}
}
}

