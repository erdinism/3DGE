#pragma once

#include <d3d11.h>

class DeviceContext;

class IndexBuffer
{
public:
	IndexBuffer();

	bool load(void* index_list, UINT index_list_size);

	UINT getIndexListSize();

	bool release();

private:
	UINT ib_index_list_size;

	ID3D11Buffer* IBuffer;

	friend class DeviceContext;
};