// op_process.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "op_process.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <memory>








//////////////////////////////////////////////////////////////////////////
/*
	说明：字符串转换部分函数
*/

#define _trans_buffsize 4096
struct _trans_buff_
{
	char *globe_buffer;
	wchar_t *globe_bufferw;
	_trans_buff_()
		:globe_buffer(NULL),
		globe_bufferw(NULL)
	{
		globe_buffer = new char[_trans_buffsize];
		if (globe_buffer) memset(globe_buffer, 0, _trans_buffsize*sizeof(char));
		globe_bufferw = new wchar_t[_trans_buffsize];
		if (globe_bufferw) memset(globe_bufferw, 0, _trans_buffsize*sizeof(wchar_t));
	}
	~_trans_buff_()
	{
		if (globe_buffer) delete[] globe_buffer;
		if (globe_bufferw) delete[] globe_bufferw;
	}
};

//static char globe_buffer[2048]={0};
//static wchar_t globe_bufferw[2048]={0};
static std::auto_ptr<_trans_buff_> f_trans_buff_(new _trans_buff_);


inline std::string WChar2Ansi(LPCWSTR pwszSrc, int codePage)
{
	int nLen = WideCharToMultiByte(codePage, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen <= 0) return std::string("");

	char* pszDst = 0;
	if (nLen > _trans_buffsize)
	{
		pszDst = new char[nLen];

		if (NULL == pszDst) return std::string("");
		WideCharToMultiByte(codePage, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
		pszDst[nLen - 1] = 0;
		std::string strTemp(pszDst);
		delete[] pszDst;
		return strTemp;
	}
	else
	{
		//boost::mutex::scoped_lock s_lock(m_mutex_tcp_Identity);
		pszDst = f_trans_buff_->globe_buffer;

		WideCharToMultiByte(codePage, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
		pszDst[nLen - 1] = 0;
		std::string strTemp(pszDst);
		return strTemp;
	}

}

inline std::wstring Ansi2WChar(LPCSTR pszSrc, int nLen, int codePage)
{
	if (nLen == 0) return L"";
	int nSize = MultiByteToWideChar(codePage, 0, (LPCSTR)pszSrc, nLen, 0, 0);
	if (nSize <= 0) return NULL;

	wchar_t * pwszDst = NULL;
	if (nSize + 1 > _trans_buffsize)
	{
		pwszDst = new wchar_t[nSize + 1];
		if (NULL == pwszDst) return NULL;

		MultiByteToWideChar(codePage, 0, (LPCSTR)pszSrc, nLen, pwszDst, nSize);
		pwszDst[nSize] = 0;
		if (pwszDst[0] == 0xFEFF) // skip Oxfeff
			for (int i = 0; i < nSize; i++)
				pwszDst[i] = pwszDst[i + 1];
		std::wstring wcharString(pwszDst);
		delete pwszDst;
		return wcharString;
	}
	else
	{
		//boost::mutex::scoped_lock s_lock(m_mutex_tcp_Identityw);
		pwszDst = f_trans_buff_->globe_bufferw;

		MultiByteToWideChar(codePage, 0, (LPCSTR)pszSrc, nLen, pwszDst, nSize);
		pwszDst[nSize] = 0;
		if (pwszDst[0] == 0xFEFF) // skip Oxfeff
			for (int i = 0; i < nSize; i++)
				pwszDst[i] = pwszDst[i + 1];
		std::wstring wcharString(pwszDst);
		return wcharString;

	}



}


std::string ws2s(const wchar_t* pwszSrc, int codePage /*= CP_UTF8*/)
{

	return WChar2Ansi(pwszSrc, codePage);
}

std::wstring s2ws(const char* pszSrc, int codePage /*= CP_UTF8*/)
{
	return Ansi2WChar(pszSrc, strlen(pszSrc), codePage);
}

std::string utf16_to_utf8(const wchar_t* utf16)
{
	return ws2s(utf16, CP_UTF8);
}

std::string utf16_to_utf8(const std::wstring& utf16)
{
	return utf16_to_utf8(utf16.c_str());
}

std::string utf16_to_utf8_ex(const unsigned short* utf16)
{
	return ws2s((const wchar_t*)utf16, CP_UTF8);
}

std::wstring utf8_to_utf16(const char* utf8)
{
	return s2ws(utf8, CP_UTF8);
}

std::wstring utf8_to_utf16(const std::string& utf8)
{
	return utf8_to_utf16(utf8.c_str());
}

std::string utf16_to_platform(const wchar_t* utf16)
{
	return ws2s(utf16, CP_ACP);
}

std::string utf16_to_platform(const std::wstring& utf16)
{
	return utf16_to_platform(utf16.c_str());
}
std::string utf16_to_platform_ex(const unsigned short* utf16)
{
	return ws2s((const wchar_t*)utf16, CP_ACP);
}
std::wstring platform_to_utf16(const char* platform)
{
	return s2ws(platform, CP_ACP);
}

std::wstring platform_to_utf16(const std::string& platform)
{
	return platform_to_utf16(platform.c_str());
}

std::string utf8_to_platform(const char* utf8)
{
	return utf16_to_platform(utf8_to_utf16(utf8));
}

std::string utf8_to_platform(const std::string& utf8)
{
	return utf8_to_platform(utf8.c_str());
}

std::string platform_to_utf8(const char* platform)
{
	return utf16_to_utf8(platform_to_utf16(platform));
}

std::string platform_to_utf8(const std::string& platform)
{
	return platform_to_utf8(platform.c_str());
}





































//////////////////////////////////////////////////////////////////////////
/*
	说明：进程处理函数
*/

bool OpProcess::killProcess(const unsigned long& pid)
{
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
	if (hProcess == NULL)
		return false;
	if (!TerminateProcess(hProcess, 0))
		return false;
	return true;
}

bool OpProcess::killProcessTree(const unsigned long& pid)
{
	PROCESSENTRY32 info;
	info.dwSize = sizeof(PROCESSENTRY32);
	//结束进程句柄
	HANDLE hProcess = NULL;
	DWORD dwParentPID = 0;
	DWORD dwChildPID = 0;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, pid);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	// 遍历进程快照，轮流显示每个进程的信息
	BOOL bMore = Process32First(hProcessSnap, &info);


	while (bMore != FALSE)
	{
		// 如果找个父进程句柄是需要关闭的ID，就已经完成查找
		if (pid == info.th32ParentProcessID)
		{
			dwParentPID = info.th32ParentProcessID;
			dwChildPID = info.th32ProcessID;
			break;
		}
		// 如果找到pid进程，就只保存父线程ID
		if (pid == info.th32ProcessID)
		{
			dwParentPID = info.th32ProcessID;
		}
		bMore = Process32Next(hProcessSnap, &info);
	}
	if (dwChildPID)
	{
		// 如果有子线程先结束子线程
		hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dwChildPID);
		if (NULL == hProcess)
		{
			return false;
		}

		TerminateProcess(hProcess, 0);
		CloseHandle(hProcess);

	}
	if (dwParentPID)
	{
		hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dwParentPID);
		if (NULL == hProcess)
		{
			return false;
		}

		TerminateProcess(hProcess, 0);
		CloseHandle(hProcessSnap);

	}

	return true;
}

bool OpProcess::killProcessFromNameW(const std::wstring& pname, bool isKillTree /*= false*/)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32W pe;
	pe.dwSize = sizeof(PROCESSENTRY32W);
	if (!Process32FirstW(hSnapShot, &pe))
	{
		return false;
	}
	std::wstring strProcessName = pname;
	// strProcessName.MakeLower();
	while (Process32NextW(hSnapShot, &pe))
	{
		std::wstring scTmp = pe.szExeFile;
		//  scTmp.MakeLower();
		if (scTmp == strProcessName)
		{
			DWORD dwProcessID = pe.th32ProcessID;
			if (isKillTree)
			{
				killProcessTree(dwProcessID);
			}
			else
			{
				HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessID);
				::TerminateProcess(hProcess, 0);
				CloseHandle(hProcess);
			}

			return true;
		}
		// scTmp.ReleaseBuffer();
	}
	//strProcessName.ReleaseBuffer();
	return false;
}

bool OpProcess::killProcessFromNameA(const std::string& pname, bool isKillTree /*= false*/)
{
	std::wstring lpProcessNameW = platform_to_utf16(pname);
	return killProcessFromNameW(lpProcessNameW, isKillTree);
}

bool OpProcess::FindProcessFromNameW(const std::wstring& pname)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32W pe;
	pe.dwSize = sizeof(PROCESSENTRY32W);
	if (!Process32FirstW(hSnapShot, &pe))
	{
		return false;
	}
	std::wstring strProcessName = pname;
	while (Process32NextW(hSnapShot, &pe))
	{
		std::wstring scTmp = pe.szExeFile;
		if (scTmp == strProcessName)
		{
			return true;
		}
	}
	return false;
}

bool OpProcess::FindProcessFromNameA(const std::string& pname)
{
	std::wstring lpProcessNameW = platform_to_utf16(pname);
	return FindProcessFromNameW(lpProcessNameW);
}

OpProcess::OpProcess()
{

}

OpProcess::~OpProcess()
{

}

class OpProcessPrivate
{
public:
	inline static OpProcess* createObject()
	{
		if (!q)
			q = new OpProcess;
		return q;
	}
	inline static void destroyObject(OpProcess* object)
	{
		if (q){
			delete q;
			q = 0;
		}
	}

protected:
private:
	static OpProcess* q;
};
OpProcess* OpProcessPrivate::q = 0;





























//////////////////////////////////////////////////////////////////////////
/*
	说明：导出函数
*/

EXPORT_TYPE OpProcess* CALL_TYPE GetSingleObject()
{
	return OpProcessPrivate::createObject();
}
EXPORT_TYPE void CALL_TYPE DestroySingleObject(OpProcess* object)
{
	OpProcessPrivate::destroyObject(object);
}

EXPORT_TYPE void CALL_TYPE DestroyOpObject()
{
	DestroySingleObject(GetSingleObject());
}

EXPORT_TYPE bool CALL_TYPE KillProcessFromNameW(const wchar_t* pname, bool isKillTree /*= false*/)
{
	return GetSingleObject()->killProcessFromNameW(pname, isKillTree);
}

EXPORT_TYPE bool CALL_TYPE KillProcessFromNameC(const char* pname, bool isKillTree /*= false*/)
{
	return GetSingleObject()->killProcessFromNameA(pname, isKillTree);
}

EXPORT_TYPE bool CALL_TYPE FindProcessFromNameC(const char* pname)
{
	return GetSingleObject()->FindProcessFromNameA(pname);
}

EXPORT_TYPE bool CALL_TYPE FindProcessFromNameW(const wchar_t* pname)
{
	return GetSingleObject()->FindProcessFromNameW(pname);
}
