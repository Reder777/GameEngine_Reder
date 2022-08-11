#include "repch.h"
#include "sandbox2d.h"
#include "reder.h"

#include <imgui.h>
#include "platform/openGL/openglShader.h"

sandbox2dLayer::sandbox2dLayer(const std::string& name)
	:reder::layer(name),m_cameraController(1280.0f/780.0f,true)
{
}

sandbox2dLayer::~sandbox2dLayer()
{
}

void sandbox2dLayer::onEvent(reder::event& e)
{
	m_cameraController.onEvent(e);
}

void sandbox2dLayer::onUpdate(reder::timeStamp t)
{
	m_cameraController.onUpdate(t);

	reder::renderCommand::clearColor({ 0.1f, 0.1f, 0.1f, 1 });
	reder::renderCommand::clear();
	reder::renderer2d::beginScene(m_cameraController.getCurrentCamera());
	reder::renderer2d::drawQuad({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f }, { 0.8f,0.3f,0.2f,1.0f });
	reder::renderer2d::drawQuad({ 0.5f,0.5f,0.0f }, { 0.5f,0.5f }, { 0.3f,0.3f,0.8f,1.0f });
	reder::renderer2d::drawQuad({ -0.5f,-0.5f,-0.1f }, { 10.5f,10.5f }, texture);
	reder::renderer2d::endScene();
}

void sandbox2dLayer::imguiRender()
{
	ImGui::Begin("color settings");
	ImGui::ColorEdit4("square color", glm::value_ptr(m_squareColor));
	ImGui::End();
}

void sandbox2dLayer::attach()
{
	texture = reder::texture2D::createTexture("assets/Checkerboard.png");
}

void sandbox2dLayer::detach()
{
}
