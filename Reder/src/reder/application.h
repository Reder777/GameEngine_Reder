#pragma once
#include "core.h"
#include "window.h"
#include "event/windowEvent.h"
#include "reder/event/appEvent.h"
#include "layerStack.h"

#include "imgui/imguiLayer.h"
#include "reder/renderer/shader.h"
#include "reder/renderer/buffers.h"
#include "reder/renderer/vertexArray.h"
#include "reder/renderer/orthographicCamera.h"


namespace reder{
	class DLL_API application
	{
		
	public:
		application();

		virtual ~application();

		void run();

		//deal with events
		void OnEvent(event& e);

		void popLayer(layer* layer);

		void pushLayer(layer* layer);

		void pushOverLayer(layer* overlayer);

		inline window& getWindow() { return *m_Window; }

		inline static application& getApp() { return *app_Instance; }

	private:

		bool windowClose(windowCloseEvent& e);
		bool windowResize(windowResizeEvent& e);
	private:
		static application* app_Instance;


		std::unique_ptr<window> m_Window;
		bool m_windowMinimized = false;


		imguiLayer* m_imguiLayer;
		layerStack m_layStack;


		float m_lastFrameTime = 0.0f;


		bool m_Running = true;

	};

	application* createSandbox();

}