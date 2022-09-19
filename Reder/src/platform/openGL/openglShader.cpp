#include "repch.h"
#include "openglShader.h"
#include "reder/core/log.h"
#include "glad/glad.h"

namespace reder {

	static std::string pathToName(const std::string& filePath) {
		int begin = filePath.find_last_of("/\\");
		RE_CORE_ASSERT(begin == filePath.npos, "wrong file path!");
		int end = filePath.find_first_of(".") == filePath.npos ? filePath.size() - 1 : filePath.find_first_of(".");
		return filePath.substr(begin + 1, end - begin - 1);
	}

	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		RE_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	openglShader::openglShader(const std::string& filePath)
	{
		m_name = pathToName(filePath);
		std::string source = readFile(filePath);
		std::cout << source;
		auto shaderSources = preProcess(source);
		compile(shaderSources);
	}

	openglShader::openglShader(const std::string& name,const std::string& filePath)
		:m_name(name)
	{
		std::string source = readFile(filePath);
		auto shaderSources = preProcess(source);
		compile(shaderSources);
	}

	openglShader::openglShader(const std::string& name,const std::string& vertexSource, const std::string& fragmentSource)
		:m_name(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;
		compile(sources);
	}
	
	openglShader::~openglShader()
	{
		glDeleteProgram(m_RendererId);
	}
	
	void openglShader::bind() const
	{
		glUseProgram(m_RendererId);
	}
	
	void openglShader::unbind() const
	{
		glUseProgram(0);
	}



	void openglShader::setInt(const std::string& name, const int value)
	{
		uploadUniformInt(name, value);
	}

	void openglShader::setFloat(const std::string& name, const float value)
	{
		uploadUniformFloat(name, value);
	}

	void openglShader::setFloat2(const std::string& name, const glm::vec2& value)
	{
		uploadUniformFloat2(name, value);
	}

	void openglShader::setFloat3(const std::string& name, const glm::vec3& value)
	{
		uploadUniformFloat3(name, value);
	}

	void openglShader::setFloat4(const std::string& name, const glm::vec4& value)
	{
		uploadUniformFloat4(name, value);
	}

	void openglShader::setMat3(const std::string& name, const glm::mat3& value)
	{
		uploadUniformMat3(name, value);
	}

	void openglShader::setMat4(const std::string& name, const glm::mat4& value)
	{
		uploadUniformMat4(name, value);
	}

	void openglShader::setIntArray(const std::string& name, int* value, uint32_t count)
	{
		uploadUniformIntArray(name, value, count);
	}

	/*
	-----------------------------------------upload-----------------------------------------------
	*/
	void openglShader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	
	void openglShader::uploadUniformMat3(const std::string& name, const glm::mat3& matrix) const
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	
	void openglShader::uploadUniformFloat4(const std::string& name, const glm::vec4& value) const
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform4f(location, value.x,value.y,value.z,value.w);
	}
	
	void openglShader::uploadUniformFloat3(const std::string& name, const glm::vec3& value) const
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}
	
	void openglShader::uploadUniformFloat2(const std::string& name, const glm::vec2& value) const
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform2f(location, value.x, value.y);
	}
	
	void openglShader::uploadUniformFloat(const std::string& name, float value) const
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1f(location, value);
	}
	
	void openglShader::uploadUniformInt(const std::string& name, int value) const
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1i(location, value);
	}

	void openglShader::uploadUniformIntArray(const std::string& name, int* value, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1iv(location, count, value);
	}


	std::string openglShader::readFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in|std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			RE_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}
	
	std::unordered_map<GLenum, std::string> openglShader::preProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			RE_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			RE_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}
	
	void openglShader::compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint program = glCreateProgram();
		RE_CORE_ASSERT(shaderSources.size <= 2, "we only support 2 shaders for now!");
		std::array<GLenum,2> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				RE_CORE_ERROR("{0}", infoLog.data());
				RE_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++]=shader;
		}

		m_RendererId = program;

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			for (auto id : glShaderIDs)
				glDeleteShader(id);

			RE_CORE_ERROR("{0}", infoLog.data());
			RE_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		for (auto id : glShaderIDs)
			glDetachShader(program, id);
	}
}