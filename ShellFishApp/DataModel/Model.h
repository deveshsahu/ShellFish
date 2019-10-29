#pragma once

#include <string>
#include <vector>
#include <memory>
namespace sg
{
	class Node;
}
namespace model
{
	class Model
	{

	public:
		Model();
		virtual ~Model();

		virtual bool load(const std::string& filePath) = 0;

	private:
		std::shared_ptr<sg::Node> iSceneGraphRoot;
	};
}