#pragma once
#include "CameraNode.h"

namespace sg
{
	class PerspectiveCamNode : public CameraNode
	{
	public:
		PerspectiveCamNode();
		void setPerspParam(double fovy, double aspectratio, double znear, double zfar);
		void updateAspectRatio(double aspect_ratio);

	protected:
		double mFOV; // In degrees
		double mAspectRatio = 1.f; // viewport width / height
		double mNearplane = 0.01f, mFarplane = 1000.f; // near and far planes
	};
}