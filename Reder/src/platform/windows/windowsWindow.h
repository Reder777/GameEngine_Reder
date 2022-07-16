#pragma once

#include <GLFW/glfw3.h>
#include "reder/window.h"
namespace reder {


	class windowsWindow:public window
	{
	public:
		windowsWindow(const windowProp& windowsProp);
		virtual ~windowsWindow();
		inline unsigned getWidth()const override { return m_windowData.m_width; }
		inline unsigned getHeight()const override { return m_windowData.m_height; }
		inline void setEventCallback(const eventCallbackFn& eventCallbackFn)override {
			m_windowData.m_eventCallbackFn = eventCallbackFn;
		}
		void setVSync(bool enabled) override;
		bool isVSync()const override;
		void onUpdate() override;

	private:
		virtual void init(const windowProp& windowsProp);
		virtual void shutDown();
	private:

		struct windowData {
			std::string m_title;
			unsigned int m_width, m_height;
			bool VSync;

			eventCallbackFn m_eventCallbackFn;

		};
		GLFWwindow* glfwWindow;
		windowData m_windowData;
	};

}