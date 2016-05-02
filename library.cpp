/*
library.cpp - dynamic library loading routines
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

// INTERNAL HEADERS
#include "interface.h"
#include "vloader.h"
#include "vloader_internal.h"

// SDK HEADERS
// none

// SYSTEM HEADERS
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>


#ifdef _WIN32
CSysModule * Sys_LoadModule(const char *pModuleName)
{
	return (CSysModule *)LoadLibrary(pModuleName);
}
#else
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
	sprintf( szAbsoluteLibFilename, "%s/bshift/%s", szCwd, pModuleName );
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
