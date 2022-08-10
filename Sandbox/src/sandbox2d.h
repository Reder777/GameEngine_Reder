#pragma once
#include "reder.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


class sandbox2dLayer :public reder::layer {

public:
	sandbox2dLayer(const std::string& name = "sandbox2d");
	~sandbox2dLayer();
	virtual void onEvent(reder::event& e) override;
	virtual void onUpdate(reder::timeStamp t) override;
	virtual void imguiRender() override;
	virtual void attach() override;
	virtual void detach() override;

private:
	reder::orthographicCameraController m_cameraController;
	reder::ref<reder::vertexArray> m_vertexArray;
	reder::ref<reder::shader> m_Shader;
	glm::vec4 m_squareColor = { 0.2f,0.8,0.3f,1.0f };
	reder::ref<reder::shaderLibrary> m_shaderLibrary;

};