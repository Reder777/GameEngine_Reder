#include "application.h"
#include "log.h"
#include "event/windowEvent.h"

namespace reder {

	application::application() {

	}

	application::~application() {

	}

	void application::run() {
		windowResizeEvent e(1280, 720);
		if (e.isInCategory(EventCategoryApplication))
		{
			RE_CLIENT_TRACE(e);
		}
		if (e.isInCategory(EventCategoryInput))
		{
			RE_CLIENT_TRACE(e);
		}

		while (true);
		
	}
}