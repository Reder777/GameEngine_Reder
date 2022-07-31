#include "repch.h"
#include "vertexArray.h"
#include "reder/renderer/rendererAPI.h"
#include "platform/openGL/openglVertexArray.h"

namespace reder {
	vertexArray* vertexArray::create()
	{
        switch (rendererAPI::getLibrary()) {
            case renderGraphicsLibrary::None:
                RE_CORE_ASSERT(false, "vertexArray::create : no render graphics library!");
                break;
            case renderGraphicsLibrary::Opengl:
                return new openglVertexArray();
        }
        RE_CORE_ASSERT(false, "vertexArray::create : unknown graphics library!");
        return nullptr;
	}
}