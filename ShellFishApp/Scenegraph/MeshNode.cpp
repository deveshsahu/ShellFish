#include "MeshNode.h"

namespace sg
{
	MeshNode::MeshNode(const std::string& name):
		Node(name)
	{

	}

	void MeshNode::setVisibility(bool visible)
	{
		mVisibility = visible;
	}

	bool MeshNode::getVisibility() const
	{
		return mVisibility;
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
}