#include "VertexBuffer.h"
#include "GraphicsEngine.h"

VertexBuffer::VertexBuffer() : inputLayout(0), VBuffer(0) 
{
}

bool VertexBuffer::load(void * vert_list, UINT vert_size, UINT vert_list_size, void * shader_byte_code, UINT shader_byte_size)
{
	if (VBuffer) VBuffer->Release();
	if (inputLayout) inputLayout->Release();

	D3D11_BUFFER_DESC buff_desc = {};

	// Buffer can be written and read by the GPU
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	// The size in bytes of our buffer
	buff_desc.ByteWidth = vert_size * vert_list_size;
	// Bind the buffer to the graphics pipeline
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = vert_list;

	vb_vert_size = vert_size;
	vb_vert_list_size = vert_list_size;

	if (FAILED(GraphicsEngine::get()->d3d_device->CreateBuffer(&buff_desc, &init_data, &VBuffer)))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC input_layout[] =
	{
		// Semantic name, Semantic index, Format, Input slot, Aligned byte offset, Input slot class, Instance data step rate
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Color", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Color", 1, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	UINT input_layout_size = ARRAYSIZE(input_layout);
	
	if (FAILED(GraphicsEngine::get()->d3d_device->CreateInputLayout(input_layout, input_layout_size, shader_byte_code, shader_byte_size, &inputLayout))) return false;

	return true;
}

bool VertexBuffer::release()
{
	inputLayout->Release();
	VBuffer->Release();
	delete this;

	return true;
}

UINT VertexBuffer::getVertexListSize()
{
	return this->vb_vert_list_size;
}
