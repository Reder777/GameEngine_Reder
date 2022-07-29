#pragma once

#include "reder/core.h"


namespace reder {
	class DLL_API shader {
	public:
		shader() {};
		~shader() {};

		virtual void bind() const {};
		virtual void unbind() const {};
	};
}