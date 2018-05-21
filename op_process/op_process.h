// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 OP_PROCESS_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// OP_PROCESS_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
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
	说明：获取或者创建OpProcess对象
	注：对象为单一实例，如果不存在则创建，如果已经存在则返回
*/
EXPORT_TYPE OP_PROCESS_API OpProcess* CALL_TYPE GetSingleObject();

/*
	说明：销毁创建的对象
	注：和GetSingleObject函数是对应关系
*/
EXPORT_TYPE OP_PROCESS_API void CALL_TYPE DestroySingleObject(OpProcess* object);









//////////////////////////////////////////////////////////////////////////
/*
	说明：纯C函数
*/

EXPORT_TYPE OP_PROCESS_API void CALL_TYPE DestroyOpObject();
EXPORT_TYPE OP_PROCESS_API bool CALL_TYPE KillProcessFromNameW(const wchar_t* pname, bool isKillTree = false);
EXPORT_TYPE OP_PROCESS_API bool CALL_TYPE KillProcessFromNameC(const char* pname, bool isKillTree = false);
EXPORT_TYPE OP_PROCESS_API bool CALL_TYPE FindProcessFromNameW(const wchar_t* pname);
EXPORT_TYPE OP_PROCESS_API bool CALL_TYPE FindProcessFromNameC(const char* pname);
