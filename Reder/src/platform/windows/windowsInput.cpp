#include "repch.h"
#include "windowsInput.h"
#include <GLFW/glfw3.h>
#include "reder/core/application.h"
namespace reder {
	bool windowsInput::isKeyPressedImpl(int keycode)
	{
		auto glfwWindow = static_cast<GLFWwindow*>(application::getApp().getWindow().getGlfwWindow());
		int status = glfwGetKey(glfwWindow, keycode);
		return (status == GLFW_PRESS) || (status == GLFW_REPEAT);
	}

	bool windowsInput::isMouseButtonPressedImpl(int button)
	{
		auto glfwWindow = static_cast<GLFWwindow*>(application::getApp().getWindow().getGlfwWindow());
		int status = glfwGetMouseButton(glfwWindow, button);
		return (status == GLFW_PRESS) ;
	}

	std::pair<float, float> windowsInput::getMousePositionImpl()
	{
		auto glfwWindow = static_cast<GLFWwindow*>(application::getApp().getWindow().getGlfwWindow());
		double xPos, yPos;
		glfwGetCursorPos(glfwWindow, &xPos, &yPos);
		return {(float)xPos,(float)yPos};
	}

	float windowsInput::getXImpl()
	{
		auto xyPos = getMousePositionImpl();

		return xyPos.first;
	}

	float windowsInput::getYImpl()
	{
		auto xyPos = getMousePositionImpl();

		return xyPos.second;
	}



	
}