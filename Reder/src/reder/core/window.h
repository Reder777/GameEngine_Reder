#pragma once
#include "reder/core/core.h"
#include "reder/event/event.h"
namespace reder{

	struct windowProp
	{
		std::string m_title;
		unsigned int m_width;
		unsigned int m_height;

		windowProp(const std::string& title="Reder Engine",unsigned int width=1280,unsigned int height=720)
			:m_title(title),m_width(width),m_height(height){}

	};
	class DLL_API window {
	public:
		using eventCallbackFn = std::function<void(event&)>;
		window() {};
		virtual ~window() {};
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;
		static window* createWindows(const windowProp& windowProp=windowProp());

		virtual void* getGlfwWindow()const=0;
		virtual void setEventCallback(const eventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;
		virtual void onUpdate() = 0;
	};
}
