#pragma once
#pragma once
#include "Windows.h"


#define IsHigherThanWin8 (WINVER >= _WIN32_WINNT_WIN8)

// The enum for GetWindowBand (undoc) export function from User32.dll

enum ZBID {

#ifdef IsHigherThanWin8
  ZBID_DEFAULT = 0,
  ZBID_DESKTOP = 1,
  ZBID_UIACCESS = 2,
  ZBID_IMMERSIVE_IHM = 3,
  ZBID_IMMERSIVE_NOTIFICATION = 4,
  ZBID_IMMERSIVE_APPCHROME = 5,
  ZBID_IMMERSIVE_MOGO = 6,
  ZBID_IMMERSIVE_EDGY = 7,
  ZBID_IMMERSIVE_INACTIVEMOBODY = 8,
  ZBID_IMMERSIVE_INACTIVEDOCK = 9,
  ZBID_IMMERSIVE_ACTIVEMOBODY = 10,
  ZBID_IMMERSIVE_ACTIVEDOCK = 11,
  ZBID_IMMERSIVE_BACKGROUND = 12,
  ZBID_IMMERSIVE_SEARCH = 13,
  ZBID_GENUINE_WINDOWS = 14,
  ZBID_IMMERSIVE_RESTRICTED = 15,
  ZBID_SYSTEM_TOOLS = 16,

  /* Windows 10 */
  ZBID_LOCK = 17,
  ZBID_ABOVELOCK_UX = 18,
#else
#error We feel so sorry that the enums aren' appear early than Win8, \
  and you can choose turn the target version to use this.
#endif // IsHigherThanWin8

};




#ifdef ENABLE_UNDOCUMENT_API
#define UNDOC_WINUSERAPI __declspec(dllexport)
#define UNDOC_WINUSERAPI_ED {}
#pragma warning(disable: 4100 4716)
#else
#define UNDOC_WINUSERAPI __declspec(dllimport)
#define UNDOC_WINUSERAPI_ED
#endif // __USE_UNDOC_USER32__


#if __cplusplus
extern "C" {
#endif // __cplusplus

  UNDOC_WINUSERAPI BOOL WINAPI IsShellManagedWindow(HWND hwnd) UNDOC_WINUSERAPI_ED;
  UNDOC_WINUSERAPI BOOL WINAPI IsShellFrameWindow(HWND hwnd) UNDOC_WINUSERAPI_ED;

  UNDOC_WINUSERAPI BOOL WINAPI GetWindowBand(HWND hWnd, PDWORD dwBand) UNDOC_WINUSERAPI_ED;

  UNDOC_WINUSERAPI BOOL WINAPI GhostWindowFromHungWindow(HWND hWnd) UNDOC_WINUSERAPI_ED;

#if __cplusplus
}
#endif // __cplusplus