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

	void OpenGLGraphics::render()
	{
	}
}
