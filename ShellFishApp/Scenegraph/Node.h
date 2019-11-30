#pragma once
#include <string>
#include <memory>
namespace sg
{
	class BaseVisitor;
	class Node : public std::enable_shared_from_this<Node>
	{
	public:
		Node(const std::string& name);
		virtual ~Node() {}

		void setName(const std::string& name);

		virtual void visit(std::shared_ptr<BaseVisitor> visitor);

	protected:
		std::shared_ptr<Node> getSharedFromThis();

	protected:
		std::string mName;
	};
}