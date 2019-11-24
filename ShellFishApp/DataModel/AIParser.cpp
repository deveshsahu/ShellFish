#include "AIParser.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "../Scenegraph/CameraNode.h"
#include "../Scenegraph/MeshNode.h"
#include "../Scenegraph/TransformNode.h"
#include <glm/glm.hpp>

namespace loader
{
	glm::mat4 convertToMat4(const aiMatrix4x4& input)
	{
		glm::mat4 mat;
		mat[0][0] = input.a1;
		mat[0][1] = input.a2;
		mat[0][2] = input.a3;
		mat[0][3] = input.a4;

		mat[1][0] = input.b1;
		mat[1][1] = input.b2;
		mat[1][2] = input.b3;
		mat[1][3] = input.b4;

		mat[2][0] = input.c1;
		mat[2][1] = input.c2;
		mat[2][2] = input.c3;
		mat[2][3] = input.c4;

		mat[3][0] = input.d1;
		mat[3][1] = input.d2;
		mat[3][2] = input.d3;
		mat[3][3] = input.d4;

		return mat;
	}

	bool copyMeshData(std::shared_ptr<sg::MeshNode>& meshNode, const aiMesh& aimesh)
	{
		unsigned int numvtx = aimesh.mNumVertices;
		meshNode->addVertexData(aimesh.mVertices, numvtx);
		// TODO Construct material 
		// Uniform block will be initialized based on shader passed.
		// Write a universal shader that supports rendering all material types
		for (int i = 0; i < aimesh.mNumFaces; ++i)
		{
			
		}
		//meshNode->addIndexData();
		return true;
	}

	void copyNodes(aiNode& node, std::shared_ptr<sg::GroupNode> parent, const aiScene& scene)
	{
		if (node.mNumMeshes > 0)
		{
			for (int i = 0; i < node.mNumMeshes; ++i)
			{
				auto meshNode = std::make_shared<sg::MeshNode>(node.mName.C_Str());
				parent->addChild(meshNode);
				copyMeshData(meshNode, *scene.mMeshes[node.mMeshes[i]]);
			}
			return;
		}

		auto transformNode = std::make_shared<sg::TransformNode>(node.mName.C_Str());
		transformNode->setTransform(convertToMat4(node.mTransformation));
		parent->addChild(transformNode);
		parent = transformNode;

		for (int i = 0; i < node.mNumChildren; i++)
		{
			if (!node.mChildren[i])
				continue;
			copyNodes(*node.mChildren[i], parent, scene);
		}
	}

	std::shared_ptr<sg::Node> AIParser::loadFromFile(const std::string& filepath)
	{
		Assimp::Importer aiImporter;
		const auto scene = aiImporter.ReadFile(filepath, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
		if (!scene)
		{
			//Error
			return std::shared_ptr<sg::Node>();
		}
		std::shared_ptr<sg::CameraNode> camNode = std::make_shared<sg::CameraNode>();
		if (scene->HasCameras())
		{
			camNode->setName(scene->mCameras[0]->mName.C_Str());
			aiMatrix4x4 cammat;
			scene->mCameras[0]->GetCameraMatrix(cammat);
			camNode->setCameraMatrix(convertToMat4(cammat));
		}
		else
		{
			camNode->setOrthoParam(1, 1, 0.1, 100);
		}

		auto modelBaseNode = std::make_shared<sg::GroupNode>("Base Node");
		camNode->addChild(modelBaseNode);
		copyNodes(*scene->mRootNode, modelBaseNode, *scene);

		return camNode;
	}
}