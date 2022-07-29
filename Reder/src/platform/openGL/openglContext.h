#pragma once

#include "reder/renderer/grahpicsContext.h"
#include "reder/core.h"
#include <GLFW/glfw3.h>


namespace reder {
	class DLL_API openglContext :public grahpicsContext {
	public:
		openglContext(GLFWwindow* glfwWindow);
		virtual void init() override;
		virtual void swapBuffers() override;

	private:
		GLFWwindow* m_glfwWindow;
	};
}
