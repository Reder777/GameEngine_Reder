#pragma once
#include "reder/renderer/orthographicCamera.h"
#include "texture.h"
namespace reder {

	class renderer2d
	{
	public:
		static void init();
		static void shutdown();

		static void beginScene(const orthographicCamera& camera);
		static void endScene();
		static void flush();

		// Primitives
		static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void drawQuad(const glm::vec2& position, const glm::vec2& size, ref<texture2D> texture, const float tilingFactor = 1.0f);
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, ref<texture2D> texture, const float tilingFactor = 1.0f);


	};

}