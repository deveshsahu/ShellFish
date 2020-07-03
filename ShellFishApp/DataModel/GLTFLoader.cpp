#include "GLTFLoader.h"
// Define these only in *one* .cc file.
#ifndef MY_TINY_GLTF_H
#define MY_TINY_GLTF_H
#ifndef TINYGLTF_IMPLEMENTATION
#define TINYGLTF_IMPLEMENTATION
#endif
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif
#define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifndef STBI_MSC_SECURE_CRT
#define STBI_MSC_SECURE_CRT
#endif
#include <tiny_gltf/tiny_gltf.h>

#include "../Scenegraph/OrthoCamNode.h"
#include "../Scenegraph/PerspectiveCamNode.h"

namespace loader
{

	std::shared_ptr<sg::Node> populateSceneGraph(tinygltf::Model& model)
	{
		std::shared_ptr<sg::Node> root;
		if (model.cameras.size() > 0)
		{
			auto& cam = model.cameras[0];
			std::shared_ptr<sg::CameraNode> cameranode;
			if (cam.type == "orthographic")
			{
				auto orthonode = std::make_shared < sg::OrthoCamNode > ();
				orthonode->setOrthoParam(cam.orthographic.xmag, cam.orthographic.ymag, cam.orthographic.znear, cam.orthographic.zfar);
				cameranode = orthonode;
			}
			else
			{
				auto perspcamnode = std::make_shared<sg::PerspectiveCamNode>();
				perspcamnode->setPerspParam(cam.perspective.aspectRatio, cam.perspective.yfov, cam.perspective.znear, cam.perspective.zfar);
				cameranode = perspcamnode;
			}
			root = cameranode;
			return cameranode;
		}
		else
		{
			auto orthonode = std::make_shared < sg::OrthoCamNode >();
			orthonode->setOrthoParam(1.0, 1.0, 0.1, 100.0);
			root = orthonode;
		}
		
		return root;
	}

	std::shared_ptr<sg::Node> GLTFLoader::loadFromBinFile(const std::string& filepath)
	{
		std::string err;
		std::string warn;
		tinygltf::TinyGLTF loader;
		auto tinygltfModel = new tinygltf::Model();
		// Check file extension to check if it is binary
		if (!loader.LoadBinaryFromFile(tinygltfModel, &err, &warn, filepath))
		{
			if (!warn.empty()) {
				printf("Warn: %s\n", warn.c_str());
			}

			if (!err.empty()) {
				printf("Err: %s\n", err.c_str());
			}
			return std::shared_ptr<sg::Node>();
		}

		return populateSceneGraph(*tinygltfModel);
	}

	std::shared_ptr<sg::Node> GLTFLoader::loadFromASCIIFile(const std::string& filepath)
	{
		std::string err;
		std::string warn;
		tinygltf::TinyGLTF loader;
		auto tinygltfModel = new tinygltf::Model();
		// Check file extension to check if it is binary or ascii
		if (!loader.LoadASCIIFromFile(tinygltfModel, &err, &warn, filepath))
		{
			if (!warn.empty()) {
				printf("Warn: %s\n", warn.c_str());
			}

			if (!err.empty()) {
				printf("Err: %s\n", err.c_str());
			}
			return std::shared_ptr<sg::Node>();
		}

		return populateSceneGraph(*tinygltfModel);
	}
}
#endif