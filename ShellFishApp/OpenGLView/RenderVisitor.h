#pragma once

#include "BaseVisitor.h"

#include <memory>
#include <glm/glm.hpp>

namespace sg
{
	struct Transforms
	{
		glm::mat4 projectionMatrix;
		glm::mat4 modelViewMatrix;
		glm::mat4 mvpMatrix;
	};

	class RenderVisitor : public BaseVisitor
	{
	public:
		RenderVisitor();
		~RenderVisitor();
		//void visit(std::shared_ptr<Node> node);
		void visit(std::shared_ptr<CameraNode> camnode) override;
		void visit(std::shared_ptr<TransformNode> xformnode) override;
		void visit(std::shared_ptr<MeshNode> meshnode) override;
	private:
		Transforms mTransforms;
	};
}