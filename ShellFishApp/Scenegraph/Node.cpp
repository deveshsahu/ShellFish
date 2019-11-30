#include "Node.h"
#include "BaseVisitor.h"
namespace sg
{
	Node::Node(const std::string& name)
		:mName(name)
	{
	}

	void Node::setName(const std::string& name)
	{
		mName = name;
	}

	void Node::visit(std::shared_ptr<BaseVisitor> visitor)
	{
		visitor->visit(getSharedFromThis());
	}

	std::shared_ptr<Node> Node::getSharedFromThis()
	{
		return shared_from_this();
	}
}