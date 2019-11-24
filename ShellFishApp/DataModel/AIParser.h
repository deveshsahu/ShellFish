#pragma once
#include <string>
#include <memory>
namespace sg
{
	class Node;
}
namespace loader
{
	class AIParser
	{
	public:
		static std::shared_ptr<sg::Node> loadFromFile(const std::string& filepath);
	};
}