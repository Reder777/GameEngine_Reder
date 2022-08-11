#include "repch.h"
#include "renderer2d.h"

#include "reder/core/core.h"
#include "vertexArray.h"
#include "shader.h"
#include "renderCommand.h"

#include "platform/opengl/openglShader.h"

namespace reder {

	struct Renderer2DStorage
	{
		ref<vertexArray> QuadVertexArray;
		ref<shader> FlatColorShader;
		ref<shader> textureShader;
	};

	static Renderer2DStorage* s_Data;

	void renderer2d::init()
	{
		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray.reset(vertexArray::create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,0.0f,0.0f,
			 0.5f, -0.5f, 0.0f,1.0f,0.0f,
			 0.5f,  0.5f, 0.0f,1.0f,1.0f,
			-0.5f,  0.5f, 0.0f,0.0f,1.0f
		};

		ref<vertexBuffer> squareVB;
		squareVB.reset(vertexBuffer::create(squareVertices, sizeof(squareVertices)));
		squareVB->setLayout({
			{ bufferElementType::Float3, "a_Position" },
			{ bufferElementType::Float2, "a_TextCoord" }
			});
		s_Data->QuadVertexArray->addVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		ref<indexBuffer> squareIB;
		squareIB.reset(indexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		s_Data->QuadVertexArray->setIndexBuffer(squareIB);

		s_Data->FlatColorShader = shader::createShader("assets/shaderfiles/fragment.glsl");
		s_Data->textureShader = shader::createShader("assets/shaderfiles/texture.glsl");
	}

	void renderer2d::shutdown()
	{
		delete s_Data;
	}

	void renderer2d::beginScene(const orthographicCamera& camera)
	{
		std::dynamic_pointer_cast<openglShader>(s_Data->FlatColorShader)->bind();
		std::dynamic_pointer_cast<openglShader>(s_Data->FlatColorShader)->uploadUniformMat4("m_viewProjection", camera.getViewProjectionMatrix());
		std::dynamic_pointer_cast<openglShader>(s_Data->textureShader)->bind();
		std::dynamic_pointer_cast<openglShader>(s_Data->textureShader)->uploadUniformMat4("m_viewProjection", camera.getViewProjectionMatrix());
	}

	void renderer2d::endScene()
	{

	}

	void renderer2d::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		drawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void renderer2d::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		std::dynamic_pointer_cast<openglShader>(s_Data->FlatColorShader)->bind();
		std::dynamic_pointer_cast<openglShader>(s_Data->FlatColorShader)->uploadUniformFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
							  glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		std::dynamic_pointer_cast<openglShader>(s_Data->FlatColorShader)->uploadUniformMat4("m_transform", transform);

		s_Data->QuadVertexArray->bind();
		renderCommand::drawIndex(s_Data->QuadVertexArray);
	}

	void renderer2d::drawQuad(const glm::vec2& position, const glm::vec2& size, ref<texture2D> texture)
	{
		drawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void renderer2d::drawQuad(const glm::vec3& position, const glm::vec2& size, ref<texture2D> texture)
	{
		std::dynamic_pointer_cast<openglShader>(s_Data->textureShader)->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		std::dynamic_pointer_cast<openglShader>(s_Data->textureShader)->uploadUniformMat4("m_transform", transform);

		texture->bind();
		s_Data->QuadVertexArray->bind();
		renderCommand::drawIndex(s_Data->QuadVertexArray);
	}

}