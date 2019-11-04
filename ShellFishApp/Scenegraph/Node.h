#pragma once
#include <string>
#include <memory>
namespace sg
{
	class Node
	{
	public:
		Node(const std::string& name);
		virtual ~Node() {}

		void setName(const std::string& name);

	protected:
		std::string mName;
	};
}