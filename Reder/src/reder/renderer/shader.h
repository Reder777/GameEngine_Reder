#pragma once

#include "reder/core.h"


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace reder {
	class DLL_API shader {
	public:
		shader() {};
		~shader() {};

		virtual void bind() const =0;
		virtual void unbind() const =0;

		virtual void uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const = 0;
	};
}