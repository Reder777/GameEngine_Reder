#pragma once

#include "core.h"

namespace reder {
	class DLL_API input {
	public:
		static bool isKeyPressed(int keycode) { return input_instance->isKeyPressedImpl(keycode); }
		static bool isMouseButtonPressed(int button) { return input_instance->isMouseButtonPressedImpl(button); }
		static std::pair<float, float> getMousePosition() { return input_instance->getMousePositionImpl(); }
		static float getY() { return input_instance->getYImpl(); }
		static float getX() { return input_instance->getXImpl(); }
	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;
		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> getMousePositionImpl() = 0;
		virtual float getXImpl() = 0;
		virtual float getYImpl() = 0;
	private:

		/*
		singleton 
		initialized in application.cpp before application() constructor
		*/
		static input* input_instance;
	};
}
