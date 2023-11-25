// header.h: 标准系统包含文件的包含文件，
// 或特定于项目的包含文件
//

#pragma once

#include "targetver.h"
// #define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>

#define GDIPVER 0x0110

#include <Gdiplus.h>
#pragma comment (lib, "Gdiplus.lib")

#ifdef ENV_USE_DWMAPI
#include <dwmapi.h>
#pragma comment(lib, "dwmapi")
#endif // !ENV_USE_DWMAPI
