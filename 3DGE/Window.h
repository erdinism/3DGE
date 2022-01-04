#include <Windows.h>

class Window
{
public:
	// Create the window
	bool init();
	bool broadcast();

	// Destroy the window
	bool release();

	// Check if window is running
	bool isRun();

	// Retrieve the internal size of the window(title bar not included)
	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	// Events
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onDefocus();

protected:
	HWND winHandle;
	bool win_Running;
};