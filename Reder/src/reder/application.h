#pragma once
#include "core.h"
namespace reder{
	class DLL_API application
	{
	public:
		application();

		virtual ~application();

		void run();
	};

	application* createSandbox();

}