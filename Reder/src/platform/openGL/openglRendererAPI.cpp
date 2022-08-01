#include "repch.h"
#include "openglRendererAPI.h"
#include <glad/glad.h>

namespace reder {
	void openglRendererAPI::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void openglRendererAPI::clearColor(const glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void openglRendererAPI::drawIndex(const std::shared_ptr<vertexArray>& vA)
	{
		glDrawElements(GL_TRIANGLES, vA->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}
}