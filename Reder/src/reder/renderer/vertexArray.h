#pragma once

#include "reder/core/core.h"
#include "reder/renderer/buffers.h"

namespace reder {
	class DLL_API vertexArray {
	public:
		~vertexArray(){}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void addVertexBuffer(std::shared_ptr<vertexBuffer>& vb) = 0;
		virtual void setIndexBuffer(std::shared_ptr<indexBuffer>& ib) = 0;

		virtual const std::vector<std::shared_ptr<vertexBuffer>>& getVertexBuffers() const =0;
		virtual const std::shared_ptr<indexBuffer>& getIndexBuffer() const=0;

		static vertexArray* create();
	private:
		
	};
	
}