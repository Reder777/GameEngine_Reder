#pragma once
#include "reder/core.h"
#include "reder/layer.h"
#include "reder/event/keyboardEvent.h"
#include "reder/event/mouseEvent.h"
#include "reder/event/windowEvent.h"
#include "reder/event/appEvent.h"


namespace reder {


	class DLL_API imguiLayer:public layer
	{
	public:
		imguiLayer();
		~imguiLayer();

		void attach();
		void detach();

		void onEvent(event& e);
		void onUpdate();

	private:
		float m_Time = 0.0f;

		/*
		* actual event address function
		* link imgui event to reder event system
		*/
		bool imguiKeyPressedEvent(keyPressedEvent& e);
		bool imguiKeyReleasedEvent(keyReleasedEvent& e);
		bool imguiMouseButtonPressedEvent(mouseButtonPressedEvent& e);
		bool imguiMouseButtonReleasedEvent(mouseButtonReleasedEvent& e);
		bool imguiMouseMovedEvent(mouseMovedEvent& e);
		bool imguiMouseScrolledEvent(mouseScrolledEvent& e);
		bool imguiWindowResizedEvent(windowResizeEvent& e);
		bool imguiKeyTypedEvent(keyTypedEvent& e);
	};

}