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
		mTransforms.projection = camnode->getProjectionMatrix();
		mTransforms.view = camnode->getCameraMatrix();

		if (auto child = camnode->getChild())
		{
			child->visit(getSharedFromThis());
		}
	}

	void RenderVisitor::visit(std::shared_ptr<sg::TransformNode> xformnode)
	{
		auto xform = xformnode->getTransform();
		mTransforms.model *= xform;
		for (auto& child : xformnode->getChildren())
			child->visit(getSharedFromThis());
		mTransforms.model *= glm::inverse(xform);
	}

	void RenderVisitor::visit(std::shared_ptr<sg::MeshNode> meshnode)
	{
		auto renderable = meshnode->getRenderable();
		if (!renderable.expired())
			renderable.lock()->setModelMatrix(mTransforms.model);
		mRenderableList.push_back(renderable);
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