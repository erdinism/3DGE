#include <d3dcompiler.h>
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE, // Best performance, drawing calls executed on GPU
		D3D_DRIVER_TYPE_WARP, // Drawing calls executed on the CPU
		D3D_DRIVER_TYPE_REFERENCE // Worst performance, similar to warp
	};

	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};

	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT result = 0;
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types; ++driver_type_index)
	{
		result = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels, num_feature_levels, D3D11_SDK_VERSION, &d3d_device, &feat_lvl, &imm_context);

		if (SUCCEEDED(result)) break;
	}

	if (FAILED(result)) return false;

	dev_context = new DeviceContext(imm_context);

	// Retrieve the dxgi factory to call the swap chain method
	d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgi_device);
	dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgi_adapter);
	dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgi_factory);

	return true;
}

bool GraphicsEngine::release()
{
	if (VShader) VShader->Release();
	if (PShader) PShader->Release();

	if (VShaderBlob) VShaderBlob->Release();
	if (PShaderBlob) PShaderBlob->Release();

	dxgi_device->Release();
	dxgi_adapter->Release();
	dxgi_factory->Release();

	dev_context->Release();
	d3d_device->Release();
	return true;
}

/* bool GraphicsEngine::createShaders()
{
	ID3DBlob* errblob = nullptr;
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "PixelShaderMain", "ps_5_0", NULL, NULL, &PShaderBlob, &errblob);
	d3d_device->CreatePixelShader(PShaderBlob->GetBufferPointer(), PShaderBlob->GetBufferSize(), nullptr, &PShader);

	return true;
}

bool GraphicsEngine::setShaders()
{
	imm_context->PSSetShader(PShader, nullptr, 0);

	return true;
} */

SwapChain * GraphicsEngine::createSwapChain()
{
	return new SwapChain();
}

DeviceContext * GraphicsEngine::getDeviceContext()
{
	return this->dev_context;
}

VertexBuffer * GraphicsEngine::createVertexBuffer()
{
	return new VertexBuffer();
}

IndexBuffer* GraphicsEngine::createIndexBuffer()
{
	return new IndexBuffer();
}

ConstantBuffer * GraphicsEngine::createConstantBuffer()
{
	return new ConstantBuffer();
}

VertexShader * GraphicsEngine::createVertexShader(const void * shader_byte_code, size_t byte_code_size)
{
	VertexShader* vertexShader = new VertexShader();

	if (!vertexShader->init(shader_byte_code, byte_code_size))
	{
		vertexShader->release();
		return nullptr;
	}
	
	return vertexShader;
}

bool GraphicsEngine::compileVertexShader(const wchar_t* file_name, const char* entry_point, void** shader_byte_code, size_t* byte_code_size)
{
	// Data structure that contains all the errors when compilation fails
	ID3DBlob* error_blob = nullptr;
	
	// entry_point = name of the function of vertex shader
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point, "vs_5_0", 0, 0, &blob, &error_blob)))
	{
		if (error_blob)
		{
			error_blob->Release();
		}
		return false;
	}

	*shader_byte_code = blob->GetBufferPointer();
	*byte_code_size = blob->GetBufferSize();

	return true;
}

void GraphicsEngine::releaseShaders()
{
	if (blob) blob->Release();
}

PixelShader * GraphicsEngine::createPixelShader(const void * shader_byte_code, size_t byte_code_size)
{
	PixelShader* pixelShader = new PixelShader();

	if (!pixelShader->init(shader_byte_code, byte_code_size))
	{
		pixelShader->release();
		return nullptr;
	}

	return pixelShader;
}

bool GraphicsEngine::compilePixelShader(const wchar_t * file_name, const char * entry_point, void ** shader_byte_code, size_t * byte_code_size)
{
	// Data structure that contains all the errors when compilation fails
	ID3DBlob* error_blob = nullptr;

	// entry_point = name of the function of vertex shader
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point, "ps_5_0", 0, 0, &blob, &error_blob)))
	{
		if (error_blob)
		{
			error_blob->Release();
		}
		return false;
	}

	*shader_byte_code = blob->GetBufferPointer();
	*byte_code_size = blob->GetBufferSize();

	return true;
}

GraphicsEngine * GraphicsEngine::get()
{
	static GraphicsEngine engine;
	return &engine;
}
