#pragma once
#include "core.h"
#include "window.h"
#include "event/windowEvent.h"
namespace reder{
	class DLL_API application
	{
	public:
		application();

		virtual ~application();

		void run();

		void OnEvent(event& e);

		bool windowClose(windowCloseEvent& e);
	private:
		
		std::unique_ptr<window> m_Window;
		bool m_Running = true;
	
	};

	application* createSandbox();

}