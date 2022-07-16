#include "repch.h"
#include "application.h"
#include "log.h"
#include "event/windowEvent.h"


namespace reder {

	application::application() {
		m_Window = std::unique_ptr<window>(window::createWindows());
		m_Running = true;
	}

	application::~application() {

	}

	void application::run() {
	

		while (m_Running) {
			m_Window->onUpdate();
		}
		
	}


}