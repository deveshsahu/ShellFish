#pragma once
#include "Graphics.h"
#include "Scene.h"

namespace Graphics
{
	OpenGLGraphics::OpenGLGraphics()
	{
	}

	OpenGLGraphics::~OpenGLGraphics()
	{
	}

	OpenGLGraphics& OpenGLGraphics::getInstance()
	{
		static OpenGLGraphics instance;
		return instance;
	}

	/*std::shared_ptr<Scene>*/void OpenGLGraphics::createNewScene(int width, int height)
	{
		mScene = std::make_shared<Scene>(width, height);
	}

	void OpenGLGraphics::createSceneFromFile(const std::string& filename, int width, int height)
	{
		mScene = std::make_shared<Scene>(filename, width, height);
		
		//mScene->addRenderable();
	}

	void OpenGLGraphics::render()
	{
		//mScene->render();
	}
}
