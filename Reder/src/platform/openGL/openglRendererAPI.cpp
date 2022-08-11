#include "repch.h"
#include "openglRendererAPI.h"
#include <glad/glad.h>

namespace reder {
	void openglRendererAPI::init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}
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
	void openglRendererAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const
	{
		glViewport(x, y, width, height);
	}
}