#pragma once
#include "reder/core/core.h"
#include <glm/glm.hpp>



namespace reder {
	class DLL_API orthographicCamera {
	public:
		orthographicCamera(float left, float right, float top, float bottom);
		void setProjection(float left, float right, float top, float bottom);
		void setPostion(const glm::vec3& position) { m_position = position; calculateViewMatrix(); }
		void setRotation(const float rotation) { m_rotation = rotation; calculateViewMatrix(); }
		void setSolidView(bool solidView) { m_solidView = solidView; }

		inline const glm::vec3& getPosition() const { return m_position; }
		inline float getRotation() const { return m_rotation; }

		inline const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; }
		inline const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
		inline const glm::mat4& getViewProjectionMatrix() const { return m_viewProjectionMatrix; }
		inline bool getSolidView() const { return m_solidView; }
	private:
		void calculateViewMatrix();
	private:
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_viewProjectionMatrix;

		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
		float m_rotation = 0.0f ;

		bool m_solidView = false;
	};
}