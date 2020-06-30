#pragma once
#include "../OpenGLRenderer/UniqueIDGenerator.h"
#include <string>
#include <memory>
namespace sg
{
	/**
	 * @brief Singleton class that generates IDs for each node.
	 * Every scenegraph node is desiged to hold a unique ID generated
	 * by this class
	 */
	class NodeIDGenerator
	{
	public:
		static ID generate()
		{
			static UniqueIDGenerator instance;
			return instance.generate();
		}
	};

	class BaseVisitor;
	class Node : public std::enable_shared_from_this<Node>
	{
	public:
		Node(const std::string& name);
		virtual ~Node() {}

		inline void setName(const std::string& name) { mName = name; }
		inline std::string getName() const { return mName; }

		virtual void visit(std::shared_ptr<BaseVisitor> visitor);

	protected:
		std::string mName;
		const ID mID;
	};
}