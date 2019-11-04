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
		std::weak_ptr<sg::Node> getRoot() const { return mSceneGraphRoot; }

	private:
		std::shared_ptr<sg::Node> mSceneGraphRoot;
	};
}