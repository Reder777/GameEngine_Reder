#include "repch.h"
#include "renderer2d.h"

#include "reder/core/core.h"
#include "vertexArray.h"
#include "shader.h"
#include "renderCommand.h"

#include "platform/opengl/openglShader.h"

namespace reder {


	struct quadVertex {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texCoord;
		float textureId;
		float tilingFactor;
	};

	struct batchData {
		const uint32_t count = 10000;
		const uint32_t maxIndices = 6 * count;
		const uint32_t maxVertex = 4 * count;
		static const uint32_t maxTextureSlot = 32;//renderer capility

		ref<vertexArray> batchVertexArray;
		ref<vertexBuffer> batchVertexBuffer;
		ref<indexBuffer> batchIndexBuffer;
		ref<shader> shader;
		ref<texture2D> whiteTexture;

		uint32_t indexCount = 0;
		quadVertex* quadVertexBufferBase = nullptr;
		quadVertex* quadVertexBufferPtr = nullptr;

		std::array<ref<texture2D>, maxTextureSlot> textureSlots;
		uint32_t textureIndex=1;//0 means white texture

	};
	static batchData s_data;


/*
	@Name		searchTexture
	@TimeStamp  2022/9/4
	@Func		check if texture has been added to texture slots,if not add it to textureSlots and return its new textureIndex
	@parameters	texture--------to be checked
	@Todo
*/
/*	static float searchTexture(ref<texture2D> texture) {
		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_data.textureIndex; i++) {
			if (*s_data.textureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}
		if (textureIndex == 0.0f) {
			textureIndex = (float)s_data.textureIndex;
			s_data.textureSlots[s_data.textureIndex] = texture;
			s_data.textureIndex++;
		}
		return textureIndex;
	}
*/


	void renderer2d::init()
	{
		s_data.batchVertexArray.reset(vertexArray::create());
		s_data.batchVertexBuffer.reset(vertexBuffer::create(s_data.maxVertex));
		s_data.batchVertexBuffer->setLayout({
			{ bufferElementType::Float3, "a_Position" },
			{ bufferElementType::Float4, "a_Color"},
			{ bufferElementType::Float2, "a_TextCoord" },
			{ bufferElementType::Float, "a_TextureId" },
			{ bufferElementType::Float, "a_TilingFactor" }
			});
		s_data.batchVertexArray->addVertexBuffer(s_data.batchVertexBuffer);

		s_data.quadVertexBufferBase = new quadVertex[s_data.maxVertex];
		uint32_t* tempIndices = new uint32_t[s_data.maxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_data.maxIndices; i+=6) {
			tempIndices[i + 0] = offset + 0;
			tempIndices[i + 1] = offset + 1;
			tempIndices[i + 2] = offset + 2;

			tempIndices[i + 3] = offset + 2;
			tempIndices[i + 4] = offset + 3;
			tempIndices[i + 5] = offset + 0;

			offset += 4;
		}
		ref<indexBuffer> squareIB;
		squareIB.reset(indexBuffer::create(tempIndices, s_data.maxIndices));
		s_data.batchVertexArray->setIndexBuffer(squareIB);
		delete[] tempIndices;
		s_data.shader = shader::createShader("assets/shaderfiles/texture.glsl");


		//init texture slots in shader
		int32_t sampler[s_data.maxTextureSlot];
		for (int32_t i = 0; i < s_data.maxTextureSlot; i++) 
			sampler[i] = i;
		
		s_data.shader->bind();
		s_data.shader->setIntArray("u_Textures",sampler,s_data.maxTextureSlot);


		//init white texture
		s_data.whiteTexture = texture2D::createTexture(1, 1);
		uint32_t whiteData = 0xffffffff;
		s_data.whiteTexture->setData(&whiteData, sizeof(uint32_t));

		s_data.textureSlots[0] = s_data.whiteTexture;
	}

	void renderer2d::shutdown()
	{

	}

	void renderer2d::beginScene(const orthographicCamera& camera)
	{
		std::dynamic_pointer_cast<openglShader>(s_data.shader)->bind();
		std::dynamic_pointer_cast<openglShader>(s_data.shader)->uploadUniformMat4("m_viewProjection", camera.getViewProjectionMatrix());
		
		s_data.indexCount = 0;
		s_data.textureIndex = 1;
		s_data.quadVertexBufferPtr = s_data.quadVertexBufferBase;
	}

	void renderer2d::endScene()
	{
		uint32_t dataSize = (uint8_t*)s_data.quadVertexBufferPtr - (uint8_t*)s_data.quadVertexBufferBase;
		s_data.batchVertexBuffer->setData(s_data.quadVertexBufferBase, dataSize);

		flush();
	}

	void renderer2d::flush() {
		for (uint32_t i = 0; i < s_data.textureIndex; i++) {
			s_data.textureSlots[i]->bind(i);
		}
		renderCommand::drawIndex(s_data.batchVertexArray, s_data.indexCount);
	}

	void renderer2d::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		drawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void renderer2d::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		//std::dynamic_pointer_cast<openglShader>(s_data.shader)->bind();
		//std::dynamic_pointer_cast<openglShader>(s_data.shader)->uploadUniformFloat4("m_color", color);
		//std::dynamic_pointer_cast<openglShader>(s_data.shader)->uploadUniformInt("hasTexture", false);
		float textureId = 0.0f;
		float tilingFactor = 1.0f;

		s_data.quadVertexBufferPtr->position = position;
		s_data.quadVertexBufferPtr->color = color;
		s_data.quadVertexBufferPtr->texCoord = { 0.0f, 0.0f };
		s_data.quadVertexBufferPtr->textureId = textureId;
		s_data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		s_data.quadVertexBufferPtr++;
		  
		s_data.quadVertexBufferPtr->position = { position.x + size.x, position.y, position.z };
		s_data.quadVertexBufferPtr->color = color;
		s_data.quadVertexBufferPtr->texCoord = { 1.0f, 0.0f };
		s_data.quadVertexBufferPtr->textureId = textureId;
		s_data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		s_data.quadVertexBufferPtr++;

		s_data.quadVertexBufferPtr->position = { position.x + size.x, position.y + size.y, position.z };
		s_data.quadVertexBufferPtr->color = color;
		s_data.quadVertexBufferPtr->texCoord = { 1.0f, 1.0f };
		s_data.quadVertexBufferPtr->textureId = textureId;
		s_data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		s_data.quadVertexBufferPtr++;

		s_data.quadVertexBufferPtr->position = { position.x, position.y + size.y, position.z };
		s_data.quadVertexBufferPtr->color = color;
		s_data.quadVertexBufferPtr->texCoord = { 0.0f, 1.0f };
		s_data.quadVertexBufferPtr->textureId = textureId;
		s_data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		s_data.quadVertexBufferPtr++;

		s_data.indexCount += 6;

		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
		//					  glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		//std::dynamic_pointer_cast<openglShader>(s_data.shader)->uploadUniformMat4("m_transform", transform);

		//s_data.batchVertexArray->bind();
		//renderCommand::drawIndex(s_data.batchVertexArray);
	}

	void renderer2d::drawQuad(const glm::vec2& position, const glm::vec2& size, ref<texture2D> texture, const float tilingFactor)
	{
		drawQuad({ position.x, position.y, 0.0f }, size, texture,tilingFactor);
	}

	void renderer2d::drawQuad(const glm::vec3& position, const glm::vec2& size, ref<texture2D> texture, const float tilingFactor)
	{

		constexpr glm::vec4 color = { 1.0f,1.0f, 1.0f, 1.0f };

		float textureId = 0.0f;
		for (uint32_t i = 1; i < s_data.textureIndex; i++) {
			if (*s_data.textureSlots[i].get() == *texture.get())
			{
				textureId = (float)i;
				break;
			}
		}
		if (textureId == 0.0f) {
			textureId = (float)s_data.textureIndex;
			s_data.textureSlots[s_data.textureIndex] = texture;
			s_data.textureIndex++;
		}

		s_data.quadVertexBufferPtr->position = position;
		s_data.quadVertexBufferPtr->color = color;
		s_data.quadVertexBufferPtr->texCoord = { 0.0f, 0.0f };
		s_data.quadVertexBufferPtr->textureId = textureId;
		s_data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		s_data.quadVertexBufferPtr++;

		s_data.quadVertexBufferPtr->position = { position.x + size.x, position.y, position.z };
		s_data.quadVertexBufferPtr->color = color;
		s_data.quadVertexBufferPtr->texCoord = { 1.0f, 0.0f };
		s_data.quadVertexBufferPtr->textureId = textureId;
		s_data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		s_data.quadVertexBufferPtr++;

		s_data.quadVertexBufferPtr->position = { position.x + size.x, position.y + size.y, position.z };
		s_data.quadVertexBufferPtr->color = color;
		s_data.quadVertexBufferPtr->texCoord = { 1.0f, 1.0f };
		s_data.quadVertexBufferPtr->textureId = textureId;
		s_data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		s_data.quadVertexBufferPtr++;

		s_data.quadVertexBufferPtr->position = { position.x, position.y + size.y, position.z };
		s_data.quadVertexBufferPtr->color = color;
		s_data.quadVertexBufferPtr->texCoord = { 0.0f, 1.0f };
		s_data.quadVertexBufferPtr->textureId = textureId;
		s_data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		s_data.quadVertexBufferPtr++;

		s_data.indexCount += 6;

		/*std::dynamic_pointer_cast<openglShader>(s_data.shader)->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		std::dynamic_pointer_cast<openglShader>(s_data.shader)->uploadUniformMat4("m_transform", transform);
		std::dynamic_pointer_cast<openglShader>(s_data.shader)->uploadUniformInt("hasTexture", true);
		texture->bind();
		s_data.batchVertexArray->bind();
		renderCommand::drawIndex(s_data.batchVertexArray);*/
	}



}