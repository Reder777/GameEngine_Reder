#include "repch.h"
#include "imguiLayer.h"


#include "imgui.h"
#include "platform/openGL/imguiOpenGL.h"
#include "reder/application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>




namespace reder {

	imguiLayer::imguiLayer():layer("imguiLayer"){}
	imguiLayer::~imguiLayer(){}

	void imguiLayer::onEvent(event& e){
		eventDispatcher imguiDispatcher(e);
		imguiDispatcher.Dispatch<keyPressedEvent>(RE_BIND_EVENT(imguiLayer::imguiKeyPressedEvent));
		imguiDispatcher.Dispatch<keyReleasedEvent>(RE_BIND_EVENT(imguiLayer::imguiKeyReleasedEvent));
		imguiDispatcher.Dispatch<mouseButtonPressedEvent>(RE_BIND_EVENT(imguiLayer::imguiMouseButtonPressedEvent));
		imguiDispatcher.Dispatch<mouseButtonReleasedEvent>(RE_BIND_EVENT(imguiLayer::imguiMouseButtonReleasedEvent));
		imguiDispatcher.Dispatch<mouseMovedEvent>(RE_BIND_EVENT(imguiLayer::imguiMouseMovedEvent));
		imguiDispatcher.Dispatch<mouseScrolledEvent>(RE_BIND_EVENT(imguiLayer::imguiMouseScrolledEvent));
		imguiDispatcher.Dispatch<windowResizeEvent>(RE_BIND_EVENT(imguiLayer::imguiWindowResizedEvent));
		imguiDispatcher.Dispatch<keyTypedEvent>(RE_BIND_EVENT(imguiLayer::imguiKeyTypedEvent));
	}

	

	void imguiLayer::attach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMPORARY: should eventually use Hazel key codes
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void imguiLayer::detach() {

	}

	void imguiLayer::onUpdate() {
		ImGuiIO& io = ImGui::GetIO();
		application& app = application::getApp();
		io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//RE_CORE_INFO("imgui layer update!");
	}

	bool imguiLayer::imguiKeyPressedEvent(keyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.getKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}
	bool imguiLayer::imguiKeyReleasedEvent(keyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.getKeyCode()] = false;
		return false;
	}
	bool imguiLayer::imguiMouseButtonPressedEvent(mouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
		return false;
	}
	bool imguiLayer::imguiMouseButtonReleasedEvent(mouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;
		return false;
	}
	bool imguiLayer::imguiMouseMovedEvent(mouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.getXPos(), e.getYPos());
		return false;
	}
	bool imguiLayer::imguiMouseScrolledEvent(mouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += e.getYOffset();
		io.MouseWheelH += e.getXOffset();
		return false;
	}
	bool imguiLayer::imguiWindowResizedEvent(windowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.getWidth(), e.getHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.getWidth(), e.getHeight());

		return false;
	}
	bool imguiLayer::imguiKeyTypedEvent(keyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.getKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);
		return false;
	}
}
