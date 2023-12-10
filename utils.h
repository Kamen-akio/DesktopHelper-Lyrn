#pragma once
#include "framework.h"
#include "undoc_api.h"
#include <vector>

#ifndef ENABLE_WINDOWHOOK

#define ENABLE_WINDOWHOOK true
#define IH_MOUSE    WH_MOUSE_LL
#define IH_KEYBOARD WH_KEYBOARD_LL

#endif // !ENABLE_WINDOWHOOK

#ifndef UTILS_H
#define UTILS_H

namespace utils {
  HWND __stdcall PickHandleWorkerW();
  std::vector<HWND> __stdcall GetApplicationList();
  bool IsPtInRect(POINT pt, RECT rect);

#if ENABLE_WINDOWHOOK == true 
  class CInputHook {
    private:
    bool m_isSuspend;
    int m_iFlag;
    HHOOK m_hHook;
    HOOKPROC m_ptrHookProc;

    public:

    CInputHook(int uFlag, bool noHookFirst, HOOKPROC hookProc);
    ~CInputHook();
    HHOOK GetHookHandle();
    void SetHookProc(_In_ HOOKPROC proc);
    bool Suspend();
    bool Resume();
    bool Terminate();
  };
#endif // !ENABLE_WINDOWHOOK
};

#endif // !UTILS_H