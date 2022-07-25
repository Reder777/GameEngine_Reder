#pragma once

#include "event.h"



namespace reder {

	class DLL_API appTick :public event {
	public:

		appTick() {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "appTick ";
			return ss.str();
		}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class DLL_API appUpdate :public event {
	public:

		appUpdate() {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "appUpdate ";
			return ss.str();
		}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class DLL_API appRender :public event {
	public:

		appRender() {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "appRender ";
			return ss.str();
		}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}