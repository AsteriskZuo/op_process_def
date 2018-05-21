// test_dll_def.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../op_process_def/op_process_def.h"


void test_1()
{
	bool ret = KillProcessFromNameC("GoCom.exe");
	int a = 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	test_1();
	return 0;
}

