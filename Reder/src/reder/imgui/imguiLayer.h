#pragma once
#include "reder/core.h"
#include "reder/layer.h"


namespace reder {

	/*
	imgui layer is part of the engine
	not controlled by sandbox
	
	*/
	class DLL_API imguiLayer:public layer
	{
	public:
		imguiLayer();
		~imguiLayer();

		virtual void attach() override;
		virtual void detach() override;

		virtual void imguiRender() override;

		void begin();
		void end();
	private:
		float m_Time = 0.0f;

		
	};

}