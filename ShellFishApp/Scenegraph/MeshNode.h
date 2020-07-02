#pragma once
#include "Node.h"

#include <vector>
#include <glm/glm.hpp>
#include "../OpenGLRenderer/BaseRenderable.h"

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
		inline void setVisibility(bool visible) { mVisibility = visible; }
		inline bool getVisibility() const { return mVisibility; }

		/**
		 * @brief Copy vertex data to the mesh
		 * Accepts only float with 3 vectors
		 */
		void addVertexData(const std::vector<glm::vec3>& vtxdata);
		void addIndexData(const std::vector<unsigned int>& idxdata);
		void addRenderable(std::shared_ptr<Graphics::BaseRenderable>& renderable) { mRenderable = renderable; }
		std::weak_ptr<Graphics::BaseRenderable> getRenderable() const { return mRenderable; }
		virtual void visit(std::shared_ptr<BaseVisitor> visitor) override;
		void finalize();
		void setColor(const glm::vec4& col) {
			mColor = col;
		}

	private:
		std::shared_ptr<MeshNode> getSharedFromThis();
		bool mVisibility = true;
		std::vector<glm::vec3> mVertexList;
		std::vector<unsigned int> mTriangleIndexList;
		std::vector<glm::vec4> mColorList;
		glm::vec4 mColor;

		std::shared_ptr<Graphics::BaseRenderable> mRenderable;
	};
}