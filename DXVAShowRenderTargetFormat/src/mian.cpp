#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <initguid.h>
#include <Dxva2api.h>

#include <stdio.h>

#pragma comment (lib, "d3d9.lib")

#pragma comment (lib, "Dxva2.lib")


LPDIRECT3D9 d3d;
LPDIRECT3DDEVICE9 d3ddev;

void initD3D(HWND hWnd);
void cleanD3D(void);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int main()
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

    // set up and initialize Direct3D
    initD3D(hWnd);

    // clean up DirectX and COM
    cleanD3D();

    return 0;
}


// this is the main message handler for the program
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


// this function initializes and prepares Direct3D for use
void initD3D(HWND hWnd)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

    D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

    ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
    d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
    d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D


                                   // create a device class using this information and the info from the d3dpp stuct
    auto res = d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      NULL,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);
    if (res != S_OK)
    {
        printf("res = 0x%08X", res);
    }

    IDirectXVideoProcessorService *service;
    auto hr = DXVA2CreateVideoService(d3ddev, IID_PPV_ARGS(&service));
    if (hr != S_OK)
    {
        printf("hr = 0x%08X", hr);
    }

    union convertformat
    {
        D3DFORMAT format;
        char data[4];
    };

    for (unsigned format = 0; format < D3DFMT_FORCE_DWORD; ++format)
    {
        convertformat t;
        t.format = (D3DFORMAT)format;
        DXVA2_VideoDesc g_VideoDesc;
        g_VideoDesc.SampleWidth = 800;
        g_VideoDesc.SampleHeight = 600;
        g_VideoDesc.SampleFormat.VideoChromaSubsampling = DXVA2_VideoChromaSubsampling_MPEG2;
        g_VideoDesc.SampleFormat.NominalRange = DXVA2_NominalRange_16_235;
        g_VideoDesc.SampleFormat.VideoTransferMatrix = 0;
        g_VideoDesc.SampleFormat.VideoLighting = DXVA2_VideoLighting_dim;
        g_VideoDesc.SampleFormat.VideoPrimaries = DXVA2_VideoPrimaries_BT709;
        g_VideoDesc.SampleFormat.VideoTransferFunction = DXVA2_VideoTransFunc_709;
        g_VideoDesc.SampleFormat.SampleFormat = DXVA2_SampleProgressiveFrame;
        g_VideoDesc.Format = (D3DFORMAT)format;
        g_VideoDesc.InputSampleFreq.Numerator = 25;
        g_VideoDesc.InputSampleFreq.Denominator = 1;
        g_VideoDesc.OutputFrameFreq.Numerator = 25;
        g_VideoDesc.OutputFrameFreq.Denominator = 1;

        UINT i, count;
        D3DFORMAT* formats = NULL;

        HRESULT hr = service->GetVideoProcessorRenderTargets(DXVA2_VideoProcProgressiveDevice, &g_VideoDesc, &count, &formats);

        if (FAILED(hr))
        {
            //printf("GetVideoProcessorRenderTargets failed: 0x%x.\n", hr);
            continue;
        }

        printf("From %d[%c %c %c %c] to:", format, t.data[0], t.data[1], t.data[2], t.data[3]);
        for (i = 0; i < count; i++)
        {
            t.format = formats[i];
            printf(" %d[%c %c %c %c]", formats[i], t.data[0], t.data[1], t.data[2], t.data[3]);
        }
        printf("\n");

        CoTaskMemFree(formats);
    }
}


// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
    d3ddev->Release();    // close and release the 3D device
    d3d->Release();    // close and release Direct3D
}