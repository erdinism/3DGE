#pragma once
#include <d3d11.h>

class DeviceContext;

class VertexBuffer
{
public:
	VertexBuffer();

	bool load(void * vert_list, UINT vert_size, UINT vert_list_size, void * shader_byte_code, UINT shader_byte_size);

	UINT getVertexListSize();

	bool release();

private:
	UINT vb_vert_size;
	UINT vb_vert_list_size;

	ID3D11Buffer * VBuffer;
	ID3D11InputLayout * inputLayout;

	friend class DeviceContext;
};