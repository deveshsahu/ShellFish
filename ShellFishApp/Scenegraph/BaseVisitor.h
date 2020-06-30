#pragma once
#include <memory>
#include <string>
namespace sg
{
	class Node;
	class MeshNode;
	class CameraNode;
	class TransformNode;
	class GroupNode;
	class BaseVisitor : public std::enable_shared_from_this<BaseVisitor>
	{
	public:
		BaseVisitor(const std::string& name = "Base") :
			mName(name)
		{
		}

		virtual ~BaseVisitor() {}

		virtual void visit(std::shared_ptr<Node> node) {}
		virtual void visit(std::shared_ptr<CameraNode> camnode) {}
		virtual void visit(std::shared_ptr<TransformNode> xformnode) {}
		virtual void visit(std::shared_ptr<MeshNode> meshnode) {}
		virtual void visit(std::shared_ptr<GroupNode> grpnode) {}

	protected:
		std::string mName;

	private:
		std::shared_ptr<BaseVisitor> getSharedFromThis() { return shared_from_this(); }
	};
}