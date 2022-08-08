#include "repch.h"
#include "renderCommand.h"


#include "platform/openGL/openglRendererAPI.h"


namespace reder {

	rendererAPI* renderCommand::m_rendererAPI = new openglRendererAPI();

	void renderCommand::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		m_rendererAPI->setViewport(x, y, width, height);
	}

}