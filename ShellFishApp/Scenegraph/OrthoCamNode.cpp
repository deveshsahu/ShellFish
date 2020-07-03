#include "OrthoCamNode.h"
#include "BaseVisitor.h"
#include <glm/gtc/matrix_transform.hpp>

namespace sg
{
	OrthoCamNode::OrthoCamNode():
		CameraNode()
	{
		mCamType = CamType::ctOrtho;
	}

	void OrthoCamNode::updateAspectRatio(double aspect_ratio)
	{
		mMagX = aspect_ratio;
		mMagY = 1.0f;
		mProjectionMat = glm::ortho(-mMagX / 2.0, mMagX / 2.0, -mMagY / 2.0, mMagY / 2.0, mNearz, mFarz);
	}

	void OrthoCamNode::setOrthoParam(double xmag, double ymag, double znear, double zfar)
	{
		mMagX = xmag;
		mMagY = ymag;
		mNearz = znear;
		mFarz = zfar;
		mProjectionMat = glm::ortho(-xmag / 2.0, xmag / 2.0, -ymag / 2.0, ymag / 2.0, znear, zfar);
	}
}