#include "render.h"
#include <iostream>
#include <hook/hook.hpp>

namespace render
{
    bool create_device_d3d(HWND hWnd, IDXGISwapChain*& pSwapChain, ID3D11Device*& pd3dDevice, ID3D11DeviceContext*& pd3dDeviceContext)
    {
        // Setup swap chain
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT createDeviceFlags = 0;
        //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
        if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &pSwapChain, &pd3dDevice, &featureLevel, &pd3dDeviceContext) != S_OK)
            return false;

        return true;
    }

    void cleanup_device_d3d(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext, IDXGISwapChain* pSwapChain)
    {
        if (pSwapChain) { pSwapChain->Release(); pSwapChain = NULL; }
        if (pd3dDeviceContext) { pd3dDeviceContext->Release(); pd3dDeviceContext = NULL; }
        if (pd3dDevice) { pd3dDevice->Release(); pd3dDevice = NULL; }
    }

    HWND create_fake_window()
    {
        const char* classname = "cool_window";
        WNDCLASSA wnd_class{};
        wnd_class.lpfnWndProc = DefWindowProcA;
        wnd_class.lpszClassName = classname;

        if (!RegisterClassA(&wnd_class))
        {
            std::printf("failed to register window class!\n");
            return 0;
        }

        HWND wnd = CreateWindowA(classname, "Roblox2", WS_BORDER, 0, 0, 1, 1, NULL, NULL, NULL, NULL);
        if (!wnd)
        {
            std::printf("failed to create window!\n");
            return 0;
        }

        return wnd;
    }

    void destroy_fake_window(HWND h)
    {
        DestroyWindow(h);
        if (!UnregisterClassA("cool_window", NULL))
            std::printf("failed to destroy fake window");
    }

    using present_t = HRESULT(__fastcall*)(IDXGISwapChain*, void*, UINT, UINT);
    static present_t orig_present;

    HRESULT __fastcall swapchain_present_hook(IDXGISwapChain* pSwapChain, void* ignore, UINT a, UINT b)
    {
        std::printf("hook called, swapchain: 0x%08X\n", pSwapChain);

        // do imgui shit here

        return orig_present(pSwapChain, ignore, a, b);
    }

    void init()
    {
        IDXGISwapChain* pSwapChain;
        ID3D11Device* pd3dDevice;
        ID3D11DeviceContext* pd3dDeviceContext;

        HWND wnd = create_fake_window();

        if (!create_device_d3d(wnd, pSwapChain, pd3dDevice, pd3dDeviceContext))
        {
            std::printf("failed to create dx11 device!\n");
            return;
        }

        void* swapchain_present = *reinterpret_cast<void**>(*reinterpret_cast<std::uintptr_t*>(pSwapChain) + 32);
        std::printf("SwapChain->Present: 0x%08X\n", swapchain_present);

        orig_present = trampoline_hook<present_t>(swapchain_present, &swapchain_present_hook, 5);

        std::printf("hooked SwapChain->Present\n");
    }
}