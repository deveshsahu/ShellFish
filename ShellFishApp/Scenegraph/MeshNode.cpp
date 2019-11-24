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

	void MeshNode::addVertexData(const void* dataStream, unsigned int numVtx)
	{
		if (mVertexList.size() > 0)
			mVertexList.clear();
		mVertexList.reserve(numVtx);
		memcpy(mVertexList.data(), dataStream, numVtx * sizeof(glm::vec3));
	}
}