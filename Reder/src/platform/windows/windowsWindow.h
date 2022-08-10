#pragma once

#include <GLFW/glfw3.h>
#include "reder/core/window.h"
#include "reder/renderer/grahpicsContext.h"



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
		inline virtual void* getGlfwWindow() const override{ return glfwWindow; }

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
		grahpicsContext* m_context;
		windowData m_windowData;
	};

}