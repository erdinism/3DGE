#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"

DeviceContext::DeviceContext(ID3D11DeviceContext * dev_context):d3d_dev_context(dev_context)
{
}

void DeviceContext::clearRenderTargetColor(SwapChain * swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = {red, green, blue ,alpha};
	d3d_dev_context->ClearRenderTargetView(swap_chain->RTV, clear_color);

	// set which render target to draw -> the back buffer of the swap chain
	d3d_dev_context->OMSetRenderTargets(1, &swap_chain->RTV, NULL);
}

void DeviceContext::setVertexBuffer(VertexBuffer * vertexBuffer)
{
	// stride = size of vertex type
	UINT stride = vertexBuffer->vb_vert_size;
	// variable that allowes us to set the beggining of the buffer in bytes
	UINT offset = 0;

	d3d_dev_context->IASetVertexBuffers(0, 1, &vertexBuffer->VBuffer, &stride, &offset);
	d3d_dev_context->IASetInputLayout(vertexBuffer->inputLayout);
}

void DeviceContext::setIndexBuffer(IndexBuffer* indexBuffer)
{
	d3d_dev_context->IASetIndexBuffer(indexBuffer->IBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::drawTriangleList(UINT vert_count, UINT vert_start_index)
{
	// notify directX that the vertex buffer is composed by a list of triangles 
	d3d_dev_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	d3d_dev_context->Draw(vert_count, vert_start_index);
}

void DeviceContext::drawIndexedTriangleList(UINT index_count, UINT index_start_location, UINT vert_start_location)
{
	d3d_dev_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	d3d_dev_context->DrawIndexed(index_count, index_start_location, vert_start_location);
}

void DeviceContext::drawTriangleStrip(UINT vert_count, UINT vert_start_index)
{
	d3d_dev_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	d3d_dev_context->Draw(vert_count, vert_start_index);
}

void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT viewport = {};
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	d3d_dev_context->RSSetViewports(1, &viewport);
}

void DeviceContext::setVertexShader(VertexShader * vert_shader)
{
	d3d_dev_context->VSSetShader(vert_shader->vertexShader, nullptr, 0);
}

void DeviceContext::setPixelShader(PixelShader * px_shader)
{
	d3d_dev_context->PSSetShader(px_shader->pixelShader, nullptr, 0);
}

void DeviceContext::setConstantBuffer(VertexShader * vert_shader, ConstantBuffer * buffer)
{
	d3d_dev_context->VSSetConstantBuffers(0, 1, &buffer->CBuffer);
}

void DeviceContext::setConstantBuffer(PixelShader * px_shader, ConstantBuffer * buffer)
{
	d3d_dev_context->PSSetConstantBuffers(0, 1, &buffer->CBuffer);
}

bool DeviceContext::Release()
{
	d3d_dev_context->Release();
	delete this;
	return true;
}
