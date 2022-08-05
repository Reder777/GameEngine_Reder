#include "reder.h"
#include "imgui.h"

#include "platform/openGL/openglShader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include  <direct.h>  
#include  <stdio.h> 



class exampleLayer :public reder::layer {
public:

	exampleLayer()
		:layer("example")
	{

		//char buffer[MAX_PATH];
		//getcwd(buffer, MAX_PATH);
		//RE_CLIENT_INFO(buffer);


		m_camera.reset(new reder::orthographicCamera(-1.6f, 1.6f, 0.9f, -0.9f));
		{
			m_vertexArray = std::shared_ptr<reder::vertexArray>(reder::vertexArray::create());
			m_vertexArray->bind();
			float vertices[3 * 3] = {
				-0.5f, -0.75f, 0.0f,
				 0.5f, -0.75f, 0.0f,
				 0.0f,  0.75f, 0.0f
			};
			std::shared_ptr<reder::vertexBuffer> vertexBuffer;
			vertexBuffer.reset(reder::vertexBuffer::create(vertices, sizeof(vertices)));

			reder::bufferLayout layout = {
				{reder::bufferElementType::Float3 , "a_Position"}
			};
			vertexBuffer->setLayout(layout);
			m_vertexArray->addVertexBuffer(vertexBuffer);


			unsigned int indices[3] = { 0, 1, 2 };
			std::shared_ptr<reder::indexBuffer> indexBuffer;
			indexBuffer.reset((reder::indexBuffer::create(indices, 3)));
			m_vertexArray->setIndexBuffer(indexBuffer);
			std::string vertexSource = R"(
			#version 330 core
			layout(location=0) in vec3 a_position;
			out vec3 forfun ;
			uniform mat4 m_viewProjection;
			uniform mat4 m_transform;
			void main(){
				forfun = a_position;
				gl_Position = m_viewProjection*m_transform*vec4(a_position,1.0);
			}		
		)";

			std::string fragmentSource = R"(
			#version 330 core
			layout(location=0) out vec4 color;
			in vec3 forfun;
			void main() {
				color = vec4(forfun*0.5+0.5, 1.0);
			}
		)";

			m_Shader = std::shared_ptr<reder::shader>(reder::shader::createShader(vertexSource, fragmentSource));
		}
		{
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
			std::string vertexSource_square = R"(
				#version 330 core
				layout(location=0) in vec3 a_Position;
				uniform mat4 m_viewProjection;
				uniform mat4 m_transform;
				void main(){
					gl_Position = m_viewProjection*m_transform*vec4(a_Position,1.0);
				}		
			)";

			std::string fragmentSource_square = R"(
				#version 330 core
				layout(location=0) out vec4 color;
				uniform vec3 m_color;
				void main() {
					color = vec4( m_color, 1.0);
				}
			)";

			m_Shader_square = std::shared_ptr<reder::shader>(reder::shader::createShader(vertexSource_square, fragmentSource_square));
			m_squareColor = glm::vec3(0.2f, 0.3f, 0.8f);

		}
		{
			std::string vertexSource_texture = R"(
				#version 330 core
				layout(location=0) in vec3 a_Position;
				layout(location=1) in vec2 a_TextCoord;
				out vec2 v_TextCoord;
				uniform mat4 m_viewProjection;
				uniform mat4 m_transform;
				void main(){
					v_TextCoord = a_TextCoord;
					gl_Position = m_viewProjection*m_transform*vec4(a_Position,1.0);
				}
			)";

			std::string fragmentSource_texture = R"(
				#version 330 core
				layout(location=0) out vec4 color;
				in vec2 v_TextCoord;
				uniform sampler2D u_Texture;
				void main() {
					color = texture(u_Texture,v_TextCoord);
				}
			)";

			m_Shader_Texture = std::shared_ptr<reder::shader>(reder::shader::createShader(vertexSource_texture, fragmentSource_texture));
			m_texture = reder::texture2D::createTexture("assets/4.jpg");

			std::dynamic_pointer_cast<reder::openglShader>(m_Shader_Texture)->bind();
			std::dynamic_pointer_cast<reder::openglShader>(m_Shader_Texture)->uploadUniformInt("u_Texture", 0);
		}
	}

	virtual void imguiRender() override {
		ImGui::Begin("color settings");
		ImGui::ColorEdit3("square color", glm::value_ptr(m_squareColor));
		ImGui::End();
	}

	void onUpdate(reder::timeStamp t) override {

		reder::renderCommand::clearColor({ 0.1f, 0.1f, 0.1f, 1 });
		reder::renderCommand::clear();
		m_camera->setPostion(camera_position);
		m_camera->setRotation(rotation);
		//RE_CLIENT_INFO("{0}", t.getMillSeconds());
		//static glm::vec4 blueColor(0.2f, 0.3f, 0.8f,1.0f);
		//static glm::vec4 redColor(0.8f, 0.3f, 0.2f,1.0f);

		std::dynamic_pointer_cast<reder::openglShader>(m_Shader_square)->bind();
		std::dynamic_pointer_cast<reder::openglShader>(m_Shader_square)->uploadUniformFloat3("m_color", m_squareColor);
		reder::renderer::beginScene(m_camera);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				glm::vec3 v = glm::vec3(i * 1.1f, j*1.1f, 0.0f);
				transform = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)), v);
				reder::renderer::submit(m_Shader_square, m_vertexArray_square, transform);
			}
		}
		m_texture->bind();
		reder::renderer::submit(m_Shader_Texture, m_vertexArray_square, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//reder::renderer::submit(m_Shader, m_vertexArray);
		reder::renderer::endScene();

		if (reder::input::isKeyPressed(RE_KEY_LEFT)) {
			camera_position.x += position_speed*t;
		}
		else if (reder::input::isKeyPressed(RE_KEY_RIGHT)) {
			camera_position.x -= position_speed*t;
		}

		if (reder::input::isKeyPressed(RE_KEY_UP)) {
			camera_position.y -= position_speed*t;
		}
		else if (reder::input::isKeyPressed(RE_KEY_DOWN)) {
			camera_position.y += position_speed*t;
		}

		if (reder::input::isKeyPressed(RE_KEY_A)) {
			rotation -= rotation_speed*t;
		}
		else if (reder::input::isKeyPressed(RE_KEY_D)) {
			rotation += rotation_speed*t;
		}
	}	
	void onEvent(reder::event& e) override {

	}

private:
	std::shared_ptr<reder::orthographicCamera> m_camera;


	std::shared_ptr<reder::shader> m_Shader;
	std::shared_ptr<reder::vertexArray> m_vertexArray;


	std::shared_ptr<reder::shader> m_Shader_square;
	std::shared_ptr<reder::vertexArray> m_vertexArray_square;


	std::shared_ptr<reder::shader> m_Shader_Texture;
	reder::ref<reder::texture2D> m_texture;

	float rotation=0.0f;
	glm::vec3 camera_position = { 0.0f,0.0f,0.0f };

	float rotation_speed = 10.0f;
	float position_speed = 1.0f;


	glm::mat4 transform=glm::mat4(1.0f);
	const glm::mat4 identityMatrix = glm::mat4(1.0f);

	glm::vec3 m_squareColor;
};


class Sandbox :public reder::application {

public:

	Sandbox() {
		pushLayer(new exampleLayer());

	}

	~Sandbox() {

	}
};


reder::application* reder::createSandbox() {
	printf("this is the first sandbox!");
	return new Sandbox();
}