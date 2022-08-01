#pragma once

#include "reder/core.h"
#include "reder/renderer/vertexArray.h"


#include <glm/glm.hpp>

namespace reder {

	enum class renderGraphicsLibrary {
		None = 0, Opengl = 1
	};

	class rendererAPI {
	public:
		inline static renderGraphicsLibrary getLibrary() {
			return library_used;
		}
		virtual void clear() = 0;
		virtual void clearColor(const glm::vec4 color) = 0;
		virtual void drawIndex(const std::shared_ptr<vertexArray>& vA)=0;
	private:
		static renderGraphicsLibrary library_used;
	};
}