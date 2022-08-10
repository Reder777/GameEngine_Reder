#pragma once
#include "reder/core/core.h"
#include "reder/renderer/shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>



// TODO: REMOVE!
typedef unsigned int GLenum;

namespace reder {

	class DLL_API openglShader :public shader {
	public:
		openglShader(const std::string& name,const std::string& vertexSource, const std::string& fragmentSource);
		openglShader(const std::string& name,const std::string& filePath);
		openglShader(const std::string& filePath);
		~openglShader();

		virtual void bind() const override;
		virtual void unbind() const override;
		inline virtual std::string getName()const override { return m_name; }

		void uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;
		void uploadUniformMat3(const std::string& name, const glm::mat3& matrix) const;
		void uploadUniformFloat4(const std::string& name, const glm::vec4& value ) const;
		void uploadUniformFloat3(const std::string& name, const glm::vec3& value) const;
		void uploadUniformFloat2(const std::string& name, const glm::vec2& value) const;

		void uploadUniformFloat(const std::string& name, float value) const;
		void uploadUniformInt(const std::string& name, int value) const;

	private:
		std::string readFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> preProcess(const std::string& source);
		void compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_RendererId;
		std::string m_name;
	};
}