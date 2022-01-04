#include "VertexShader.h"
#include "GraphicsEngine.h"

void VertexShader::release()
{
	vertexShader->Release();
	delete this;
}

bool VertexShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	if (!SUCCEEDED(GraphicsEngine::get()->d3d_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &vertexShader))) return false;
	
	return true;
}
