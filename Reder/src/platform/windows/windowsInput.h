#pragma once
#include "reder/core.h"
#include "reder/input.h"


namespace reder {
	class windowsInput:public input 
	{
	protected:
		virtual bool isKeyPressedImpl(int keycode) override ;
		virtual bool isMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> getMousePositionImpl() override;
		virtual float getXImpl() override;
		virtual float getYImpl() override;

	};

}