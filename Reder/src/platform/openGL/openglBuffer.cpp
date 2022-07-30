#include "repch.h"
#include "openglBuffer.h"
namespace reder {
	/*
	-----------------------------opengl vertex buffer----------------------------
	*/
	openglVertexBuffer::openglVertexBuffer(float* vertices, RE_BUFFER_INT size)
	{
		glCreateBuffers(1, &m_VertexBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	openglVertexBuffer::~openglVertexBuffer() {
		glDeleteBuffers(1, &m_VertexBufferId);
	}
	void openglVertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
	}
	void openglVertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/*
	-----------------------------opengl index buffer-----------------------------
	*/
	openglIndexBuffer::openglIndexBuffer(RE_BUFFER_INT* indices, RE_BUFFER_INT count)
		:m_count(count)
	{
		glCreateBuffers(1, &m_IndexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(RE_BUFFER_INT), indices, GL_STATIC_DRAW);
	}
	openglIndexBuffer::~openglIndexBuffer() {
		glDeleteBuffers(1, &m_IndexBufferId);
	}
	void openglIndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId);
	}
	void openglIndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}