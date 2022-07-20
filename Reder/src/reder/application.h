#pragma once
#include "core.h"
#include "window.h"
#include "event/windowEvent.h"
#include "layerStack.h"
namespace reder{
	class DLL_API application
	{
	public:
		application();

		virtual ~application();

		void run();

		void OnEvent(event& e);

		void popLayer(layer* layer);

		void pushLayer(layer* layer);
	private:
		bool windowClose(windowCloseEvent& e);
		std::unique_ptr<window> m_Window;
		bool m_Running = true;
		layerStack m_layStack;
	};

	application* createSandbox();

}