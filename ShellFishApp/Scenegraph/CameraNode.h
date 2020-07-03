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
		
		void setCamera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up);
		void setCameraMatrix(const glm::mat4& mat);
		void addChild(std::weak_ptr<Node> child);
		std::shared_ptr<sg::Node> getChild() { return mChildNode; }
		glm::mat4 getCameraMatrix() const { return mCameraMat; }
		glm::mat4 getProjectionMatrix() const { return mProjectionMat; }
		CamType getCameraType() const { return mCamType; }

		virtual void visit(std::shared_ptr<BaseVisitor> visitor) override;

	protected:
		glm::mat4 mCameraMat;
		glm::mat4 mProjectionMat;
		CamType mCamType = CamType::ctInvalid;
		std::shared_ptr<Node> mChildNode;
	
	protected:
		std::shared_ptr<CameraNode> getSharedFromThis();
	};
}