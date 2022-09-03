#pragma once
#include "reder/renderer/rendererAPI.h"

namespace reder {
	class DLL_API openglRendererAPI :public rendererAPI {
	public:
		virtual void init() override;
		virtual void clear() override;
		virtual void clearColor(const glm::vec4 color) override;
		virtual void drawIndex(const std::shared_ptr<vertexArray>& vA,uint32_t count=0) override;
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const override;
	};
}