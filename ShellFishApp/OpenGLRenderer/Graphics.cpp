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

	void OpenGLGraphics::initGL()
	{
		ogl_LoadFunctions();

#ifdef _DEBUG
		glDebugMessageCallback(GLUtils::debugCallback, NULL);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
#endif // _DEBUG
	}

	void OpenGLGraphics::render()
	{
	}
}
