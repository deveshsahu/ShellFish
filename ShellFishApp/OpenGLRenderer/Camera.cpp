#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
namespace Graphics
{

	Camera::Camera(int projectionType):
		mProjectionType(projectionType)
	{
		mEyePos = glm::vec3(0, 0, 5);
		mCenter = glm::vec3(0, 0, 0);
		mUp = glm::vec3(0, 1, 0);
	}


	Camera::~Camera()
	{
	}

	void Camera::updateCamera()
	{
		if (mMatrixDirty)
		{
			if (mProjectionType == PT_ORTHO)
				mProjection = glm::ortho(-1.f, 1.f, -1.f, 1.f, mZNear, mZFar);
			else if (mProjectionType == PT_PERSP)
				mProjection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, mZNear, mZFar);
			mView = glm::lookAt(mEyePos, mCenter, mUp);
			mViewProjection = mProjection * mView;
		}
	}

	glm::mat4 Camera::getViewProjectionMatrix()
	{
		return mViewProjection;
	}

	glm::mat4 Camera::getViewMatrix()
	{
		return mView;
	}
}