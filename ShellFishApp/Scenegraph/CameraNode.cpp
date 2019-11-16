#include "CameraNode.h"
#include <glm/gtc/matrix_transform.hpp>

namespace sg
{
	CameraNode::CameraNode():
		Node("Camera")
	{
	}

	void CameraNode::setOrthoParam(double xmag, double ymag, double znear, double zfar)
	{
		mCamType = CamType::ctOrtho;
		mProjectionMat = glm::ortho(-xmag / 2.0, xmag / 2.0, -ymag / 2.0, ymag / 2.0, znear, zfar);
	}

	void CameraNode::setPerspParam(double fovy, double aspectratio, double znear, double zfar)
	{
		mCamType = CamType::ctPersp;
		mProjectionMat = glm::perspective(fovy, aspectratio, znear, zfar);
	}

	void CameraNode::setCameraMatrix(const glm::mat4& mat)
	{
		mCameraMat = mat;
	}

	void CameraNode::addChild(std::weak_ptr<Node> child)
	{
		if (auto node = child.lock())
		{
			mChildNode = child;
		}
	}
}