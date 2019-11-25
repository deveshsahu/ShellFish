#pragma once
#include "Node.h"

#include <vector>
#include <glm/glm.hpp>

namespace sg
{
	/**
	 * @brief Holds mesh data buffer
	 * TODO Needs to be extended to use CGAL library for
	 * handling and manipulating mesh data
	 */
	class MeshNode final : public Node
	{
	public:
		MeshNode(const std::string& name);
		void setVisibility(bool visible);
		bool getVisibility() const;

		/**
		 * @brief Copy vertex data to the mesh
		 * Accepts only float with 3 vectors
		 */
		void addVertexData(const void* dataStream, size_t numVtx);
		void addIndexData(const void* dataStream, size_t numIdx);

	private:
		bool mVisibility;

		std::vector<glm::vec3> mVertexList;
		std::vector<glm::uvec3> mTriangleIndexList;
		std::vector<glm::vec4> mColorList;
	};
}