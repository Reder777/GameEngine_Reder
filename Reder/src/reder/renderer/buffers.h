#pragma once
#include "reder/core.h"


namespace reder {
	class DLL_API vertexBuffer {
	public:
		~vertexBuffer() {};
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static vertexBuffer* create(float* vertices, RE_BUFFER_INT size);
	};

	class DLL_API indexBuffer {
	public:
		~indexBuffer() {};
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual RE_BUFFER_INT getCount() const = 0;
		static indexBuffer* create(RE_BUFFER_INT* indices, RE_BUFFER_INT count);
	};
}