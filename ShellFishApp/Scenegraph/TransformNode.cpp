#include "TransformNode.h"

namespace sg
{
	TransformNode::TransformNode(const std::string& name):
		GroupNode(name)
	{
	}

	void TransformNode::setTransform(const glm::mat4& xform)
	{
		mTransform = xform;
	}

	std::shared_ptr<TransformNode> TransformNode::getSharedFromThis()
	{
		std::shared_ptr<TransformNode> xformnode;
		try
		{
			xformnode = std::static_pointer_cast<TransformNode>(shared_from_this());
		}
		catch (...)
		{

		}
		return xformnode;
	}
}