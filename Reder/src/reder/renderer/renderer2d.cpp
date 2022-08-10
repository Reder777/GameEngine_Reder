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
	};

	static Renderer2DStorage* s_Data;

	void renderer2d::init()
	{
		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray.reset(vertexArray::create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		ref<vertexBuffer> squareVB;
		squareVB.reset(vertexBuffer::create(squareVertices, sizeof(squareVertices)));
		squareVB->setLayout({
			{ bufferElementType::Float3, "a_Position" }
			});
		s_Data->QuadVertexArray->addVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		ref<indexBuffer> squareIB;
		squareIB.reset(indexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		s_Data->QuadVertexArray->setIndexBuffer(squareIB);

		s_Data->FlatColorShader = shader::createShader("assets/shaderfiles/fragment.glsl");
	}

	void renderer2d::shutdown()
	{
		delete s_Data;
	}

	void renderer2d::beginScene(const orthographicCamera& camera)
	{
		std::dynamic_pointer_cast<openglShader>(s_Data->FlatColorShader)->bind();
		std::dynamic_pointer_cast<openglShader>(s_Data->FlatColorShader)->uploadUniformMat4("m_viewProjection", camera.getViewProjectionMatrix());
		std::dynamic_pointer_cast<openglShader>(s_Data->FlatColorShader)->uploadUniformMat4("m_transform", glm::mat4(1.0f));
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

		s_Data->QuadVertexArray->bind();
		renderCommand::drawIndex(s_Data->QuadVertexArray);
	}

}