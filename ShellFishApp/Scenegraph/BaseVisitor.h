#pragma once
#include <memory>
#include <string>
namespace sg
{
	class Node;
	class MeshNode;
	class CameraNode;
	class TransformNode;
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

	protected:

		std::shared_ptr<BaseVisitor> getSharedFromThis() { return shared_from_this(); }

		std::string mName;
	};
}