#include "repch.h"
#include "application.h"


#include "reder/log.h"
#include "reder/core/timeStamp.h"
#include "reder/renderer/renderCommand.h"
#include "reder/renderer/renderer.h"


#include "platform/windows/windowsInput.h"
#include "platform/openGL/openglShader.h"



#include <glad/glad.h>
#include <GLFW/glfw3.h>




namespace reder {
	application* application::app_Instance = nullptr;
	input* input::input_instance = new windowsInput();;


	application::application() {

		RE_CORE_ASSERT(!app_Instance, "app already exists!");
		app_Instance = this;
		
		m_Window = std::unique_ptr<window>(window::createWindows());
		//m_Window->setVSync(false);
		m_Window->setEventCallback(RE_BIND_EVENT(application::OnEvent));

		m_imguiLayer = new imguiLayer();
		pushOverLayer(m_imguiLayer);
		
	}

	application::~application() {

	}

	void application::run() {
	


		while (m_Running) {
			/*
			* to be rewrited!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			*/
			float currentTime = (float)glfwGetTime();
			timeStamp t = currentTime - m_lastFrameTime;
			m_lastFrameTime = currentTime;

			if (!m_windowMinimized) {
				for (layer* layer : m_layStack) {
					layer->onUpdate(t);
				}
			}
			m_imguiLayer->begin();
			for (layer* layer : m_layStack) {
				layer->imguiRender();
			}
			m_imguiLayer->end();
			m_Window->onUpdate();

		}
		
	}

	bool application::windowClose(windowCloseEvent& e) {
		m_Running = false;
		return true;
	}
	bool application::windowResize(windowResizeEvent& e)
	{
		if (e.getWidth() == 0 || e.getHeight() == 0)
		{
			m_windowMinimized= true;
			return false;
		}

		m_windowMinimized = false;
		renderer::windowResize(e.getWidth(), e.getHeight());

		return false;
	}
	/*
	*   question:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	*	from the end of the layer stack ,send the events to it and check if handled
	*	question is i dont know why from the bottom!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	*/
	void application::OnEvent(event& e) {
		eventDispatcher m_eventDispatcher(e);
		m_eventDispatcher.Dispatch<windowCloseEvent>(RE_BIND_EVENT(application::windowClose));
		m_eventDispatcher.Dispatch<windowResizeEvent>(RE_BIND_EVENT(application::windowResize));
		
		for (auto it = m_layStack.end(); it != m_layStack.begin();) {
			(*--it)->onEvent(e);
			if (e.getHandled() == true) {
				break;
			}
		}

	}

	void application::popLayer(layer* layer) {
		m_layStack.popLayer(layer);
	}

	void application::pushLayer(layer* layer) {
		m_layStack.pushLayer(layer);
		layer->attach();
	}

	void application::pushOverLayer(layer* overlayer) {
		m_layStack.pushOverLayer(overlayer);
		overlayer->attach();
	}
}


