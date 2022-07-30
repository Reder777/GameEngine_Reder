#pragma once

#include "reder/core.h"
#include "reder/renderer/buffers.h"
#include <glad/glad.h>


namespace reder {
	/*
	---------------------------opengl vertex buffer------------------------------
	*/

	class DLL_API openglVertexBuffer :public vertexBuffer {
	public:
		openglVertexBuffer(float* vertices, RE_BUFFER_INT size);
		virtual ~openglVertexBuffer();
		virtual void bind() const override;
		virtual void unbind() const override;
	private:
		RE_BUFFER_INT m_VertexBufferId;
	};
	/*
	---------------------------opengl index buffer-------------------------------
	*/

	class DLL_API openglIndexBuffer :public indexBuffer {
	public:
		openglIndexBuffer(RE_BUFFER_INT* indices, RE_BUFFER_INT count);
		virtual ~openglIndexBuffer();
		virtual void bind() const override;
		virtual void unbind() const override;
		inline virtual RE_BUFFER_INT getCount() const override { return m_count; };

	private:
		RE_BUFFER_INT m_count;
		RE_BUFFER_INT m_IndexBufferId;
	};
}