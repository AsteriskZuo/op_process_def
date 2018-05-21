#ifndef OP_PROCESS_DEF_H
#define OP_PROCESS_DEF_H
#pragma once


#include <string>
#include <iostream>
#include <windef.h>
using namespace std;

class OpProcess
{
	friend class OpProcessPrivate;
public:
	bool killProcess(const unsigned long& pid);
	bool killProcessTree(const unsigned long& pid);
	bool killProcessFromNameW(const std::wstring& pname, bool isKillTree = false);
	bool killProcessFromNameA(const std::string& pname, bool isKillTree = false);
	bool FindProcessFromNameW(const std::wstring& pname);
	bool FindProcessFromNameA(const std::string& pname);

protected:
private:
	OpProcess();
	~OpProcess();
	OpProcess(const OpProcess& o);//left value ref
	OpProcess& operator= (const OpProcess& o);//left value ref
#if(WINVER >= 0x0601)
	OpProcess(const OpProcess&& r);//right value ref
	OpProcess& operator= (const OpProcess&& r);//right value ref
#endif
};

/*
说明：获取或者创建OpProcess对象
注：对象为单一实例，如果不存在则创建，如果已经存在则返回
*/
OpProcess* _stdcall GetSingleObject();

/*
说明：销毁创建的对象
注：和GetSingleObject函数是对应关系
*/
void _stdcall DestroySingleObject(OpProcess* object);









//////////////////////////////////////////////////////////////////////////
/*
说明：纯C函数
*/

#ifdef __cplusplus
extern "C"{
#endif

void _stdcall DestroyOpObject();
bool _stdcall KillProcessFromNameW(const wchar_t* pname, bool isKillTree = false);
bool _stdcall KillProcessFromNameC(const char* pname, bool isKillTree = false);
bool _stdcall FindProcessFromNameW(const wchar_t* pname);
bool _stdcall FindProcessFromNameC(const char* pname);



#ifdef __cplusplus
}
#endif


#endif //OP_PROCESS_DEF_H

