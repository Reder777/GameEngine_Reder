#pragma once

#include "event.h"


namespace reder {
	class DLL_API mouseMovedEvent :public event {

	public:
		mouseMovedEvent(float x,float y) :x_Pos(x), y_Pos(y) {}
		inline float getXPos() const { return x_Pos; }
		inline float getYPos() const { return y_Pos; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "mouseMovedEvent:x_Pos  " << x_Pos << " ,y_Pos " << y_Pos;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryInput| EventCategoryMouse)
	private:
		float x_Pos, y_Pos;
	};

	class DLL_API mouseScrolledEvent :public event {
	public:
		mouseScrolledEvent(float x,float y):x_Offset(x),y_Offset(y){}
		inline float getXOffset() const { return x_Offset; }
		inline float getYOffset() const { return y_Offset; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "mouseScrolledEvent:x_Offset  " << x_Offset << " ,y_Offset " << y_Offset;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryInput| EventCategoryMouse)
	private:
		float x_Offset, y_Offset;
	};

	class DLL_API mouseButtonEvent : public event
	{
	public:
		inline int GetMouseButton() const { return r_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	protected:
		mouseButtonEvent(int button)
			: r_Button(button) {}

		int r_Button;
	};

	class DLL_API mouseButtonPressedEvent : public mouseButtonEvent
	{
	public:
		mouseButtonPressedEvent(int button)
			: mouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "mouseButtonPressedEvent: " << r_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class DLL_API mouseButtonReleasedEvent : public mouseButtonEvent
	{
	public:
		mouseButtonReleasedEvent(int button)
			: mouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << r_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}