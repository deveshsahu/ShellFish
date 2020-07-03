#include "AIParser.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "../Scenegraph/CameraNode.h"
#include "../Scenegraph/MeshNode.h"
#include "../Scenegraph/TransformNode.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

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
		std::vector<glm::vec3> vtxData;
		for (int i = 0; i < numvtx; ++i)
		{
			vtxData.emplace_back(aimesh.mVertices[i][0], aimesh.mVertices[i][1], aimesh.mVertices[i][2]);
		}
		meshNode->addVertexData(vtxData);
		// TODO Construct material 
		// Uniform block will be initialized based on shader passed.
		// Write a universal shader that supports rendering all material types
		std::vector<glm::vec3> texcoords;
		std::vector<unsigned int> indexList;
		indexList.reserve(aimesh.mNumFaces * size_t(3)); // Reserve enough space for triangular mesh
		for (int i = 0; i < aimesh.mNumFaces; ++i)
		{
			for (int j = 0; j < aimesh.mFaces->mNumIndices; ++j)
			{
				indexList.push_back(aimesh.mFaces[i].mIndices[j]);
			}
		}
		meshNode->addIndexData(indexList);
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
			camNode->setCameraMatrix(glm::ortho(1.f, 1.f, 0.1f, 1000.f));
		}

		auto modelBaseNode = std::make_shared<sg::GroupNode>("Base Node");
		camNode->addChild(modelBaseNode);
		if (scene->mNumMeshes == 1)
		{
			// Assuming triangle primitive for now
			auto meshNode = std::make_shared<sg::MeshNode>("lonemesh");
			modelBaseNode->addChild(meshNode);
			if (scene->mMeshes[0]->HasPositions())
			{
				const auto& mesh = scene->mMeshes[0];
				std::vector<glm::vec3> vtxList(mesh->mNumVertices);
				for (int i = 0; i < mesh->mNumVertices; ++i)
					vtxList[i] = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
				meshNode->addVertexData(vtxList);
			}

			if (scene->mMeshes[0]->HasFaces())
			{
				const auto& mesh = scene->mMeshes[0];

				std::vector<unsigned int> idxList;
				unsigned int start = 0;
				for (int i = 0; i < mesh->mNumFaces; ++i)
				{
					idxList.resize(start + mesh->mFaces[i].mNumIndices);
					memcpy_s(mesh->mFaces[i].mIndices, mesh->mFaces[i].mNumIndices, &idxList[start], mesh->mFaces[i].mNumIndices);
					start += mesh->mFaces[i].mNumIndices;
				}
				meshNode->addIndexData(idxList);
			}
			meshNode->finalize();
		}
		else
			copyNodes(*scene->mRootNode, modelBaseNode, *scene);

		return camNode;
	}
}