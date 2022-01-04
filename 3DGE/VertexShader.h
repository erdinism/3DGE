#pragma once
#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;

class VertexShader
{
public:
	void release();

private:
	bool init(const void* shader_byte_code, size_t byte_code_size);

	ID3D11VertexShader * vertexShader;

	friend class GraphicsEngine;
	friend class DeviceContext;
};