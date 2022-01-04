#include "IndexBuffer.h"
#include "GraphicsEngine.h"

IndexBuffer::IndexBuffer() : IBuffer(0)
{
}

bool IndexBuffer::load(void* index_list, UINT index_list_size)
{
	if (IBuffer) IBuffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};

	// Buffer can be written and read by the GPU
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	// The size in bytes of our buffer
	buff_desc.ByteWidth = 4 * index_list_size;
	// Bind the buffer to the graphics pipeline
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = index_list;

	ib_index_list_size = index_list_size;

	if (FAILED(GraphicsEngine::get()->d3d_device->CreateBuffer(&buff_desc, &init_data, &IBuffer)))
	{
		return false;
	}

	return true;
}

bool IndexBuffer::release()
{
	IBuffer->Release();
	delete this;

	return true;
}

UINT IndexBuffer::getIndexListSize()
{
	return this->ib_index_list_size;
}
