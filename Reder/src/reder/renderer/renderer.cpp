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
	void renderer::submit(const std::shared_ptr<shader>& s,const std::shared_ptr<vertexArray>& vA)
	{
		s->bind();
		s->uploadUniformMat4("m_viewProjection", m_sceneData->viewProjectionMatrix);


		vA->bind();
		renderCommand::drawIndex(vA);
	}
}