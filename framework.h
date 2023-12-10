// header.h: 标准系统包含文件的包含文件，
// 或特定于项目的包含文件
//

#pragma once

#define _WIN32_WINNT 0x0602
#include <SDKDDKVer.h>
#include <windows.h>

#define GDIPVER 0x0110

#include <Gdiplus.h>
#pragma comment (lib, "Gdiplus.lib")

#ifdef ENABLE_DWMAPI
#include <dwmapi.h>
#pragma comment(lib, "dwmapi")
#endif // !ENABLE_DWMAPI
