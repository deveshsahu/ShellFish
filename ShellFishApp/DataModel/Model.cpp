#include "Model.h"
#include "../Scenegraph/Node.h"
#include "GLTFLoader.h"
#include "AIParser.h"

namespace model
{
	Model::Model()
	{
	}

	Model::~Model()
	{
	}

	bool Model::load(const std::string& filePath)
	{
		std::string extension = filePath.substr(filePath.find_last_of(".") + 1);
		mSceneGraphRoot = loader::AIParser::loadFromFile(filePath);
		//if (extension == "glb" || extension == "GLB")
		//{
		//	mSceneGraphRoot = loader::AIParser::loadFromFile(filePath)/*loader::GLTFLoader::loadFromBinFile(filePath)*/;
		//}
		//else if ( extension == "gltf" || extension == "GLTF")
		//{
		//	mSceneGraphRoot = loader::GLTFLoader::loadFromASCIIFile(filePath);
		//}
		return false;
	}
}