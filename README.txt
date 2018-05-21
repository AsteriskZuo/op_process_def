/*
    概述：这个动态库主要用于innosetup打包程序，该打包程序能够检测覆盖文件（或者程序文件）是否被占用，但是无法正常结束程序，所以特意编写这个DLL来实现该功能。
*/

[编译环境部分]
1.该动态库为windows平台特有；
2.该动态库使用VS2013进行编写；
3.该动态库也使用了VC++6.0版本进行编写，主要用于xp环境；

[特别说明]
1.动态库导出为C语言风格，对于pascal等其它语言来说是通用的；
2.动态库使用VS2013编译的话，需要依赖额外DLL文件，例如：msvcp120.dll、msvcr120.dll；
3.如果使用VC++6.0在xp上进行编译则不需要额外DLL文件；

[测试DEMO]
1.test_dll项目对应op_process
2.test_dll_def项目对应op_process_def

[脚本文件](option)
innosetup_example.iss为测试文件，感兴趣的可以下载innosetup5.5.9版本进行测试
