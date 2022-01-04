#pragma once

#include <d3d11.h>

class DeviceContext;

class ConstantBuffer
{
public:
	ConstantBuffer();

	// Points to the buffer and it's size in memory
	bool load(void * buffer, UINT buffer_size);

	void update(DeviceContext * dev_context, void * buffer);

	bool release();

private:
	ID3D11Buffer * CBuffer;

	friend class DeviceContext;
};