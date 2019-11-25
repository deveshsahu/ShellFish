#pragma once
#include "GroupNode.h"
#include <glm/glm.hpp>

namespace sg
{
	class TransformNode : public GroupNode
	{
	public:
		TransformNode(const std::string& name);
		void setTransform(const glm::mat4& xform);
		glm::mat4 getTransform() const { return mTransform; }

	private:
		glm::mat4 mTransform;
	};
}