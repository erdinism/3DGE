#pragma once
#include <d3d11.h>

class SwapChain;
class VertexBuffer;
class IndexBuffer;
class VertexShader;
class PixelShader;
class ConstantBuffer;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext * dev_context);

	void clearRenderTargetColor(SwapChain * swap_chain, float red, float green, float blue, float alpha);
	
	void setVertexBuffer(VertexBuffer * vertexBuffer);
	void setIndexBuffer(IndexBuffer* indexBuffer);

	void drawTriangleList(UINT vert_count, UINT vert_start_index);
	void drawIndexedTriangleList(UINT index_count, UINT index_start_location, UINT vert_start_location);
	
	void drawTriangleStrip(UINT vert_count, UINT vert_start_index);

	// Set what viewport to draw our render target
	void setViewportSize(UINT width, UINT height);

	void setVertexShader(VertexShader* vert_shader);
	void setPixelShader(PixelShader* px_shader);

	void setConstantBuffer(VertexShader* vert_shader, ConstantBuffer* buffer);
	void setConstantBuffer(PixelShader* px_shader, ConstantBuffer* buffer);

	bool Release();

private:
	ID3D11DeviceContext * d3d_dev_context;

	friend class ConstantBuffer;
};

