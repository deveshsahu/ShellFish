#pragma once
#include "Node.h"

#include <vector>
#include <glm/glm.hpp>

namespace sg
{
	class MeshNode : public Node
	{
	public:
		MeshNode(const std::string& name);
		void setVisibility(bool visible);
		bool getVisibility() const;

		/**
		 * @brief Copy vertex data to the mesh
		 * Accepts only float with 3 vectors
		 */
		void addVertexData(const void* dataStream, unsigned int numVtx);
		//void addIndexData(const void)

	private:
		bool mVisibility;

		std::vector<glm::vec3> mVertexList;
		std::vector<glm::uvec3> mTriangleIndexList;
		std::vector<glm::vec4> mColorList;
	};
}