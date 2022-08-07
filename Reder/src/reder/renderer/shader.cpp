#include "repch.h"
#include "shader.h"

#include "reder/renderer/rendererAPI.h"
#include "platform/openGL/openglShader.h"


namespace reder {
	shader* shader::createShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
        switch (rendererAPI::getLibrary()) {
            case renderGraphicsLibrary::None:
                RE_CORE_ASSERT(false, "createShader::create : no render graphics library!");
                break;
            case renderGraphicsLibrary::Opengl:
                return new openglShader(vertexSource,fragmentSource);
            }
        RE_CORE_ASSERT(false, "createShader::create : unknown graphics library!");
        return nullptr;
	}
    shader* shader::createShader(const std::string& filePath)
    {
        switch (rendererAPI::getLibrary()) {
        case renderGraphicsLibrary::None:
            RE_CORE_ASSERT(false, "createShader::create : no render graphics library!");
            break;
        case renderGraphicsLibrary::Opengl:
            return new openglShader(filePath);
        }
        RE_CORE_ASSERT(false, "createShader::create : unknown graphics library!");
        return nullptr;
    }
}