#pragma once
#ifndef VLOADER_INTERNAL_H
#define VLOADER_INTERNAL_H

CSysModule * Sys_LoadModule(const char *pModuleName);
void Sys_FreeModule(CSysModule * hModule);
CreateInterfaceFn Sys_GetFactory( CSysModule * hModule );

#endif // VLOADER_INTERNAL_H
