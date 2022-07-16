#pragma once
#include "core.h"
#include "window.h"
namespace reder{
	class DLL_API application
	{
	public:
		application();

		virtual ~application();

		void run();

	private:
		std::unique_ptr<window> m_Window;
		bool m_Running = true;
	};

	application* createSandbox();

}