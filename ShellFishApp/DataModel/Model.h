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

		bool load(const std::string& filePath);

	private:
		std::shared_ptr<sg::Node> mSceneGraphRoot;
	};
}