#include "reder.h"
#include "imgui.h"

#include "platform/openGL/openglShader.h"
#include "reder/core/entryPoint.h"
#include "sandbox2d.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <direct.h>  
#include <stdio.h> 



class exampleLayer :public reder::layer {
public:

	exampleLayer()
		:layer("example"),m_cameraController(1280.0f/780.0f,true)
	{
		
	}
	virtual void attach() override{
		m_shaderLibrary.reset(new reder::shaderLibrary());

		m_vertexArray_square = std::shared_ptr<reder::vertexArray>(reder::vertexArray::create());
		m_vertexArray_square->bind();


		float vertices_square[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		std::shared_ptr<reder::vertexBuffer> vertexBufferSquare;
		vertexBufferSquare.reset(reder::vertexBuffer::create(vertices_square, sizeof(vertices_square)));

		reder::bufferLayout layout_square = {
			{reder::bufferElementType::Float3 , "a_Position"},
			{reder::bufferElementType::Float2 , "a_TextCoord"}
		};
		vertexBufferSquare->setLayout(layout_square);
		m_vertexArray_square->addVertexBuffer(vertexBufferSquare);


		unsigned int indices_square[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<reder::indexBuffer> indexBufferSquare;
		indexBufferSquare.reset((reder::indexBuffer::create(indices_square, 6)));
		m_vertexArray_square->setIndexBuffer(indexBufferSquare);


		m_Shader_square = m_shaderLibrary->loadShader("fragment", "assets/shaderfiles/fragment.glsl");
		m_Shader_Texture = m_shaderLibrary->loadShader("assets/shaderfiles/texture.glsl");
		m_texture = reder::texture2D::createTexture("assets/4.jpg");

		auto m_Shader_Texture = m_shaderLibrary->getByName("texture");
		std::dynamic_pointer_cast<reder::openglShader>(m_Shader_Texture)->bind();
		std::dynamic_pointer_cast<reder::openglShader>(m_Shader_Texture)->uploadUniformInt("u_Texture", 0);
	}

	virtual void imguiRender() override {
		ImGui::Begin("color settings");
		ImGui::ColorEdit3("square color", glm::value_ptr(m_squareColor));
		ImGui::End();
	}

	void onUpdate(reder::timeStamp t) override {
		m_cameraController.onUpdate(t);

		reder::renderCommand::clearColor({ 0.1f, 0.1f, 0.1f, 1 });
		reder::renderCommand::clear();
		reder::renderer::beginScene(m_cameraController.getCurrentCamera());
		
		std::dynamic_pointer_cast<reder::openglShader>(m_Shader_square)->bind();
		std::dynamic_pointer_cast<reder::openglShader>(m_Shader_square)->uploadUniformFloat3("m_color", m_squareColor);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				glm::vec3 v = glm::vec3(i * 1.1f, j*1.1f, 0.0f);
				transform = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)), v);
				reder::renderer::submit(m_Shader_square, m_vertexArray_square, transform);
			}
		}
		m_texture->bind();
		reder::renderer::submit(m_Shader_Texture, m_vertexArray_square, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		reder::renderer::endScene();

	}	
	void onEvent(reder::event& e) override {
		m_cameraController.onEvent(e);
	}

private:
	reder::orthographicCameraController m_cameraController;
	std::shared_ptr<reder::vertexArray> m_vertexArray;
	std::shared_ptr<reder::vertexArray> m_vertexArray_square;
	std::shared_ptr<reder::shader> m_Shader_square, m_Shader_Texture;
	reder::ref<reder::texture2D> m_texture;
	glm::mat4 transform=glm::mat4(1.0f);
	const glm::mat4 identityMatrix = glm::mat4(1.0f);
	glm::vec3 m_squareColor = {0.2f,0.8,0.3f};

	reder::ref<reder::shaderLibrary> m_shaderLibrary;
};


class Sandbox :public reder::application {

public:

	Sandbox() {
		pushLayer(new sandbox2dLayer());
	}

	~Sandbox() {

	}

};


reder::application* reder::createSandbox() {
	printf("this is the first sandbox!");
	return new Sandbox();
}