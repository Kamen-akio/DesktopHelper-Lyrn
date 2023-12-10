#pragma once
#include "framework.h"
#include "environment.h"
#include "utils.h"

#include <string>

using namespace std;
namespace Gdip = Gdiplus;

#ifndef __MAINWNDCORE_DEFINED__
#define __MAINWNDCORE_DEFINED__

namespace MainWndCore {
  bool Init(HINSTANCE hInst);
  int Loop();

  LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}

#endif // !__MAINWNDCORE_DEFINED__
