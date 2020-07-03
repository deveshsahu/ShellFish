#include "PerspectiveCamNode.h"
#include "BaseVisitor.h"
#include <glm/gtc/matrix_transform.hpp>

namespace sg
{
	PerspectiveCamNode::PerspectiveCamNode():
		CameraNode()
	{
		mCamType = CamType::ctPersp;
	}

	void PerspectiveCamNode::setPerspParam(double fovy, double aspectratio, double znear, double zfar)
	{
		mFOV = fovy;
		mAspectRatio = aspectratio;
		mNearplane = znear;
		mFarplane = zfar;
		mProjectionMat = glm::perspective(fovy, aspectratio, znear, zfar);
	}

	void PerspectiveCamNode::updateAspectRatio(double aspect_ratio)
	{
		mAspectRatio = aspect_ratio;
		mProjectionMat = glm::perspective(mFOV, mAspectRatio, mNearplane, mFarplane);
	}
}