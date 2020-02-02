#include "RenderVisitor.h"
#include "CameraNode.h"
#include "MeshNode.h"
#include "TransformNode.h"


namespace view
{
	RenderVisitor::RenderVisitor(std::vector<std::weak_ptr<Graphics::BaseRenderable>>& inRenderableList) :
		sg::BaseVisitor("Render"),
		mRenderableList(inRenderableList)
	{

	}

	RenderVisitor::~RenderVisitor()
	{
	}

	void RenderVisitor::visit(std::shared_ptr<sg::CameraNode> camnode)
	{
		mTransforms.projectionMatrix = camnode->getProjectionMatrix();
		mTransforms.modelViewMatrix = camnode->getCameraMatrix();

		if (auto child = camnode->getChild())
		{
			child->visit(getSharedFromThis());
		}
	}

	void RenderVisitor::visit(std::shared_ptr<sg::TransformNode> xformnode)
	{
		mTransforms.modelViewMatrix *= xformnode->getTransform();
		for (auto& child : xformnode->getChildren())
			child->visit(getSharedFromThis());
	}

	void RenderVisitor::visit(std::shared_ptr<sg::MeshNode> meshnode)
	{
		mRenderableList.push_back(meshnode->getRenderable());
	}

	void RenderVisitor::visit(std::shared_ptr<sg::Node> node)
	{

	}
}