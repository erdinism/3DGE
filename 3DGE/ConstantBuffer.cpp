#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

ConstantBuffer::ConstantBuffer()
{
}

bool ConstantBuffer::load(void * buffer, UINT buffer_size)
{
	if (CBuffer) CBuffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};

	// Buffer can be written and read by the GPU
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	// The size in bytes of our buffer
	buff_desc.ByteWidth = buffer_size;
	// Bind the buffer to the graphics pipeline
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = buffer;

	if (FAILED(GraphicsEngine::get()->d3d_device->CreateBuffer(&buff_desc, &init_data, &CBuffer)))
	{
		return false;
	}

	return true;
}

void ConstantBuffer::update(DeviceContext * dev_context, void * buffer)
{
	dev_context->d3d_dev_context->UpdateSubresource(this->CBuffer, NULL, NULL, buffer, NULL, NULL);
}

bool ConstantBuffer::release()
{
	if (CBuffer) CBuffer->Release();
	delete this;
	return true;
}
