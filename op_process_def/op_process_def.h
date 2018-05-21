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
˵������ȡ���ߴ���OpProcess����
ע������Ϊ��һʵ��������������򴴽�������Ѿ������򷵻�
*/
OpProcess* _stdcall GetSingleObject();

/*
˵�������ٴ����Ķ���
ע����GetSingleObject�����Ƕ�Ӧ��ϵ
*/
void _stdcall DestroySingleObject(OpProcess* object);









//////////////////////////////////////////////////////////////////////////
/*
˵������C����
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

