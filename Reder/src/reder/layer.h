#pragma once
#include "core.h"
#include "reder/event/event.h"
#include "reder/core/timeStamp.h"

namespace reder {
	class DLL_API layer
	{
	public:
		layer(const std::string& name = "layer");
		virtual ~layer();
		virtual void onEvent(event& e){}
		virtual void onUpdate(timeStamp t) {}
		virtual void imguiRender(){}
		virtual void attach() {}
		virtual void detach() {}

		inline const std::string& getName() const { return debugName; }
	protected:
		std::string debugName;

	};

}