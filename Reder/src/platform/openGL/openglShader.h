#pragma once
#include "reder/core.h"
#include "reder/renderer/shader.h"

namespace reder {

	class DLL_API openglShader :public shader {
	public:
		openglShader(const std::string& vertexSource, const std::string& fragmentSource);
		~openglShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const override;
	private:
		uint32_t m_RendererId;
	};
}