#pragma once

#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "InputListener.h"
#include "Matrix4x4.h"

class AppWindow : public Window, public InputListener
{
public:
	void update();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onDefocus() override;

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point& mouse_pos) override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;

private:
	SwapChain * swapChain;
	VertexBuffer * vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer * constantBuffer;
	VertexShader * vertexShader;
	PixelShader * pixelShader;

	long old_time;
	long new_time;

	float DELTA_TIME;
	float DELTA_POS;
	float DELTA_SCALE;
	float DELTA_ROTATE;

	float rotation_x = 0.0f;
	float rotation_y = 0.0f;

	float SCALE = 1;

	Matrix4x4 WORLD_CAMERA;
	// Sign of direction 1 moves forward , -1 moves backwards
	float forward = 0.0f;
	// Sign of direction 1 moves right , -1 moves left
	float rightward = 0.0f;
};

