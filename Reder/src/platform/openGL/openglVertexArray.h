#pragma once

#include "reder/core/core.h"
#include "reder/renderer/vertexArray.h"


namespace reder {
	class DLL_API openglVertexArray :public vertexArray {
	public:
		openglVertexArray();
		~openglVertexArray();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void addVertexBuffer(std::shared_ptr<vertexBuffer>& vb) override;
		virtual void setIndexBuffer(std::shared_ptr<indexBuffer>& ib) override;

		virtual const std::vector<std::shared_ptr<vertexBuffer>>& getVertexBuffers() const override {
			return m_vertexBuffers;
		}

		virtual const std::shared_ptr<indexBuffer>& getIndexBuffer() const override {
			return m_indexBuffer;
		}

	private:
		std::vector<std::shared_ptr<vertexBuffer>> m_vertexBuffers;
		std::shared_ptr<indexBuffer> m_indexBuffer;
		RE_BUFFER_INT m_vertexArrayId;
	};
}