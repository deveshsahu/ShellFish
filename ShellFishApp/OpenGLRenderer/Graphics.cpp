#pragma once
#include "Graphics.h"
#include "GLUtils.h"

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
		if (mInitGL)
			return;
		ogl_LoadFunctions();

#ifdef _DEBUG
		glDebugMessageCallback(GLUtils::debugCallback, NULL);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
#endif // _DEBUG

		mInitGL = true;
	}

	void OpenGLGraphics::clear(const glm::vec4& color)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void OpenGLGraphics::viewport(int x, int y, int sx, int sy)
	{
		glViewport(0, 0, sx, sy);
	}
}
