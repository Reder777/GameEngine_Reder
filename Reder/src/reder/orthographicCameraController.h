#pragma once
#include "reder/core/timeStamp.h"
#include "reder/renderer/orthographicCamera.h"
#include "reder/event/windowEvent.h"
#include "reder/event/mouseEvent.h"
#include "reder/core/core.h"

#include <glm/glm.hpp>

namespace reder {
	class DLL_API orthographicCameraController {
	public:
		orthographicCameraController(float aspectRatio, bool enableRotation = false);

		void onUpdate(timeStamp ts);
		void onEvent(event& e);
		orthographicCamera& getCurrentCamera(){ return current_Camera; }
		const orthographicCamera& getCurrentCamera() const { return current_Camera; }
	private:
		bool mouseScrollEvent(mouseScrolledEvent& e);
		bool resizeEvent(windowResizeEvent& e);
	private:
		float zoomLevel = 1.0f;
		float m_aspectRatio;
		orthographicCamera current_Camera;

		bool m_enableRotation ;

		glm::vec3 cameraPos = { 0.0f,0.0f,0.0f };
		float rotation = 0.0f;
		float transSpeed = 1.0f;
		float rotationSpeed = 45.0f;
	};
}