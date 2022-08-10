#pragma once


#include "reder/core/core.h"

namespace reder {
	class DLL_API grahpicsContext {

	public:
		virtual void init() = 0;
		virtual void swapBuffers() = 0;
	};
}