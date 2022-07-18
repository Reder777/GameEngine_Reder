#include "repch.h"
#include "windowsWindow.h"
#include "reder/log.h"
#include "event/appEvent.h"
#include "event/keyboardEvent.h"
#include "event/mouseEvent.h"
#include "event/windowEvent.h"


namespace reder {
	static bool s_GLFWinitialized = false;
	window* window::createWindows(const windowProp& windowProp) {
		return new windowsWindow(windowProp);
	}

	windowsWindow::windowsWindow(const windowProp& windowProp) {
		init(windowProp);
	}

	windowsWindow::~windowsWindow() {
		shutDown();
	}

	void windowsWindow::init(const windowProp& windowProp) {
		m_windowData.m_title = windowProp.m_title;
		m_windowData.m_height = windowProp.m_height;
		m_windowData.m_width = windowProp.m_width;

		RE_CORE_INFO("start creating windows title:{0} height:{1} width:{2} !", m_windowData.m_title, m_windowData.m_height, m_windowData.m_width);
		if (!s_GLFWinitialized) {
			int ifSucceed = glfwInit();
			RE_CORE_ASSERT(ifSucceed, "initialize glfw failed!");
			s_GLFWinitialized = true;
		}

		glfwWindow = glfwCreateWindow((int)windowProp.m_width, (int)windowProp.m_height, windowProp.m_title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(glfwWindow);
		glfwSetWindowUserPointer(glfwWindow, &m_windowData);
		setVSync(true);

		/*
		-----------------------------------------------callback function-----------------------------------------------------------
		including windows,keyboard,mouse event.
		*/
		glfwSetWindowCloseCallback(glfwWindow, [](GLFWwindow* glfwWindow) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(glfwWindow);
			event &e = windowCloseEvent();
			data.m_eventCallbackFn(e);
			});

		glfwSetWindowSizeCallback(glfwWindow, [](GLFWwindow* glfwWindow,int width,int height) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(glfwWindow);
			event& e = windowResizeEvent(width, height);
			data.m_width = width;
			data.m_height = height;
			data.m_eventCallbackFn(e);
			});

		glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow* glfwWindow, int button, int action,int mods) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(glfwWindow);

			switch (action) {
				case GLFW_PRESS: {
					event& e = mouseButtonPressedEvent(button);
					data.m_eventCallbackFn(e);
					break;
				}
				case GLFW_RELEASE: {
					event& e = mouseButtonReleasedEvent(button);
					data.m_eventCallbackFn(e);
					break;
				}
			}
			});

		glfwSetScrollCallback(glfwWindow, [](GLFWwindow* glfwWindow, double x_Offset, double y_Offset) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(glfwWindow);
			event& e = mouseScrolledEvent((float)x_Offset, (float)y_Offset);
			data.m_eventCallbackFn(e);
			});


		glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow* glfwWindow,double xPos,double yPos) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(glfwWindow);
			event& e = mouseMovedEvent((float)xPos, (float)yPos);
			data.m_eventCallbackFn(e);
			});


		glfwSetKeyCallback(glfwWindow, [](GLFWwindow* glfwWindow, int key,int scancode, int action, int mods) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(glfwWindow);

			switch (action) {
				case GLFW_PRESS: {
					event& e = keyPressedEvent(key, 0);
					data.m_eventCallbackFn(e);
					break;
				}
				case GLFW_RELEASE: {
					event& e = keyReleasedEvent(key);
					data.m_eventCallbackFn(e);
					break;
				}
				case GLFW_REPEAT: {
					event& e = keyPressedEvent(key, 1);
					data.m_eventCallbackFn(e);
					break;
				}
			}
			});



	}

	void windowsWindow::shutDown() {
		glfwDestroyWindow(glfwWindow);
	}

	void windowsWindow::setVSync(bool enabled)  {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		m_windowData.VSync = enabled;
	}

	bool windowsWindow::isVSync()const {
		return m_windowData.VSync;
	}

	void windowsWindow::onUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(glfwWindow);
	}
}