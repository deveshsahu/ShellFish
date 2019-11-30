#include "RenderVisitor.h"
#include "CameraNode.h"
#include "MeshNode.h"
#include "TransformNode.h"

namespace sg
{
	/*void RenderVisitor::visit(std::shared_ptr<Node> node)
	{
	}*/

	RenderVisitor::RenderVisitor():
		BaseVisitor("Render")
	{
	}

	RenderVisitor::~RenderVisitor()
	{
	}

	void RenderVisitor::visit(std::shared_ptr<CameraNode> camnode)
	{
		mTransforms.projectionMatrix = camnode->getProjectionMatrix();
		mTransforms.modelViewMatrix = camnode->getCameraMatrix();

		if (auto child = camnode->getChild())
		{
			child->visit(getSharedFromThis());
		}
	}

	void RenderVisitor::visit(std::shared_ptr<TransformNode> xformnode)
	{
		mTransforms.modelViewMatrix *= xformnode->getTransform();
		for (auto& child : xformnode->getChildren())
			child->visit(getSharedFromThis());
	}

	void RenderVisitor::visit(std::shared_ptr<MeshNode> meshnode)
	{

	}
}