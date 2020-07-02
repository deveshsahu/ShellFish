#include "MeshNode.h"
#include "BaseVisitor.h"
#include "../OpenGLRenderer/TriangleRenderable.h"

namespace sg
{
	MeshNode::MeshNode(const std::string& name):
		Node(name)
	{
	}

	void MeshNode::addVertexData(const std::vector<glm::vec3>& vtxData)
	{
		if (mVertexList.size() > 0)
			mVertexList.clear();
		mVertexList = vtxData;
	}

	void MeshNode::addIndexData(const std::vector<unsigned int>& idxData)
	{
		if (mTriangleIndexList.size() > 0)
			mTriangleIndexList.clear();
		mTriangleIndexList = idxData;
	}

	void MeshNode::visit(std::shared_ptr<BaseVisitor> visitor)
	{
		visitor->visit(getSharedFromThis());
	}

	void MeshNode::finalize()
	{
		auto renderable = std::make_shared<Graphics::TriangleRenderable>(mName, mVertexList, mTriangleIndexList);
		renderable->setColor(mColor);
		mRenderable = renderable;
	}

	std::shared_ptr<MeshNode> MeshNode::getSharedFromThis()
	{
		std::shared_ptr<MeshNode> meshnode;
		try
		{
			meshnode = std::static_pointer_cast<MeshNode>(shared_from_this());
		}
		catch (...)
		{
		}
		return meshnode;
	}
}