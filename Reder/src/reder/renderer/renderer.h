#pragma once
#include "reder/core.h"

#include "reder/renderer/renderCommand.h"
#include "reder/renderer/shader.h"
#include "reder/renderer/orthographicCamera.h"

namespace reder {
	class DLL_API renderer {

	public:
		static void init();
		static void beginScene(orthographicCamera& oC);
		static void endScene();
		static void windowResize(uint32_t width, uint32_t height);

		static void submit(const std::shared_ptr<shader>& s, const std::shared_ptr<vertexArray>& vA, const glm::mat4& transform=glm::mat4(1.0f));
		inline static renderGraphicsLibrary getGraphicsLibrary() {
			return rendererAPI::getLibrary();
		}
	private:
		struct sceneData
		{
			glm::mat4 viewProjectionMatrix;
		};

		static sceneData* m_sceneData;
	};
}