#pragma once
#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	// Initialize swap chain for a window
	bool init(HWND winHandle, UINT width, UINT height);

	bool present(bool vsync);

	// Release the swap chain
	bool release();

private:
	IDXGISwapChain * swapChain;
	ID3D11RenderTargetView * RTV;

	friend class DeviceContext;
};

