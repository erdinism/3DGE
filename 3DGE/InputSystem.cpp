#include "InputSystem.h"
#include <Windows.h>

void InputSystem::update()
{
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	if (first_time)
	{
		old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
		first_time = false;
	}

	if (current_mouse_pos.x != old_mouse_pos.coord_X || current_mouse_pos.y != old_mouse_pos.coord_Y)
	{
		// Mouse has moved
		std::unordered_set<InputListener*>::iterator it = listenerSet.begin();

		while (it != listenerSet.end())
		{
			(*it)->onMouseMove(Point(current_mouse_pos.x, current_mouse_pos.y));
			++it;
		}
	}

	old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);

	if (::GetKeyboardState(keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			// Key is down
			if (keys_state[i] & 0x80)
			{
				std::unordered_set<InputListener*>::iterator it = listenerSet.begin();

				while (it != listenerSet.end())
				{
					// The keys state can also be used for mouse
					if (i == VK_LBUTTON)
					{
						if (keys_state[i] != old_keys_state[i])
							(*it)->onLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					else if (i == VK_RBUTTON)
					{
						if (keys_state[i] != old_keys_state[i])
							(*it)->onRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					else
						(*it)->onKeyDown(i);

					++it;
				}
			}
			// Key is up
			else
			{
				if (keys_state[i] != old_keys_state[i])
				{
					std::unordered_set<InputListener*>::iterator it = listenerSet.begin();

					while (it != listenerSet.end())
					{
						if (i == VK_LBUTTON)
							(*it)->onLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						else if (i == VK_RBUTTON)
							(*it)->onRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						else
							(*it)->onKeyUp(i);

						++it;
					}
				}
			}
		}

		// Store current keys state to old keys state
		::memcpy(old_keys_state, keys_state, sizeof(unsigned char) * 256);
	}
}

InputSystem* InputSystem::get()
{
	static InputSystem system;
	return &system;
}

void InputSystem::addListener(InputListener* listener)
{
	listenerSet.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	listenerSet.erase(listener);
}

void InputSystem::setCursorPosition(const Point& position)
{
	::SetCursorPos(position.coord_X, position.coord_Y);
}

void InputSystem::showCursor(bool showing)
{
	::ShowCursor(showing);
}
