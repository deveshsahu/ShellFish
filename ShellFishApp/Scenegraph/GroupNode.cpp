#include "GroupNode.h"
namespace sg
{
	GroupNode::GroupNode(const std::string& name) :
		Node(name)
	{

	}

	void GroupNode::addChild(std::shared_ptr<Node> child)
	{
		if (child)
			return;
		mChildren.push_back(child);
	}
	
}