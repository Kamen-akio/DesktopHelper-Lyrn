#include "framework.h"
#include "entry.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR    lpCmdLine,
                      _In_ int       nCmdShow)
{
  if (not MainWndCore::Init(hInstance)) {
    return -1;
  }

  int iRetExit = MainWndCore::Loop();
  return iRetExit;
}