#include "repch.h"
#include "application.h"
#include "log.h"
#include "event/windowEvent.h"


namespace reder {

	application::application() {
		m_Window = std::unique_ptr<window>(window::createWindows());
		m_Window->setEventCallback(std::bind(&application::OnEvent, this, std::placeholders::_1));
		m_Running = true;
	}

	application::~application() {

	}

	void application::run() {
	
		while (m_Running) {
			for (layer* layer : m_layStack) {
				layer->onUpdate();
			}
			m_Window->onUpdate();
		}
		
	}

	bool application::windowClose(windowCloseEvent& e) {
		m_Running = false;
		return true;
	}
	/*
		from the end of the layer stack ,send the events to it and check if handled
	
	*/
	void application::OnEvent(event& e) {
		eventDispatcher m_eventDispatcher(e);
		m_eventDispatcher.Dispatch<windowCloseEvent>(std::bind(&application::windowClose,this,std::placeholders::_1));
		RE_CORE_INFO("{0}", e);
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
	}
}