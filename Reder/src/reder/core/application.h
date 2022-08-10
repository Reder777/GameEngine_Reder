#pragma once
#include "reder/core/core.h"
#include "reder/core/window.h"
#include "reder/core/layerStack.h"
#include "reder/event/windowEvent.h"
#include "reder/event/appEvent.h"

#include "reder/imgui/imguiLayer.h"
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

		inline bool getSolidView() const { return m_solidView; }

		bool setSolidView(bool solidView) { m_solidView = solidView; }

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

		bool m_solidView=false;

	};

	application* createSandbox();

}