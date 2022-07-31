#pragma once
#include "reder/core.h"


namespace reder {


	enum class bufferElementType {
		None=0,Int,Int2,Int3,Int4,Float,Float2,Float3,Float4,Mat3,Mat4,Bool
	};


	/*
	----------------------------------element stored in buffers-------------------------------
	*/
	struct bufferElement {
		std::string name;
		RE_BUFFER_INT size;
		RE_BUFFER_INT offset;
		bufferElementType type;
		bool normalized;

		bufferElement(bufferElementType type, const std::string& name,bool normal=false)
			:name(name),type(type),size(bufferElementTypeSize(type)),offset(0),normalized(normal)
		{

		}

		RE_BUFFER_INT getComponentCount() const{
			switch (type)
			{
				case reder::bufferElementType::None:
					RE_CORE_ASSERT(false, "getComponentCount : no type defined!");
					return 0;
				case reder::bufferElementType::Int:				return 1;
				case reder::bufferElementType::Int2:			return 2;
				case reder::bufferElementType::Int3:			return 3;
				case reder::bufferElementType::Int4:			return 4;
				case reder::bufferElementType::Float:			return 1;
				case reder::bufferElementType::Float2:			return 2;
				case reder::bufferElementType::Float3:			return 3;
				case reder::bufferElementType::Float4:			return 4;
				case reder::bufferElementType::Mat3:			return 3 * 3;
				case reder::bufferElementType::Mat4:			return 4 * 4;
				case reder::bufferElementType::Bool:			return 1;
				default:										break;
			}
			RE_CORE_ASSERT(false, "getComponentCount : unknown type!");
			return 0;
		}

		RE_BUFFER_INT bufferElementTypeSize(bufferElementType type) {
			switch (type)
			{
				case reder::bufferElementType::None:
					RE_CORE_ASSERT(false, "elementTypeSize : no type defined!");
					return 0;
				case reder::bufferElementType::Int:			    return 4;
				case reder::bufferElementType::Int2:			return 4 * 2;
				case reder::bufferElementType::Int3:			return 4 * 3;
				case reder::bufferElementType::Int4:			return 4 * 4;
				case reder::bufferElementType::Float:			return 4;
				case reder::bufferElementType::Float2:			return 4 * 2;
				case reder::bufferElementType::Float3:			return 4 * 3;
				case reder::bufferElementType::Float4:			return 4 * 4;
				case reder::bufferElementType::Mat3:			return 4 * 3 * 3;
				case reder::bufferElementType::Mat4:			return 4 * 4 * 4;
				case reder::bufferElementType::Bool:			return 1;
				default:										break;
			}
			RE_CORE_ASSERT(false, "elementTypeSize : unknown type!");
			return 0;
		}
	};



	


	class DLL_API bufferLayout {
	public:
		bufferLayout(){}
		bufferLayout(const std::initializer_list<bufferElement>& elements)
			:m_elements(elements)
		{
			calculateOffsetAndStride();
		}
		inline const std::vector<bufferElement>& getElements() const { return m_elements; }
		std::vector<bufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<bufferElement>::iterator end()   { return m_elements.end(); }
		std::vector<bufferElement>::const_iterator begin() const {return m_elements.begin(); }
		std::vector<bufferElement>::const_iterator end() const { return m_elements.end(); }

	private:
		void calculateOffsetAndStride() {
			RE_BUFFER_INT offset=0;
			for (auto& element : m_elements) {
				element.offset = offset;
				offset += element.size;
			}
			m_stride = offset;
		}
		std::vector<bufferElement> m_elements;
		RE_BUFFER_INT m_stride = 0;
	};






	class DLL_API vertexBuffer {
	public:
		~vertexBuffer() {};
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const bufferLayout& getLayout() const = 0;
		virtual void setLayout(const bufferLayout& layout) = 0;

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