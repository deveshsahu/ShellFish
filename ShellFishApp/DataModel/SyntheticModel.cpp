#include "SyntheticModel.h"

#include "../Scenegraph/CameraNode.h"
#include "../Scenegraph/MeshNode.h"
#include "../Scenegraph/TransformNode.h"
#include <glm/gtx/transform.hpp>

namespace model
{

	bool SyntheticModel::load(const std::string& fileName)
	{
		// Create a synthetic model here
		auto camnode = std::make_shared<sg::CameraNode>();
		camnode->setPerspParam(45.f, 1.33f, 0.01f, 1000.f); // Projection matrix fov, aspect ratio, near and far planes
		camnode->setCamera(glm::vec3(1, 1, -1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // eye position, model's center and up direction

		// Create Group Node
		auto grpnode = std::make_shared<sg::GroupNode>("Group mesh");
		

		// Create two transform nodes
		auto xformnode1 = std::make_shared<sg::TransformNode>("mesh1 xform");
		glm::mat4 xform = glm::scale(glm::mat4(1.f), glm::vec3(0.2f));
		xform = glm::translate(glm::mat4(1.f), glm::vec3(-0.5, 0.2, 0))*xform;
		xformnode1->setTransform(xform);

		auto xformnode2 = std::make_shared<sg::TransformNode>("mesh2 xform");
		xform = glm::scale(glm::mat4(1.f), glm::vec3(0.5f));
		xform = glm::translate(glm::mat4(1.f), glm::vec3(0.5, 0.0f, 0)) * xform;
		xformnode2->setTransform(xform);

		// Mesh data
		std::vector<glm::vec3> vtxdata = {
			glm::vec3(0.5, 0.5, 0.5),
			glm::vec3(0.5, 0.5, -0.5),
			glm::vec3(-0.5, 0.5, -0.5),
			glm::vec3(-0.5, 0.5, 0.5),
			
			glm::vec3(0.5, -0.5, 0.5),
			glm::vec3(0.5, -0.5, -0.5),
			glm::vec3(-0.5, -0.5, -0.5),
			glm::vec3(-0.5, -0.5, 0.5)
		};

		std::vector<unsigned int> idxData =
		{
			0, 1, 2, 
			2, 3, 0,
			
			0, 4, 5,
			5, 1, 0,

			1, 5, 6,
			5, 6, 2,

			2, 6, 7,
			6, 7, 3,

			3, 7, 4,
			7, 4, 0,

			4, 6, 5,
			7, 6, 4
		};

		// Create mesh node 
		auto meshnode1 = std::make_shared<sg::MeshNode>("mesh1");
		meshnode1->addVertexData(vtxdata);
		meshnode1->addIndexData(idxData);

		auto meshnode2 = std::make_shared<sg::MeshNode>("mesh2");
		meshnode2->addVertexData(vtxdata);
		meshnode2->addIndexData(idxData);

		meshnode1->setColor(glm::vec4(1, 0, 0, 1));
		meshnode2->setColor(glm::vec4(0, 1, 0, 1));

		meshnode1->finalize();
		meshnode2->finalize();

		mSceneGraphRoot = camnode;
		camnode->addChild(grpnode);

		grpnode->addChild(xformnode1);
		grpnode->addChild(xformnode2);

		xformnode1->addChild(meshnode1);
		xformnode2->addChild(meshnode2);

		return false;
	}
}