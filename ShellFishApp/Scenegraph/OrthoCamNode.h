#pragma once
#include "CameraNode.h"

namespace sg
{
	class OrthoCamNode : public CameraNode
	{
	public:
		OrthoCamNode();

		void setOrthoParam(double xmag, double ymag, double znear, double zfar);
		void updateAspectRatio(double aspect_ratio);

	private:
		double mMagX, mMagY; // X-Y magnitudes
		double mNearz = 0.01f, mFarz = 1000.f; // Near and Far planes
	};
}