#pragma once

#include "reder/core.h"




namespace reder {
	class DLL_API shader {
	public:
		shader() {};
		~shader() {};

		virtual void bind() const =0;
		virtual void unbind() const =0;

		static shader* createShader(const std::string& vertexSource, const std::string& fragmentSource);

	private:
	};


}