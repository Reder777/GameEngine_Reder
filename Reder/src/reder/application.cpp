#include "repch.h"
#include "application.h"
#include "log.h"

#include <glad/glad.h>
#include "platform/windows/windowsInput.h"
#include "platform/openGL/openglShader.h"



namespace reder {
	application* application::app_Instance = nullptr;
	input* input::input_instance = new windowsInput();;
	application::application() {

		RE_CORE_ASSERT(!app_Instance, "app already exists!");
		app_Instance = this;
		

		m_Window = std::unique_ptr<window>(window::createWindows());
		m_Window->setEventCallback(RE_BIND_EVENT(application::OnEvent));

		m_imguiLayer = new imguiLayer();
		pushOverLayer(m_imguiLayer);

		

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		std::string vertexSource=R"(
			#version 330 core
			layout(location=0) in vec3 a_position;
			out vec3 forfun ;
			void main(){
				forfun = a_position;
				gl_Position = vec4(a_position,1.0);
			}		
		)";

		std::string fragmentSource=R"(
			#version 330 core
			layout(location=0) out vec4 color;
			in vec3 forfun;
			void main() {
				color = vec4(forfun*0.5+0.4, 1.0);
			}
		)";

		m_Shader = std::unique_ptr<shader>(new openglShader(vertexSource,fragmentSource));
		/*
		m_Shader.reset(new openglShader());
		*/
	}

	application::~application() {

	}

	void application::run() {
	


		while (m_Running) {

			glClearColor(0, 0.5f, 0.5f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (layer* layer : m_layStack) {
				layer->onUpdate();
			}
			m_imguiLayer->begin();
			for (layer* layer : m_layStack) {
				layer->imguiRender();
			}
			m_imguiLayer->end();
			m_Window->onUpdate();

		}
		
	}

	bool application::windowClose(windowCloseEvent& e) {
		m_Running = false;
		return true;
	}
	/*
		from the end of the layer stack ,send the events to it and check if handled
		question is i dont know why from the bottom
	
	*/
	void application::OnEvent(event& e) {
		eventDispatcher m_eventDispatcher(e);
		m_eventDispatcher.Dispatch<windowCloseEvent>(RE_BIND_EVENT(application::windowClose));
#if SHOW_ALL_DEBUG_INFO
		RE_CORE_INFO("{0}", e);
#endif // SHOW_ALL_DEBUG_INFO

		
		for (auto it = m_layStack.end(); it != m_layStack.begin();) {
			(*--it)->onEvent(e);
			if (e.getHandled() == true) {
				break;
			}
		}

	}

	void application::popLayer(layer* layer) {
		m_layStack.popLayer(layer);
	}

	void application::pushLayer(layer* layer) {
		m_layStack.pushLayer(layer);
		layer->attach();
	}

	void application::pushOverLayer(layer* overlayer) {
		m_layStack.pushOverLayer(overlayer);
		overlayer->attach();
	}
}