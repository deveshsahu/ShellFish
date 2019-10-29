#include "Node.h"

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
}