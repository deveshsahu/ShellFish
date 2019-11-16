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
		void addChild(std::shared_ptr<Node> child);

	protected:
		std::vector<std::shared_ptr<Node>> mChildren;
	};
}