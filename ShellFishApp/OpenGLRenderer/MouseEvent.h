#pragma once
namespace Graphics
{
	enum MouseButton
	{
		mbLeft,
		mbRight,
		mbMiddle
	};

	enum ButtonState
	{
		bsPressed,
		bsReleased
	};

	enum Modifier
	{
		modShift,
		modCtrl,
		modAlt,
		modInvalid
	};

	struct MouseButtonEvent
	{
		int button = -1;
		int state = -1;
		int mods = -1;
		double xpos = 0, ypos = 0;
		MouseButtonEvent(int btn, int st, double x, double y):
			button(btn),
			state(st),
			xpos(x),
			ypos(y)	{}
		MouseButtonEvent() {}
	};

	struct MouseMoveEvent
	{
		double xpos, ypos;
		MouseMoveEvent(int x, int y) :
			xpos(x),
			ypos(y) {}
	};
}