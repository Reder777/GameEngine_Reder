#pragma once

#include "reder/core.h"


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace reder {
	class DLL_API shader {
	public:
		shader() {};
		~shader() {};

		virtual void bind() const {};
		virtual void unbind() const {};

		virtual void uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const {};
		static shader* createShader(const std::string& vertexSource, const std::string& fragmentSource);

	private:
	};


}