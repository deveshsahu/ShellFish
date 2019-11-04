#include "Model.h"
#include "../Scenegraph/Node.h"
#include "GLTFLoader.h"

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
		if (extension == "glb" || extension == "GLB")
		{
			mSceneGraphRoot = loader::GLTFLoader::loadFromBinFile(filePath);
		}
		else if ( extension == "gltf" || extension == "GLTF")
		{
			mSceneGraphRoot = loader::GLTFLoader::loadFromASCIIFile(filePath);
		}
		return false;
	}
}