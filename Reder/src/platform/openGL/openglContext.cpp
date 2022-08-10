#include "repch.h"
#include "openglContext.h"
#include "reder/core/log.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace reder {
	openglContext::openglContext(GLFWwindow* glfwWindow) 
		:m_glfwWindow(glfwWindow)
	{
	}

	void openglContext::init()
	{
		glfwMakeContextCurrent(m_glfwWindow);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RE_CORE_ASSERT(status, "Failed to initialize Glad!");

		RE_CORE_INFO("OpenGL Info:");
		RE_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		RE_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		RE_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}

	void openglContext::swapBuffers()
	{
		glfwSwapBuffers(m_glfwWindow);
	}
}