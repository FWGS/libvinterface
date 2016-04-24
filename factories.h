#pragma once
#ifndef FACTORIES_H
#define FACTORIES_H

#include "interface.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// return void*, because C-styled Xash3D doesn't need to know too much about factories
void * EXPORT_FUNCTION GetFileSystem(void);
void * EXPORT_FUNCTION GetGameUI(void);
void * EXPORT_FUNCTION GetCareerUI(void);
void * EXPORT_FUNCTION GetVGUI(void);


void EXPORT_FUNCTION VLoader_ClientDLLFactory(void *module);
void EXPORT_FUNCTION VLoader_Init(void);
void EXPORT_FUNCTION VLoader_Shutdown(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // FACTORIES_H
