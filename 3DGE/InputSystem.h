#pragma once

#include "InputListener.h"
#include "Point.h"
#include <unordered_set>

class InputSystem
{
public:
	void update();

	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void setCursorPosition(const Point& position);
	void showCursor(bool showing);

	static InputSystem* get();

private:
	std::unordered_set<InputListener*> listenerSet;
	unsigned char keys_state[256] = {};
	unsigned char old_keys_state[256] = {};

	Point old_mouse_pos;
	bool first_time = true;
};

