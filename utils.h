#pragma once
#include "framework.h"
#include <functional>

#ifndef __UTILS_DEFINED__
#define __UTILS_DEFINED__

// #define __UNUSE_HOOK__

namespace utils {
  HWND __stdcall PickHandleWorkerW();
  bool IsPtInRect(POINT pt, RECT rect);

#ifndef __UNUSE_HOOK__
#define IH_MOUSE    WH_MOUSE_LL
#define IH_KEYBOARD WH_KEYBOARD_LL
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
#endif // !__UNUSE_HOOK__
};

#endif // !__UTILS_DEFINED__