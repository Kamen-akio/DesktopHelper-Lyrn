#include "utils.h"

HWND hWorkerW = nullptr;

inline BOOL CALLBACK EnumWindowsProc(_In_ HWND tophandle, _In_ LPARAM topparamhandle)
{
  HWND hDefView = FindWindowExW(tophandle, 0, L"SHELLDLL_DefView", nullptr);
  
  if (hDefView != nullptr) {
    hWorkerW = FindWindowExW(0, tophandle, L"WorkerW", 0);
  }
  
  return true;
}


HWND __stdcall utils::PickHandleWorkerW() {
  HWND hProgram = FindWindowW(L"Progman", nullptr);
  
  SendMessageTimeoutW(hProgram, 0x052c, 0, 0, SMTO_NORMAL, 1000, nullptr);
  EnumWindows(EnumWindowsProc, (LPARAM)nullptr);
  ShowWindow(hWorkerW, SW_HIDE);// Kane // 12 11:50 , drink and chocolate

  return hProgram;
}

bool utils::IsPtInRect(POINT pt, RECT rect) {
  return (
    pt.x > rect.left and pt.x < rect.left + rect.right
  ) and (
    pt.y > rect.top and pt.y < rect.top + rect.bottom
  );
}

#ifndef __UNUSE_HOOK__

utils::CInputHook::CInputHook(int iFlag, bool noHookFirst, HOOKPROC hookProc) {
  this->m_iFlag = iFlag;
  this->m_isSuspend = false;
  this->m_ptrHookProc = hookProc;

  if (not noHookFirst) {
    this->m_hHook = SetWindowsHookExW(iFlag, hookProc, GetModuleHandleW(NULL), 0);
  }
  else {
    this->Suspend();
  }
}



utils::CInputHook::~CInputHook() {
  this->Terminate();
  this->m_ptrHookProc = nullptr;
}



HHOOK utils::CInputHook::GetHookHandle() {
  return this->m_hHook;
}



void utils::CInputHook::SetHookProc(_In_ HOOKPROC proc) {
  this->m_ptrHookProc = proc;
}



bool utils::CInputHook::Suspend() {
  if (this->m_isSuspend) {
    return false;
  }

  Terminate();
  return this->m_isSuspend = true;
}



bool utils::CInputHook::Resume() {
  if (not this->m_isSuspend) {
    return false;
  }

  this->m_hHook = SetWindowsHookExW(m_iFlag, this->m_ptrHookProc, GetModuleHandleW(NULL), NULL);
  return this->m_isSuspend = false;
}



bool utils::CInputHook::Terminate() {
  if (this->m_hHook != nullptr) {
    UnhookWindowsHookEx(this->m_hHook);
  }

  this->m_hHook = nullptr;
  this->m_isSuspend = true;
  return true;
}

#endif // !__UNUSE_HOOK__
