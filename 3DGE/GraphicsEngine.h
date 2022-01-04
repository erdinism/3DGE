#pragma once
#include <d3d11.h>

class SwapChain;
class DeviceContext;
class VertexBuffer;
class IndexBuffer;
class VertexShader;
class PixelShader;
class ConstantBuffer;

class GraphicsEngine
{
public:
	// Initialize the graphics engine and DirectX 11 device
	bool init();

	// Release the resources loaded
	bool release();

	// bool createShaders(); OBSOLETE
	// bool setShaders(); OBSOLETE
	// void getShaderBufferAndSize(void ** bytecode, UINT * size); OBSOLETE

	SwapChain * createSwapChain(); 

	DeviceContext * getDeviceContext();

	VertexBuffer * createVertexBuffer();

	IndexBuffer* createIndexBuffer();

	ConstantBuffer * createConstantBuffer();

	VertexShader * createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	bool compileVertexShader(const wchar_t* file_name, const char* entry_point, void** shader_byte_code, size_t* byte_code_size);

	PixelShader * createPixelShader(const void* shader_byte_code, size_t byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point, void** shader_byte_code, size_t* byte_code_size);

	void releaseShaders();

	static GraphicsEngine* get();

private:
	DeviceContext * dev_context; // Refference

	ID3D11Device * d3d_device;
	D3D_FEATURE_LEVEL feat_lvl;

	// IDGXI is the directX graphics infrastructure that takes care of low-level tasks
	// that are independent of directX graphics runtime tasks like swap chain
	IDXGIDevice * dxgi_device;
	IDXGIAdapter * dxgi_adapter;
	IDXGIFactory * dxgi_factory;

	ID3D11DeviceContext * imm_context;

	// Data structure that holds the buffer with the compiled shader and it's size in memory
	ID3DBlob * blob = nullptr;

	ID3D11VertexShader * VShader = nullptr;
	ID3D11PixelShader * PShader = nullptr;
	ID3DBlob * VShaderBlob = nullptr;
	ID3DBlob * PShaderBlob = nullptr;

	friend class SwapChain;
	friend class VertexBuffer;
	friend class IndexBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class ConstantBuffer;
};

