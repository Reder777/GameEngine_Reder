#include "repch.h"
#include "renderer.h"


namespace reder {
	renderer::sceneData* renderer::m_sceneData = new renderer::sceneData();

	void renderer::beginScene(const std::shared_ptr<orthographicCamera>& oC)
	{
		m_sceneData->viewProjectionMatrix = oC->getViewProjectionMatrix();
	}
	void renderer::endScene()
	{
	}
	void renderer::submit(const std::shared_ptr<shader>& s,const std::shared_ptr<vertexArray>& vA,const glm::mat4& transform)
	{
		s->bind();
		s->uploadUniformMat4("m_viewProjection", m_sceneData->viewProjectionMatrix);
		s->uploadUniformMat4("m_transform", transform);

		vA->bind();
		renderCommand::drawIndex(vA);
	}
}