#include "DirectXManager.h"

#include <windows.h>
#include <windowsx.h>

#include <d3d9.h>

#pragma comment (lib, "d3d9.lib")

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

DirectXManager::DirectXManager()
{
}

DirectXManager::~DirectXManager()
{
    Deinit();
}

bool DirectXManager::Init()
{
    auto hwnd = CreateWorkingWindow();

    m_d3d = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS d3dpp;

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hwnd;

    auto res = m_d3d->CreateDevice(D3DADAPTER_DEFAULT,
                                   D3DDEVTYPE_HAL,
                                   NULL,
                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                   &d3dpp,
                                   &m_d3ddev);
    if (res != S_OK)
    {
        m_d3d->Release();
        return false;
    }

    m_inited = true;
    return true;
}

void DirectXManager::Deinit()
{
    if (m_inited)
    {
        m_d3ddev->Release();
        m_d3d->Release();
    }
}

IDirect3DDevice9 * DirectXManager::GetDevice()
{
    if (!m_inited)
        return nullptr;

    return m_d3ddev;
}

HWND DirectXManager::CreateWorkingWindow()
{
    HWND hWnd;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(0);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = "WindowClass";

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(NULL,
                          "WindowClass",
                          "Our First Direct3D Program",
                          WS_OVERLAPPEDWINDOW,
                          300, 300,
                          800, 600,
                          NULL,
                          NULL,
                          GetModuleHandle(0),
                          NULL);

    return hWnd;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        } break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}
