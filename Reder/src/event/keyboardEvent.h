#pragma once


#include "event.h"
#include <sstream>

namespace reder {
	class DLL_API keyboardEvent :public event {


	public:
		inline int getKeyCode() const{
			return r_keyCode;
		}
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard| EventCategoryInput)
	protected:
		int r_keyCode;
		keyboardEvent(int key):r_keyCode(key) {}
	};

	class DLL_API keyPressedEvent :public keyboardEvent {
	public:
		keyPressedEvent(int keyCode,int pressCount){
			r_keyCode = keyCode;
			r_pressCount = pressCount;
		}

		inline int getPressCount() const {
			return r_pressCount;
		}
		std::string ToString() const override {
			std::stringstream ss;
			ss << "keyPressedEvent:" <<r_keyCode<<"  "<<r_pressCount;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed);
	private:
		int r_pressCount;
	};

	class DLL_API keyReleasedEvent :public keyboardEvent {
	public:
		keyReleasedEvent(int keyCode) {
			r_keyCode = keyCode;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "keyReleasedEvent:" << r_keyCode ;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased);
	
	};
}