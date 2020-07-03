#include "CameraNode.h"
#include "BaseVisitor.h"
#include <glm/gtc/matrix_transform.hpp>

namespace sg
{
	CameraNode::CameraNode():
		Node("Camera")
	{
	}

	void CameraNode::setCamera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up)
	{
		mCameraMat = glm::lookAt(eye, center, up);
	}

	void CameraNode::setCameraMatrix(const glm::mat4& mat)
	{
		mCameraMat = mat;
	}

	void CameraNode::addChild(std::weak_ptr<Node> child)
	{
		if (auto node = child.lock())
		{
			mChildNode = node;
		}
	}

	void CameraNode::visit(std::shared_ptr<BaseVisitor> visitor)
	{
		visitor->visit(getSharedFromThis());
	}

	std::shared_ptr<CameraNode> CameraNode::getSharedFromThis()
	{
		std::shared_ptr<CameraNode> ptr;
		try
		{
			ptr = std::static_pointer_cast<CameraNode>(shared_from_this());
		}
		catch(void*)
		{
			
		}
		return ptr;
	}
}