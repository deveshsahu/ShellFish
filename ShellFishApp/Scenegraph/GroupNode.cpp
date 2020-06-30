#include "GroupNode.h"
#include "BaseVisitor.h"
namespace sg
{
	GroupNode::GroupNode(const std::string& name) :
		Node(name)
	{

	}

	void GroupNode::addChild(std::shared_ptr<Node> child)
	{
		if (!child)
			return;
		mChildren.push_back(child);
	}

	void GroupNode::visit(std::shared_ptr<BaseVisitor> visitor)
	{
		visitor->visit(getSharedFromThis());
	}

	std::shared_ptr<GroupNode> GroupNode::getSharedFromThis()
	{
		std::shared_ptr<GroupNode> grpnode;
		try
		{
			grpnode = std::static_pointer_cast<GroupNode>(shared_from_this());
		}
		catch (...)
		{

		}
		return grpnode;
	}
	
}