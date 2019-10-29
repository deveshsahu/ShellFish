#pragma once
#include <glm/glm.hpp>
namespace Graphics
{
	enum PROJECTION_TYPE
	{
		PT_ORTHO,
		PT_PERSP,
		PT_SIZE
	};

	class Camera
	{
	public:
		Camera(int projectionType = PT_ORTHO);
		~Camera();

		void updateCamera();
		glm::mat4 getViewProjectionMatrix();
		glm::mat4 getViewMatrix();

	private:

		float mZNear = 0.01f, mZFar = 100.f;

		int mProjectionType;
		bool mMatrixDirty = true;

		glm::vec3 mEyePos, mCenter, mUp;

		glm::mat4 mProjection;
		glm::mat4 mView;

		glm::mat4 mViewProjection;
	};

}