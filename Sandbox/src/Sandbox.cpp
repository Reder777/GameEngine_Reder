#include "reder.h"
#include "imgui.h"

class exampleLayer :public reder::layer {
public:

	exampleLayer()
		:layer("example")
	{
		m_camera.reset(new reder::orthographicCamera(-1.6f, 1.6f, 0.9f, -0.9f));
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
			void main(){
				forfun = a_position;
				gl_Position = m_viewProjection*vec4(a_position,1.0);
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


		m_vertexArray_square = std::shared_ptr<reder::vertexArray>(reder::vertexArray::create());
		m_vertexArray_square->bind();


		float vertices_square[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};
		std::shared_ptr<reder::vertexBuffer> vertexBufferSquare;
		vertexBufferSquare.reset(reder::vertexBuffer::create(vertices_square, sizeof(vertices_square)));

		reder::bufferLayout layout_square = {
			{reder::bufferElementType::Float3 , "a_Position"}
		};
		vertexBufferSquare->setLayout(layout_square);
		m_vertexArray_square->addVertexBuffer(vertexBufferSquare);


		unsigned int indices_square[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<reder::indexBuffer> indexBufferSquare;
		indexBufferSquare.reset((reder::indexBuffer::create(indices_square, 6)));
		m_vertexArray_square->setIndexBuffer(indexBufferSquare);
		std::string vertexSource_square = R"(
			#version 330 core
			layout(location=0) in vec3 a_position;
			out vec3 forfun ;
			uniform mat4 m_viewProjection;
			void main(){
				forfun = a_position;
				gl_Position = m_viewProjection*vec4(a_position,1.0);
			}		
		)";

		std::string fragmentSource_square = R"(
			#version 330 core
			layout(location=0) out vec4 color;
			in vec3 forfun;
			void main() {
				color = vec4( 0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_Shader_square = std::shared_ptr<reder::shader>(reder::shader::createShader(vertexSource_square, fragmentSource_square));
	}

	virtual void imguiRender() override {
		
	}

	void onUpdate() override {

		m_camera->setPostion(camera_position);
		m_camera->setRotation(rotation);


		reder::renderer::beginScene(m_camera);
		reder::renderer::submit(m_Shader_square, m_vertexArray_square);
		reder::renderer::submit(m_Shader, m_vertexArray);
		reder::renderer::endScene();

		if (reder::input::isKeyPressed(RE_KEY_LEFT)) {
			camera_position.x += position_speed;
		}
		else if (reder::input::isKeyPressed(RE_KEY_RIGHT)) {
			camera_position.x -= position_speed;
		}

		if (reder::input::isKeyPressed(RE_KEY_UP)) {
			camera_position.y -= position_speed;
		}
		else if (reder::input::isKeyPressed(RE_KEY_DOWN)) {
			camera_position.y += position_speed;
		}

		if (reder::input::isKeyPressed(RE_KEY_A)) {
			rotation -= rotation_speed;
		}
		else if (reder::input::isKeyPressed(RE_KEY_D)) {
			rotation += rotation_speed;
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

	float rotation=0.0f;
	glm::vec3 camera_position = { 0.0f,0.0f,0.0f };

	float rotation_speed = 0.05f;
	float position_speed = 0.1f;
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