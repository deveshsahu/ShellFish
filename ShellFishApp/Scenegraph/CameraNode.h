#pragma once
#include "Node.h"
#include <glm/glm.hpp>
namespace sg
{
	enum class CamType
	{
		ctOrtho,
		ctPersp,
		ctInvalid
	};

	class CameraNode : public Node
	{
	public:
		CameraNode();
		void setOrthoParam(double xmag, double ymag, double znear, double zfar);
		void setPerspParam(double fovy, double aspectratio, double znear, double zfar);

	protected:
		glm::mat4 mCameraMat;
		glm::mat4 mProjectionMat;

		CamType mCamType = CamType::ctInvalid;

		std::shared_ptr<Node> mChildNode;
	};
}