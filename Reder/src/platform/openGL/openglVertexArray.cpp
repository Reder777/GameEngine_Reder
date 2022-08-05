#include "repch.h"
#include "openglVertexArray.h"
#include <glad/glad.h>

namespace reder {

	GLenum elementTypeToGLenum(bufferElementType type)
	{
		switch (type)
		{
		case reder::bufferElementType::None:
			RE_CORE_ASSERT(false, "elementTypeToGLenum : no type defined!");
			return 0;
		case reder::bufferElementType::Int:			    return GL_INT;
		case reder::bufferElementType::Int2:			return GL_INT;
		case reder::bufferElementType::Int3:			return GL_INT;
		case reder::bufferElementType::Int4:			return GL_INT;
		case reder::bufferElementType::Float:			return GL_FLOAT;
		case reder::bufferElementType::Float2:			return GL_FLOAT;
		case reder::bufferElementType::Float3:			return GL_FLOAT;
		case reder::bufferElementType::Float4:			return GL_FLOAT;
		case reder::bufferElementType::Mat3:			return GL_FLOAT;
		case reder::bufferElementType::Mat4:			return GL_FLOAT;
		case reder::bufferElementType::Bool:			return GL_BOOL;
		default:                             		    break;
		}
		RE_CORE_ASSERT(false, "elementTypeToGLenum : unknown type!");
		return 0;
	}


	openglVertexArray::openglVertexArray()
	{
		glGenVertexArrays(1, &m_vertexArrayId);
	}
	openglVertexArray::~openglVertexArray()
	{
		glDeleteVertexArrays(1, &m_vertexArrayId);
	}
	void openglVertexArray::bind() const
	{
		glBindVertexArray(m_vertexArrayId);
	}
	void openglVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
	void openglVertexArray::addVertexBuffer(std::shared_ptr<vertexBuffer>& vb)
	{
		glBindVertexArray(m_vertexArrayId);
		vb->bind();

		RE_BUFFER_INT index = 0;
		const auto& layout = vb->getLayout();
		for (auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.getComponentCount(),
				elementTypeToGLenum(element.type),
				element.normalized? GL_TRUE:GL_FALSE,
				layout.getStride(),
				(const void*)element.offset
			);
			index++;
		}
		m_vertexBuffers.push_back(vb);
	}
	void openglVertexArray::setIndexBuffer(std::shared_ptr<indexBuffer>& ib)
	{
		m_indexBuffer = ib;
	}
}