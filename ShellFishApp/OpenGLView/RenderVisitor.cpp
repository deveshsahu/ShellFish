#include "RenderVisitor.h"
#include "CameraNode.h"
#include "MeshNode.h"
#include "TransformNode.h"

#include <stdexcept>
#include <iostream>

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

	void RenderVisitor::visit(std::shared_ptr<sg::GroupNode> node)
	{
		for (auto& child : node->getChildren())
			child->visit(getSharedFromThis());
	}

	std::shared_ptr<RenderVisitor> RenderVisitor::getSharedFromThis()
	{
		std::shared_ptr<RenderVisitor> rendervisitor;
		try
		{
			rendervisitor = std::static_pointer_cast<RenderVisitor>(shared_from_this());
		}
		catch(const std::runtime_error& err)
		{
			std::cerr << "Render visitor cast failure" << std::endl;
		}

		return rendervisitor;
	}
}