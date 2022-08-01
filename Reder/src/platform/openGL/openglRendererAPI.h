#pragma once
#include "reder/renderer/rendererAPI.h"

namespace reder {
	class DLL_API openglRendererAPI :public rendererAPI {
	public:
		virtual void clear() override;
		virtual void clearColor(const glm::vec4 color) override;
		virtual void drawIndex(const std::shared_ptr<vertexArray>& vA) override;
	};
}