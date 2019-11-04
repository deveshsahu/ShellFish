#pragma once
#include "Node.h"

#include <memory>
#include <vector>
namespace sg
{
	class GroupNode : public Node
	{
	public:
		GroupNode(const std::string& name);
		void setOrthoParam();
		void setPerspParam();

	protected:
		std::vector<std::shared_ptr<Node>> mChildren;
	};
}