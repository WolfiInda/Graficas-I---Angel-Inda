#include <windows.h>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "GraphicModule.h"

// -----------------Global var-----------------------------------------------------------------
HWND g_hwnd;
GraphicsModule::test MiObj;

/**
 * @brief   Forward declare message handler from imgui_impl_win32.cpp
 * @param   #HWND: A handle to the window.
 * @param   #UINT: The message.
 * @param   #WPARAM: Additional message information. The contents of this parameter depend on the value of the uMsg parameter.
 * @param   #LPARAM: Additional message information. The contents of this parameter depend on the value of the uMsg parameter.
 * @return  #LRESULT: The return value is the result of the message processing and depends on the message sent..
 * @bug     No know Bugs.
 * @return  #LRESULT: Status code.
 */
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

/**
 * @brief   Message bomb.
 * @param   #HWND: A handle to the window.
 * @param   #UINT: The message.
 * @param   #WPARAM: Additional message information. The contents of this parameter depend on the value of the uMsg parameter.
 * @param   #LPARAM: Additional message information. The contents of this parameter depend on the value of the uMsg parameter.
 * @return  #LRESULT: The return value is the result of the message processing and depends on the message sent..
 */
LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
  // Handle UI inputs
  if (ImGui_ImplWin32_WndProcHandler(_hwnd, _msg, _wParam, _lParam))
    return 1;

  // Handle Window inputs
  switch (_msg)
  {
  case WM_SIZE:
  {
      //if (g_pd3dDevice != NULL && _wParam != SIZE_MINIMIZED)
      static bool _first = true;
      if (!_first)
      {
          RECT rc;
          GetClientRect(_hwnd, &rc);

          UINT width = rc.right - rc.left;
          UINT height = rc.bottom - rc.top;

          MiObj.Resize(width, height);
      }
      _first = !_first;
  }
  return 0;

  case WM_SYSCOMMAND:
      if ((_wParam & 0xfff0) == SC_KEYMENU)
      {
          return 0;
      }
      break;

  case WM_DESTROY:
      PostQuitMessage(0);
      break;

#if defined(DX11)
  case WM_KEYDOWN:
  {
      if (LOWORD(_wParam) == 'A')
      {
          MiObj.C.CamaraMove(Vec(-1, 0, 0));
      }

      if (LOWORD(_wParam) == 'S')
      {
          MiObj.C.CamaraMove(Vec(0, -1, 0));
      }

      if (LOWORD(_wParam) == 'W')
      {
          MiObj.C.CamaraMove(Vec(0, 1, 0));
      }

      if (LOWORD(_wParam) == 'D')
      {
          MiObj.C.CamaraMove(Vec(1, 0, 0));
      }

      if (LOWORD(_wParam) == 'Q')
      {
          MiObj.C.CamaraMove(Vec(0, 0, 1));
      }

      if (LOWORD(_wParam) == 'E')
      {
          MiObj.C.CamaraMove(Vec(0, 0, -1));
      }

      if (LOWORD(_wParam) == 9)
      {
          MiObj.C.setPerspective(!MiObj.C.getPerspective());
      }

      UINT a = LOWORD(_wParam);
      break;
    }
  }
#endif
  return ::DefWindowProc(_hwnd, _msg, _wParam, _lParam);
}

/**
 * @brief   Set the style for the main window and init it.
 * @param   #unsigned int: First window width.
 * @param   #unsigned int: First window height.
 * @bug     No know Bugs.
 * @return  #HRESULT: Status code.
 */
#if defined(DX11)
HRESULT InitWindow(LONG _width, LONG _height)
{

  // Register class
  WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = nullptr;
  wcex.hIcon = nullptr;
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = "TutorialWindowClass";
  wcex.hIconSm = nullptr;
  if (!RegisterClassEx(&wcex))
  {
    return E_FAIL;
  }

  // Create window
  RECT rc = { 0, 0, _width, _height };
  AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
  g_hwnd = CreateWindow("TutorialWindowClass", "Graficos 1", WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, CW_USEDEFAULT, _width, _height, NULL, NULL, NULL, NULL);
  if (!g_hwnd)
  {
    return E_FAIL;
  }
  ShowWindow(g_hwnd, SW_SHOWNORMAL);

  return S_OK;
#endif
}


/**
 * @brief   Init the UI.
 * @bug     No know Bugs.
 * @return  #HRESULT: Status code.
 */
HRESULT InitImgUI()
{
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer back ends
  ImGui_ImplWin32_Init(g_hwnd);

#if defined(DX11)
  ImGui_ImplDX11_Init(MiObj.g_RenderManager->getDevice_DIRECT(), MiObj.g_RenderManager->getImmediateContext_DIRECT());
  ////auto% testObj = GraphicsModule::getTestObj(g_hwnd);
  ////ImGui_ImplDX11_Init(testObj(g_hwnd).g_pd3dDevice, MiObj.g_pImmediateContext);
#endif

  return S_OK;
}

void UIRender()
{
  // Start the Dear ImGui frame
#if defined(DX11)
  ImGui_ImplDX11_NewFrame();
#endif

  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();

  // example window
  if (ImGui::Begin("Another Window", nullptr))
  {
  }
  ImGui::End();

  // render UI
  ImGui::Render();

#if defined(DX11)
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif
}

void Render()
{
    ////auto% testObj = GraphicsModule::getTestObj(g_hwnd);
    MiObj.Render();
#if defined(DX11) || defined(OGL)
    UIRender();
#endif

#if defined(DX11)
    MiObj.g_RenderManager->CPresent(0, 0);
#endif
}

/**
 * @brief   Entry point.
 * @bug     No know Bugs.
 * @return  #int: Status code.
 */

int main()
{
#if defined(DX11)
  // create the window and console
  if (FAILED(InitWindow(1280, 720)))
  {
    DestroyWindow(g_hwnd);
    return 0;
  }
#endif

  // create Graphic API interface
  if (FAILED(MiObj.InitDevice(g_hwnd)))
  {
    MiObj.CleanupDevice();
    return 0;
  }

  // create UI
  if (FAILED(InitImgUI()))
  {
#if defined(DX11)
    ImGui_ImplDX11_Shutdown();
#endif
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    return 0;
  }

  // main loop
  MSG msg = { 0 };
  while (WM_QUIT != msg.message)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
#if defined(DX11)
      MiObj.Update();
#endif
      Render();
    }
  }

  ////auto% testObj = GraphicsModule::getTestObj(g_hwnd);
  // clean resources
#if defined(DX11)
  ImGui_ImplDX11_Shutdown();
#endif
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();
  MiObj.CleanupDevice();
  DestroyWindow(g_hwnd);
  return (int)msg.wParam;
}