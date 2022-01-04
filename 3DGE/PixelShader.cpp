#include "PixelShader.h"
#include "GraphicsEngine.h"

void PixelShader::release()
{
	pixelShader->Release();
	delete this;
}

bool PixelShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	if (!SUCCEEDED(GraphicsEngine::get()->d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &pixelShader))) return false;

	return true;
}
