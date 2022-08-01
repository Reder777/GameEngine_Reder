#pragma once
#include "reder/renderer/renderCommand.h"
#include "reder/core.h"


namespace reder {
	class DLL_API renderer {

	public:
		static void beginScene();
		static void endScene();

		static void submit(const std::shared_ptr<vertexArray>& vA);
		inline static renderGraphicsLibrary getGraphicsLibrary() {
			return rendererAPI::getLibrary();
		}
	};
}