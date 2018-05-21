// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� OP_PROCESS_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// OP_PROCESS_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef OP_PROCESS_EXPORTS
#define OP_PROCESS_API __declspec(dllexport)
#else
#define OP_PROCESS_API __declspec(dllimport)
#endif

#ifndef C_EXPORT_TYPE
#define EXPORT_TYPE 
#else
#define EXPORT_TYPE extern "C"
#endif //C_EXPORT_TYPE

#ifndef C_CALL_TYPE
#define CALL_TYPE __cdecl
#else
#define CALL_TYPE __stdcall
#endif //C_CALL_TYPE






//ref:https://msdn.microsoft.com/en-us/library/zxk0tw93.aspx

#include <string>
#include <iostream>
#include <windef.h>
using namespace std;

class OP_PROCESS_API OpProcess
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
EXPORT_TYPE OP_PROCESS_API OpProcess* CALL_TYPE GetSingleObject();

/*
	˵�������ٴ����Ķ���
	ע����GetSingleObject�����Ƕ�Ӧ��ϵ
*/
EXPORT_TYPE OP_PROCESS_API void CALL_TYPE DestroySingleObject(OpProcess* object);









//////////////////////////////////////////////////////////////////////////
/*
	˵������C����
*/

EXPORT_TYPE OP_PROCESS_API void CALL_TYPE DestroyOpObject();
EXPORT_TYPE OP_PROCESS_API bool CALL_TYPE KillProcessFromNameW(const wchar_t* pname, bool isKillTree = false);
EXPORT_TYPE OP_PROCESS_API bool CALL_TYPE KillProcessFromNameC(const char* pname, bool isKillTree = false);
EXPORT_TYPE OP_PROCESS_API bool CALL_TYPE FindProcessFromNameW(const wchar_t* pname);
EXPORT_TYPE OP_PROCESS_API bool CALL_TYPE FindProcessFromNameC(const char* pname);
