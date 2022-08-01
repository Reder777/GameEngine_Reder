#include "repch.h"
#include "renderer.h"


namespace reder {
	void renderer::beginScene()
	{
	}
	void renderer::endScene()
	{
	}
	void renderer::submit(const std::shared_ptr<vertexArray>& vA)
	{
		vA->bind();
		renderCommand::drawIndex(vA);
	}
}