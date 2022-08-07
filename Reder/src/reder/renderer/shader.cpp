#include "repch.h"
#include "shader.h"

#include "reder/renderer/rendererAPI.h"
#include "platform/openGL/openglShader.h"


namespace reder {
    /*
    ----------------------------------class Shader-------------------------------------------
    */
    ref<shader> shader::createShader(const std::string& name,const std::string& vertexSource, const std::string& fragmentSource)
	{
        switch (rendererAPI::getLibrary()) {
            case renderGraphicsLibrary::None:
                RE_CORE_ASSERT(false, "createShader::create : no render graphics library!");
                break;
            case renderGraphicsLibrary::Opengl:
                return std::make_shared<openglShader>(vertexSource,fragmentSource);
            }
        RE_CORE_ASSERT(false, "createShader::create : unknown graphics library!");
        return nullptr;
	}
    
    ref<shader> shader::createShader(const std::string& name,const std::string& filePath)
    {
        switch (rendererAPI::getLibrary()) {
        case renderGraphicsLibrary::None:
            RE_CORE_ASSERT(false, "createShader::create : no render graphics library!");
            break;
        case renderGraphicsLibrary::Opengl:
            return std::make_shared<openglShader>(name,filePath);
        }
        RE_CORE_ASSERT(false, "createShader::create : unknown graphics library!");
        return nullptr;
    }
    
    ref<shader> shader::createShader(const std::string& filePath)
    {
        switch (rendererAPI::getLibrary()) {
        case renderGraphicsLibrary::None:
            RE_CORE_ASSERT(false, "createShader::create : no render graphics library!");
            break;
        case renderGraphicsLibrary::Opengl:
            return std::make_shared<openglShader>(filePath);
        }
        RE_CORE_ASSERT(false, "createShader::create : unknown graphics library!");
        return nullptr;
    }


    /*
    ----------------------------------class ShaderLibrary------------------------------------
    */

    void shaderLibrary::addShader(const ref<shader>& shader)
    {
        std::string name = shader->getName();
        RE_CORE_ASSERT(m_shaderLibrary.find(name) == m_shaderLibrary.end(), "shader already exist!");
        m_shaderLibrary[name] = shader;
    }

    void shaderLibrary::addShader(const std::string& name, const ref<shader>& shader)
    {
        RE_CORE_ASSERT(m_shaderLibrary.find(name) == m_shaderLibrary.end(), "shader already exist!");
        m_shaderLibrary[name] = shader;
    }

    reder::ref<reder::shader> shaderLibrary::loadShader(const std::string& filePath)
    {
        auto shader = shader::createShader(filePath);
        addShader(shader);
        return shader;
    }

    reder::ref<reder::shader> shaderLibrary::loadShader(const std::string& name, const std::string& filePath)
    {
        auto shader = reder::shader::createShader(filePath);
        addShader(name,shader);
        return shader;
    }
    
    ref<shader> shaderLibrary::getByName(const std::string& name) const
    {
        auto iter = m_shaderLibrary.find(name);
        if (iter == m_shaderLibrary.end())return nullptr;
        return iter->second;
    }

    const std::string shaderLibrary::pathToName(const std::string& filePath) const
    {
        int begin = filePath.find_last_of("/\\");
        RE_CORE_ASSERT(begin == filePath.npos, "wrong file path!");
        int end = filePath.find_first_of(".") == filePath.npos ? filePath.size() - 1 : filePath.find_first_of(".");
        return filePath.substr(begin+1, end - begin-1);
    }
}