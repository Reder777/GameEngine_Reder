#pragma once
#include "reder/core/core.h"
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

		static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

	private:
		static rendererAPI* m_rendererAPI;
	};
}