#include "repch.h"
#include "orthographicCameraController.h"
#include "reder/core/input.h"
#include "reder/core/log.h"
#include "reder/codesDef/keyCodes.h"
#include "reder/event/event.h"

namespace reder {

	/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	question is why current_camera init doesnt work!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	orthographicCameraController::orthographicCameraController(float aspectRatio, bool enableRotation)
		:m_aspectRatio(aspectRatio),
		 current_Camera(aspectRatio*zoomLevel, aspectRatio* zoomLevel,zoomLevel,-zoomLevel),
		 m_enableRotation(enableRotation)
	{
		current_Camera.setProjection(-m_aspectRatio * zoomLevel, m_aspectRatio * zoomLevel, zoomLevel, -zoomLevel);
	}
	void orthographicCameraController::onUpdate(timeStamp ts)
	{
		if (input::isKeyPressed(RE_KEY_A)) {
			cameraPos.x -= transSpeed * ts;
		}
		else if (input::isKeyPressed(RE_KEY_D)) {
			cameraPos.x += transSpeed * ts;
		}

		if (input::isKeyPressed(RE_KEY_W)) {
			cameraPos.y += transSpeed * ts;
		}
		else if (input::isKeyPressed(RE_KEY_S)) {
			cameraPos.y -= transSpeed * ts;
		}
		if (m_enableRotation) {
			if (input::isKeyPressed(RE_KEY_Q)) {
				rotation -= rotationSpeed * ts;
			}
			else if (input::isKeyPressed(RE_KEY_E)) {
				rotation += rotationSpeed * ts;
			}
			current_Camera.setRotation(rotation);
		}
		current_Camera.setPostion(cameraPos);

	}
	void orthographicCameraController::onEvent(event& e)
	{
		eventDispatcher dispatcher(e);
		dispatcher.Dispatch<mouseScrolledEvent>(RE_BIND_EVENT(orthographicCameraController::mouseScrollEvent));
		dispatcher.Dispatch<windowResizeEvent>(RE_BIND_EVENT(orthographicCameraController::resizeEvent));
	}
	bool orthographicCameraController::mouseScrollEvent(mouseScrolledEvent& e)
	{
		zoomLevel -= e.getYOffset() * 0.5f;
		zoomLevel = std::max(zoomLevel, 0.25f);
		transSpeed = zoomLevel;
		current_Camera.setProjection(-m_aspectRatio * zoomLevel, m_aspectRatio * zoomLevel, zoomLevel, -zoomLevel);
		return false;
	}
	bool orthographicCameraController::resizeEvent(windowResizeEvent& e)
	{
		if (!current_Camera.getSolidView()) {
			m_aspectRatio = (float)e.getWidth() / (float)e.getHeight();
			current_Camera.setProjection(-m_aspectRatio * zoomLevel, m_aspectRatio * zoomLevel, zoomLevel, -zoomLevel);
		}
		return false;
	}
}