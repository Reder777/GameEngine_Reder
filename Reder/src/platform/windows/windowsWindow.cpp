#include "repch.h"
#include "windowsWindow.h"
#include "reder/log.h"


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