#pragma once
#include "reder/core.h"
#include "reder/renderer/rendererAPI.h"
#include <glm/glm.hpp>


namespace reder {
	class DLL_API renderCommand {
	public:
		inline static void init() {
			m_rendererAPI->init();
		}
		inline static void clear() {
			m_rendererAPI->clear();
		}

		inline static void clearColor(const glm::vec4 color) {
			m_rendererAPI->clearColor(color);
		}

		inline static void drawIndex(const std::shared_ptr<vertexArray>& vA) {
			m_rendererAPI->drawIndex(vA);
		}

	private:
		static rendererAPI* m_rendererAPI;
	};
}