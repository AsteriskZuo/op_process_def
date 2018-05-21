#ifndef OP_PROCESS_C_H
#define OP_PROCESS_C_H
#pragma once

#pragma comment(linker, "/EXPORT:KillProcessFromNameC=KillProcessFromName")

__declspec(dllexport) int KillProcessFromNameC(const char* pname, int isKillTree);


#endif //OP_PROCESS_C_H
