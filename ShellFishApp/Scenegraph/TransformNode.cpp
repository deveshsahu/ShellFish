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
}