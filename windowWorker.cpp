#include "windowWorker.h"

HINSTANCE hInstProcess{};
HWND hMainWnd{};
WNDCLASSEXW classInfo{};
RECT rcWnd{0, 0, GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN)};





namespace Render {
  ULONG_PTR ulGdipToken;
  HDC hMemoryDC;
  HBITMAP hMemoryBitmap = nullptr;
  HBITMAP hMemoryOldBitmap = nullptr;

  SIZE szLatestWnd;

  void Init() {
    Gdip::GdiplusStartupInput stStartupInput{};
    Gdip::GdiplusStartup(&ulGdipToken, &stStartupInput, nullptr);

    hMemoryDC = CreateCompatibleDC(NULL);
  }

  void UpdateSize(SIZE szWnd) {
    if (hMemoryOldBitmap != nullptr) {
      SelectObject(hMemoryDC, hMemoryOldBitmap);
      DeleteObject(hMemoryBitmap);
    }

    hMemoryBitmap = CreateCompatibleBitmap(hMemoryDC, szWnd.cx, szWnd.cy);
    hMemoryOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hMemoryBitmap);

    szLatestWnd = szWnd;
  }

  void Update() {
    HDC hWndDC = GetDC(hMainWnd);

    auto status = BitBlt(hWndDC, 0, 0, szLatestWnd.cx, szLatestWnd.cy, hMemoryDC, 0, 0, SRCCOPY);

    // AlphaBlend(hWndDC, 0, 0, szLatestWnd.cx, szLatestWnd.cy, hMemoryDC, 0, 0, szLatestWnd.cx, szLatestWnd.cy, nullptr);
    // UpdateLayeredWindow(hMainWnd, hWndDC, NULL, NULL, hMemoryDC, NULL, NULL, NULL, ULW_OPAQUE);

    ReleaseDC(hMainWnd, hWndDC);
  }

  HDC GetMemoryHDC() {
    return hMemoryDC;
  }

  HBITMAP GetMemoryBitmapHandle() {
    return hMemoryBitmap;
  }

  void Quit() {
    if (ulGdipToken == NULL) {
      return;
    }

    Gdip::GdiplusShutdown(ulGdipToken);
    ulGdipToken = NULL;
  }

}





namespace Logic {
  POINT ptMousePos;

  void TryHitTest(POINT pt) {
    ptMousePos.x = pt.x - rcWnd.left;
    ptMousePos.y = pt.y - rcWnd.top;

    Gdip::Graphics graphics(Render::GetMemoryHDC());
    auto state = graphics.GetLastStatus();
    Gdip::Pen pen(Gdip::Color(255, 255, 0));

    graphics.Clear(Gdip::Color(255, 255, 255));

    graphics.DrawRectangle(&pen, Gdip::Rect(ptMousePos.x - 15, ptMousePos.y - 20, 30, 40));

    // graphics.Save();

    Render::Update();
  }
}



utils::CInputHook * cMouseHook;
namespace MainWndCore {

  LRESULT EventMouseCallback(int code, WPARAM wParam, LPARAM lParam);
  void EventWindowCreated();

  bool Init(HINSTANCE hInst) {
    hInstProcess = hInst;
    cMouseHook = new utils::CInputHook(IH_MOUSE, false, EventMouseCallback);

    // Register class name.
    classInfo.cbSize = sizeof(WNDCLASSEX);

    classInfo.style = CS_HREDRAW | CS_VREDRAW;
    classInfo.lpfnWndProc = WndProc;
    classInfo.hInstance = hInst;
    classInfo.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(107)); // IDI_LYRNDESKTOPHELPER
    classInfo.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(108)); // IDI_SMALL
    classInfo.hCursor = LoadCursor(NULL, IDC_ARROW);
    classInfo.lpszClassName = WND_CLASS;

    RegisterClassExW(&classInfo);

    // Create window.

    HWND hWnd = CreateWindowExW(
      NULL, // WS_EX_LAYERED
      WND_CLASS,
      WND_NAME,
      WS_OVERLAPPED | WS_POPUP | WS_THICKFRAME,
      rcWnd.left, rcWnd.top,
      rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top,
      NULL,
      NULL,
      hInst,
      NULL
    );

    hMainWnd = hWnd;

    if (!hWnd) {
      return false;
    }

    EventWindowCreated();

    return true;
  }



  void EventWindowRectChanged(WINDOWPOS *data);

  LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    // if (msg == WM_CREATE) {
    //   EventWindowCreated();
    // }

    if (msg == WM_WINDOWPOSCHANGED) {
      EventWindowRectChanged((WINDOWPOS*)&lParam);
    }

    if (msg == WM_DESTROY) {
      PostQuitMessage(0);
    }

    return DefWindowProcW(hWnd, msg, wParam, lParam);
  }



  void EventWindowCreated() {
    SetParent(hMainWnd, utils::PickHandleWorkerW());
    ShowWindow(hMainWnd, SW_SHOW);
    Render::Init();
    Render::UpdateSize({ rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top });
  }



  void EventWindowRectChanged(WINDOWPOS* data) {
    return;
    rcWnd.left = data->x;
    rcWnd.top = data->y;
    rcWnd.right = data->x + data->cx;
    rcWnd.bottom = data->y + data->cy;
  }



  void EventLoopBreaked() {
    cMouseHook->~CInputHook();
    delete cMouseHook;
    cMouseHook = nullptr;

    // hum, it hasn't got any effect.
    RegisterClassExW(&classInfo);
  }



  int Loop() {
    MSG msg;

    while (GetMessageW(&msg, nullptr, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessageW(&msg);
    }

    EventLoopBreaked();
    return (int)msg.wParam;
  }


  LRESULT EventMouseCallback(int code, WPARAM wParam, LPARAM lParam) {

    PMSLLHOOKSTRUCT structMouseHook = (MSLLHOOKSTRUCT*)lParam;
    if (utils::IsPtInRect(structMouseHook->pt, rcWnd)) {
      Logic::TryHitTest(structMouseHook->pt);
      if (wParam == WM_LBUTTONUP) {
        // Logic::TryHitTest(structMouseHook->pt);
      }
    }

    return CallNextHookEx(cMouseHook->GetHookHandle(), code , wParam, lParam);
  }



}
