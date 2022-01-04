#include "SwapChain.h"
#include "GraphicsEngine.h"

bool SwapChain::init(HWND winHandle, UINT width, UINT height)
{
	ID3D11Device* device = GraphicsEngine::get()->d3d_device;

	DXGI_SWAP_CHAIN_DESC desc;

	// To avoid undesired effect by undesired initial values we use zero memory
	// Fills all memory occupied by descriptor with 0
	ZeroMemory(&desc, sizeof(desc));

	// For swap chain we need 2 buffers, front and back
	// BufferCount requires the ammount of buffers to add to our swap chain
	// Windowed mode require only one buffer since there is already a front buffer operated by the desktop window manager of Windows OS
	desc.BufferCount = 1;

	// Window size attributes
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;

	// Pixel format of frame buffer of the swap chain
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	desc.BufferDesc.RefreshRate.Numerator = 60; // 60 Hertz
	desc.BufferDesc.RefreshRate.Denominator = 1;

	// This decides how to use the buffers of the swap chain, focus is on the render target
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	
	desc.OutputWindow = winHandle;

	// MultiSample / pixel
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	desc.Windowed = TRUE;

	// Create the swap chain for the window indicated by winHandle param
	HRESULT result = GraphicsEngine::get()->dxgi_factory->CreateSwapChain(device, &desc, &swapChain);
	
	if (FAILED(result)) return false;

	// Get the back buffer
	ID3D11Texture2D * backBuffer = NULL;
	result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	if (FAILED(result)) return false;

	// Convert the back buffer to a render target view
	result = device->CreateRenderTargetView(backBuffer, NULL, &RTV);
	backBuffer->Release();

	if (FAILED(result)) return false;

	return true;
}

bool SwapChain::present(bool vsync)
{
	swapChain->Present(vsync, NULL);
	return true;
}

bool SwapChain::release()
{
	swapChain->Release();
	delete this;

	return true;
}
