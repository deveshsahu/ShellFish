#include "Node.h"
#include "BaseVisitor.h"
namespace sg
{
	Node::Node(const std::string& name)
		:mName(name),
		mID(NodeIDGenerator::generate())
	{
	}

	void Node::visit(std::shared_ptr<BaseVisitor> visitor)
	{
		visitor->visit(shared_from_this());
	}
}