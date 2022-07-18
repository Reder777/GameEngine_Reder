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
			m_Window->onUpdate();
		}
		
	}

	bool application::windowClose(windowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	void application::OnEvent(event& e) {
		eventDispatcher m_eventDispatcher(e);
		m_eventDispatcher.Dispatch<windowCloseEvent>(std::bind(&application::windowClose,this,std::placeholders::_1));
		RE_CORE_INFO("{0}", e);
	}


}