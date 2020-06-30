#include "MeshNode.h"
#include "BaseVisitor.h"
#include "../OpenGLRenderer/TriangleRenderable.h"

namespace sg
{
	MeshNode::MeshNode(const std::string& name):
		Node(name)
	{
	}

	void MeshNode::addVertexData(const void* dataStream, size_t numVtx)
	{
		if (mVertexList.size() > 0)
			mVertexList.clear();
		mVertexList.reserve(numVtx);
		memcpy(mVertexList.data(), dataStream, numVtx * sizeof(glm::vec3));
	}

	void MeshNode::addIndexData(const void* dataStream, size_t numIdx)
	{
		if (mTriangleIndexList.size() > 0)
			mTriangleIndexList.clear();
		mTriangleIndexList.reserve(numIdx);
		memcpy(mTriangleIndexList.data(), dataStream, numIdx * sizeof(unsigned int));
	}

	void MeshNode::visit(std::shared_ptr<BaseVisitor> visitor)
	{
		visitor->visit(shared_from_this());
	}

	void MeshNode::finalize()
	{
		mRenderable = std::make_shared<Graphics::TriangleRenderable>("temp", mVertexList, mTriangleIndexList);
	}
}