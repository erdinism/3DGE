#include "AppWindow.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include <Windows.h>
#include <iostream>
struct VERTEX
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

// DirectX handles constant data in VRAM in chunks of 16 bytes
__declspec(align(16))
struct CONSTANT
{
	Matrix4x4 WORLD;
	Matrix4x4 VIEW;
	Matrix4x4 PROJECTION_MATRIX;

	unsigned int TIME;
};

void AppWindow::update()
{
	CONSTANT buffer_const;

	buffer_const.TIME = ::GetTickCount();

	DELTA_POS += DELTA_TIME / 10.0f;

	if (DELTA_POS > 1.0f) DELTA_POS = 0;

	Matrix4x4 temp;

	DELTA_SCALE += DELTA_TIME / 0.55f;

	//buffer_const.WORLD.scale(Vector3D::lerp(Vector3D(0.5f, 0.5f, 0), Vector3D(1.0f, 1.0f, 0), (sin(DELTA_SCALE) + 1.0f) / 2.0f));

	//temp.translate(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), DELTA_POS));

	//buffer_const.WORLD *= temp;

	/*
	buffer_const.WORLD.scale(Vector3D(SCALE, SCALE, SCALE));

	temp.setId();
	temp.setZRotation(0.0f);
	buffer_const.WORLD *= temp;

	temp.setId();
	temp.setYRotation(rotation_y);
	buffer_const.WORLD *= temp;

	temp.setId();
	temp.setXRotation(rotation_x);
	buffer_const.WORLD *= temp;
	*/

	buffer_const.WORLD.setId();

	Matrix4x4 world_cam;
	world_cam.setId();
	
	temp.setId();
	temp.setXRotation(rotation_x);
	world_cam *= temp;

	temp.setId();
	temp.setYRotation(rotation_y);
	world_cam *= temp;

	Vector3D camera_pos = WORLD_CAMERA.getTranslation() + world_cam.getZdirection() * (forward * 0.1f);
	camera_pos = camera_pos + world_cam.getXdirection() * (rightward * 0.1f);

	world_cam.translate(camera_pos);

	// Save the camera matrix in the constant buffer
	WORLD_CAMERA = world_cam;

	// Make the camera matrix into a view matrix
	world_cam.inverse();

	buffer_const.VIEW = world_cam;
	//buffer_const.PROJECTION_MATRIX.orthogonalProjection((this->getClientWindowRect().right - this->getClientWindowRect().left) / 400.0f, (this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 400.0f, -4.0f, 4.0f);

	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	buffer_const.PROJECTION_MATRIX.perspectiveProjection(1.57f, ((float)width / (float)height), 0.1f, 100.0f);

	constantBuffer->update(GraphicsEngine::get()->getDeviceContext(), &buffer_const);
}

void AppWindow::onCreate()
{
	Window::onCreate();

	InputSystem::get()->addListener(this);
	InputSystem::get()->showCursor(false);

	GraphicsEngine::get()->init();
	swapChain = GraphicsEngine::get()->createSwapChain();

	RECT clientArea = this->getClientWindowRect();
	swapChain->init(this->winHandle, clientArea.right - clientArea.left, clientArea.bottom - clientArea.top);

	WORLD_CAMERA.translate(Vector3D(0, 0, -2));

	/*
	VERTEX vertex_list[] =
	{
		// Vertex list for the pyramid
		// Position						     Color 1	        Color 2
		{Vector3D(0, 1, 0),					Vector3D(1,0,0),	Vector3D(0,1,1)},
		{Vector3D(-0.5f, 0, 0.5f),			Vector3D(0,1,0),	Vector3D(1,0,1)},
		{Vector3D(0.5f, 0, 0.5f),			Vector3D(0,0,1),	Vector3D(1,1,0)},
		{Vector3D(0.5f, 0, -0.5f),			Vector3D(1,1,0),	Vector3D(0,0,1)},
		{Vector3D(-0.5f, 0, -0.5f),			Vector3D(1,0,0),	Vector3D(0,1,1)}
	};
	*/

	VERTEX vertex_list[] =
	{
		// Position						     Color 1	        Color 2
		// Front
		{Vector3D(-0.5f, -0.5f, -0.5f),   Vector3D(1,0,0),	Vector3D(0,1,1)},
		{Vector3D(-0.5f, 0.5f, -0.5f),    Vector3D(0,1,0),	Vector3D(1,0,1)},
		{Vector3D(0.5f, 0.5f, -0.5f),     Vector3D(0,0,1),	Vector3D(1,1,0)},
		{Vector3D(0.5f, -0.5f, -0.5f),	  Vector3D(1,1,0),	Vector3D(0,0,1)},

		// Back
		{Vector3D(0.5f, -0.5f, 0.5f),   Vector3D(1,0,0),	Vector3D(0,1,1)},
		{Vector3D(0.5f, 0.5f, 0.5f),    Vector3D(0,1,0),	Vector3D(1,0,1)},
		{Vector3D(-0.5f, 0.5f, 0.5f),     Vector3D(0,0,1),	Vector3D(1,1,0)},
		{Vector3D(-0.5f, -0.5f, 0.5f),	  Vector3D(1,1,0),	Vector3D(0,0,1)}
	};

	vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	UINT vertex_list_size = ARRAYSIZE(vertex_list);

	/*
	//Index list for pyramid
	unsigned int index_list[] = {
		0,1,2,
		2,3,0,
		3,4,0,
		4,1,0,
		1,3,2,
		3,1,4
	};
	*/

	unsigned int index_list[] = {
		// Front
		0,1,2, // First triangle
		2,3,0, // Second triangle

		// Back
		4,5,6,
		6,7,4,

		// Top
		1,6,5,
		5,2,1,

		// Bottom
		7,0,3,
		3,4,7,

		// Right
		3,2,5,
		5,4,3,

		// Left
		7,6,1,
		1,0,7
	};

	indexBuffer = GraphicsEngine::get()->createIndexBuffer();
	UINT index_list_size = ARRAYSIZE(index_list);

	indexBuffer->load(index_list, index_list_size);

	// GraphicsEngine::get()->createShaders(); OBSOLETE

	void* shader_byte_code = nullptr;
	size_t shader_size = 0;

	// VERTEX SHADER
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "VertexShaderMain", &shader_byte_code, &shader_size);

	vertexShader = GraphicsEngine::get()->createVertexShader(shader_byte_code, shader_size);

	vertexBuffer->load(vertex_list, sizeof(VERTEX), vertex_list_size, shader_byte_code, shader_size);

	GraphicsEngine::get()->releaseShaders();

	// PIXEL SHADER
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "PixelShaderMain", &shader_byte_code, &shader_size);

	pixelShader = GraphicsEngine::get()->createPixelShader(shader_byte_code, shader_size);

	GraphicsEngine::get()->releaseShaders();

	//////////////////////////////////////////////////////////////////

	CONSTANT buffer_const;
	buffer_const.TIME = 0;

	constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	constantBuffer->load(&buffer_const, sizeof(CONSTANT));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	// Clear the render target
	GraphicsEngine::get()->getDeviceContext()->clearRenderTargetColor(this->swapChain, 0, 0.5f, 0.5f, 1);

	// Set the viewport
	RECT clientArea = this->getClientWindowRect();
	GraphicsEngine::get()->getDeviceContext()->setViewportSize(clientArea.right - clientArea.left, clientArea.bottom - clientArea.top);

	update();

	// Bind the constant buffer to the graphics pipeline for each shader
	GraphicsEngine::get()->getDeviceContext()->setConstantBuffer(vertexShader, constantBuffer);
	GraphicsEngine::get()->getDeviceContext()->setConstantBuffer(pixelShader, constantBuffer);

	// Set the default shaders to be able to draw
	// GraphicsEngine::get()->setShaders(); OBSOLETE
	GraphicsEngine::get()->getDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::get()->getDeviceContext()->setPixelShader(pixelShader);

	// Set the vertices and indices of the triangles to draw
	GraphicsEngine::get()->getDeviceContext()->setVertexBuffer(vertexBuffer);
	GraphicsEngine::get()->getDeviceContext()->setIndexBuffer(indexBuffer);

	// Draw the triangles
	GraphicsEngine::get()->getDeviceContext()->drawIndexedTriangleList(indexBuffer->getIndexListSize(), 0, 0);

	swapChain->present(true);

	// Time calculations

	old_time = new_time;
	new_time = ::GetTickCount();

	DELTA_TIME = (old_time) ? ((new_time - old_time) / 1000.0f) : 0;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	vertexBuffer->release();
	indexBuffer->release();
	constantBuffer->release();
	swapChain->release();
	vertexShader->release();
	pixelShader->release();
	GraphicsEngine::get()->release();
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onDefocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		//rotation_x += 0.5f * DELTA_TIME;
		forward = 1.0f;
	}
	else if (key == 'S')
	{
		//rotation_x -= 0.5f * DELTA_TIME;
		forward = -1.0f;
	}
	else if (key == 'A')
	{
		//rotation_y += 0.5f * DELTA_TIME;
		rightward = -1.0f;
	}
	else if (key == 'D')
	{
		//rotation_y -= 0.5f * DELTA_TIME;
		rightward = 1.0f;
	}
}

void AppWindow::onKeyUp(int key)
{
	forward = 0.0f;
	rightward = 0.0f;
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	rotation_x += (mouse_pos.coord_Y - (height / 2.0f)) * DELTA_TIME * 0.1f;
	rotation_y += (mouse_pos.coord_X - (width / 2.0f)) * DELTA_TIME * 0.1f;

	InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
	SCALE = 0.5f;
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
	SCALE = 2.0f;
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
	SCALE = 1.0f;
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
	SCALE = 1.0f;
}