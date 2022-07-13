#pragma once


#include "event.h"
#include <sstream>


namespace reder {

	class DLL_API windowResizeEvent : public event {
	public:
		inline unsigned int getWidth() { return r_width; }
		inline unsigned int getHeight() { return r_height; }

		windowResizeEvent(unsigned int width, unsigned int height)
			: r_width(width), r_height(height) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << r_width << ", " << r_height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int r_width, r_height;
	};

	class DLL_API windowCloseEvent :public event {
	public:
		
		windowCloseEvent() {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowCloseEvent: ";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}