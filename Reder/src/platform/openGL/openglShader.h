#pragma once
#include "reder/core.h"
#include "reder/renderer/shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace reder {

	class DLL_API openglShader :public shader {
	public:
		openglShader(const std::string& vertexSource, const std::string& fragmentSource);
		~openglShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		void uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;
		void uploadUniformMat3(const std::string& name, const glm::mat3& matrix) const;
		void uploadUniformFloat4(const std::string& name, const glm::vec4& value ) const;
		void uploadUniformFloat3(const std::string& name, const glm::vec3& value) const;
		void uploadUniformFloat2(const std::string& name, const glm::vec2& value) const;

		void uploadUniformFloat(const std::string& name, float value) const;
		void uploadUniformInt(const std::string& name, int value) const;
	private:
		uint32_t m_RendererId;
	};
}