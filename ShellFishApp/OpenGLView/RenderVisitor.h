#pragma once

#include "BaseVisitor.h"

#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace Graphics
{
	class BaseRenderable;
}

namespace view
{
	struct Transforms
	{
		glm::mat4 projectionMatrix;
		glm::mat4 modelViewMatrix;
		glm::mat4 mvpMatrix;
	};

	/**
	 * @brief Traverses the scenegraph, initializes all render objects and populate
	 * the list of renderables that needs to be drawn
	 *
	 * Create an object of this type and provide it a list of renderables to populate
	 * This objects in this list can the be rendered directly. The scene graph can be
	 * periodically scanned for changes and this list can be updated as required
	 */
	class RenderVisitor : public sg::BaseVisitor
	{
	public:
		RenderVisitor(std::vector<std::weak_ptr<Graphics::BaseRenderable>>& inRenderableList);
		~RenderVisitor();
		void visit(std::shared_ptr<sg::CameraNode> camnode) override;
		void visit(std::shared_ptr<sg::TransformNode> xformnode) override;
		void visit(std::shared_ptr<sg::MeshNode> meshnode) override;
		void visit(std::shared_ptr<sg::GroupNode> grpnode) override;
		//void visit(std::shared_ptr<sg::Node> node) override;
		
	private:
		std::shared_ptr<RenderVisitor> getSharedFromThis();
		Transforms mTransforms;
		std::vector<std::weak_ptr<Graphics::BaseRenderable>>& mRenderableList;
	};
}