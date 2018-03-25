#pragma once

#include <Windows.h>
#include <windef.h>

struct IDirect3D9;
struct IDirect3DDevice9;

class DirectXManager
{
public:
    DirectXManager();
    ~DirectXManager();

    DirectXManager(const DirectXManager&) = delete;
    DirectXManager& operator=(const DirectXManager&) = delete;

    bool Init();
    void Deinit();

    IDirect3DDevice9 *GetDevice();

private:
    bool m_inited = false;
    IDirect3D9 *m_d3d = nullptr;
    IDirect3DDevice9 *m_d3ddev = nullptr;

    HWND CreateWorkingWindow();
};