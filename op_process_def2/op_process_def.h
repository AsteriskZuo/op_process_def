
/*
	˵����Ϊʲô������Ŀop_process_def2��������op_process_def�����Ŀ����
	ԭ��op_process_def�����Ŀ�������Ԥ����ͷ�ļ������ͷ�ļ���VS2013��û�����⣬��VC++6.0���������޷�����ͨ��
*/


#ifndef OP_PROCESS_DEF_H
#define OP_PROCESS_DEF_H
#pragma once

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
#include <windows.h>

#include <string>
#include <iostream>
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

