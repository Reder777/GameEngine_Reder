#include "repch.h"
#include "renderCommand.h"


#include "platform/openGL/openglRendererAPI.h"


namespace reder {

	rendererAPI* renderCommand::m_rendererAPI = new openglRendererAPI();

}