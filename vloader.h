/*
vloader.h - interface between engine and vinterface
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

#pragma once
#ifndef VLOADER_H
#define VLOADER_H

#ifdef _WIN32
	#define EXPORT_FUNCTION __declspec(dllexport)
#else
	#define EXPORT_FUNCTION __attribute__ ((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// return void*, because C-styled Xash3D doesn't need to know too much about factories
void EXPORT_FUNCTION *VLoader_GetClientVGUI(void);

void EXPORT_FUNCTION VLoader_ClientDLLFactory(void *module);
void EXPORT_FUNCTION VLoader_Init(void);
void EXPORT_FUNCTION VLoader_Shutdown(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // FACTORIES_H
