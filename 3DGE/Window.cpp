#include "Window.h"

// Window* window = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
		
	case WM_CREATE:
	{
		// Event that triggers on window creation
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);

		window->setHWND(hwnd);
		window->onCreate();
		break;
	}

	case WM_SETFOCUS:
	{
		// Event that triggers on window focused/selected
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onFocus();
		break;
	}

	case WM_KILLFOCUS:
	{
		// Event that triggers on window defocused/deselected
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDefocus();
		break;
	}

	case WM_DESTROY:
	{
		// Event that triggers on window destruction
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		PostQuitMessage(0);
		break;
	}

	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

bool Window::init()
{
	// Setting up WNDCLASSEX object
	WNDCLASSEX winCl;
	winCl.cbClsExtra = NULL;
	winCl.cbSize = sizeof(WNDCLASSEX);
	winCl.cbWndExtra = NULL;
	winCl.hbrBackground = (HBRUSH)COLOR_WINDOW;
	winCl.hCursor = LoadCursor(NULL, IDC_ARROW);
	winCl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winCl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	winCl.hInstance = NULL;
	winCl.lpszClassName = "GEwinCl";
	winCl.lpszMenuName = "";
	winCl.style = NULL;
	winCl.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&winCl)) return false; // If the registration of class WNDCLASSEX fails, function returns false
	
	// if (!window) window = this;

	// Creating the window
	winHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "GEwinCl", "3DGE DX11", WS_CAPTION|WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this);

	// If creating the window didn't work return false
	if (!winHandle) return false;

	// Show the window
	::ShowWindow(winHandle, SW_SHOW);
	::UpdateWindow(winHandle);

	// Set flag to true to indicate window is initialized and running
	win_Running = true;

	return true;
}

bool Window::broadcast()
{
	MSG msg;

	this->onUpdate();

	// PeekMessage allows to get the message from the queue of messages from the OS
	// We will peek until this queue is empty
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) 
	{ 
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	// Pause that allows the CPU to handle the loop so it doesn't throttle
	Sleep(1);

	return true;
}

bool Window::release()
{
	// Destroy the window
	if (!::DestroyWindow(winHandle)) return false;

	return true;
}

bool Window::isRun()
{
	return win_Running;
}

RECT Window::getClientWindowRect()
{
	RECT rect;
	::GetClientRect(this->winHandle, &rect);

	return rect;
}

void Window::setHWND(HWND hwnd)
{
	this->winHandle = hwnd;
}

void Window::onCreate()
{
}

void Window::onUpdate()
{
}

void Window::onDestroy()
{
	win_Running = false;
}

void Window::onFocus()
{
}

void Window::onDefocus()
{
}
