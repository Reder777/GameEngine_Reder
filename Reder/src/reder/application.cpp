#include "repch.h"
#include "application.h"
#include "log.h"

#include <glad/glad.h>
#include "platform/windows/windowsInput.h"



namespace reder {
	application* application::app_Instance = nullptr;
	input* input::input_instance = new windowsInput();;
	application::application() {

		RE_CORE_ASSERT(!app_Instance, "app already exists!");
		app_Instance = this;
		

		m_Window = std::unique_ptr<window>(window::createWindows());
		m_Window->setEventCallback(RE_BIND_EVENT(application::OnEvent));

		
	}

	application::~application() {

	}

	void application::run() {
	


		while (m_Running) {

			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			for (layer* layer : m_layStack) {
				layer->onUpdate();
			}
			m_Window->onUpdate();

			float x =input::getX();
			float y = input::getY();
			RE_CORE_TRACE("{0}  {1}", x, y);
		}
		
	}

	bool application::windowClose(windowCloseEvent& e) {
		m_Running = false;
		return true;
	}
	/*
		from the end of the layer stack ,send the events to it and check if handled
		question is i dont know why from the bottom
	
	*/
	void application::OnEvent(event& e) {
		eventDispatcher m_eventDispatcher(e);
		m_eventDispatcher.Dispatch<windowCloseEvent>(RE_BIND_EVENT(application::windowClose));
#ifdef SHOW_ALL_DEBUG_INFO
		RE_CORE_INFO("{0}", e);
#endif // SHOW_ALL_DEBUG_INFO

		
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