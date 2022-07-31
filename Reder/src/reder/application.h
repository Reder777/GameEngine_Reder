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

		void pushOverLayer(layer* overlayer);

		inline window& getWindow() { return *m_Window; }

		inline static application& getApp() { return *app_Instance; }

	private:

		bool windowClose(windowCloseEvent& e);
		std::unique_ptr<window> m_Window;


		std::unique_ptr<shader> m_Shader;
		std::shared_ptr<vertexArray> m_vertexArray;


		std::unique_ptr<shader> m_Shader_square;
		std::shared_ptr<vertexArray> m_vertexArray_square;


		imguiLayer* m_imguiLayer;
		bool m_Running = true;
		layerStack m_layStack;


		//singleton 
		// initialized in application.cpp application() constructor
		static application* app_Instance;
	};

	application* createSandbox();

}