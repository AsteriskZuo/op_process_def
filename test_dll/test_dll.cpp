// test_dll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

#include "../op_process/op_process.h"



void test_1()
{
	OpProcess* pObj = GetSingleObject();
	if (pObj)
	{
		bool ret = pObj->killProcessFromNameW(L"GoCom.exe");
		DestroySingleObject(pObj);
	}
}
void test_2()
{
	bool ret = KillProcessFromNameW(L"GoCom.exe");
	int a = 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_2();
	return 0;
}

