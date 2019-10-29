#pragma once
#include "RenderTarget.h"
#include "GLSLProgram.h"
#include "ViewMatrix.h"
#include "MouseEvent.h"
#include "Camera.h"
#include <vector>
#include <memory>
#include <string>

namespace Graphics
{
	class BaseRenderable;
	class BackgroundRenderable;
	class Scene
	{
	public:
		Scene(int width, int height);
		Scene(const std::string& filename, int width, int height);
		
		void init();
		void render();
		void dispose();

		void addRenderable(std::shared_ptr<BaseRenderable> renderable);
		void addBackground(const std::string filepath);

		///////// EVENTS //////////////////////
		void resize(int width, int height);
		void mouseMove(double xpos, double ypos);
		void mouseButton(MouseButtonEvent evt);
		void mouseScroll(double xoffset, double yoffset);

	protected:

		void mUploadViewMatrix();

		void mBeginFrame();
		void mDraw();
		void mEndFrame();

	protected:
		int mWidth = 0, mHeight = 0;
		std::vector<std::shared_ptr<BaseRenderable>> mRenderables;
		std::shared_ptr<BackgroundRenderable> mBackgroundRenderable;

		RenderTarget mModelRenderTarget;
		RenderTarget mBackgroundRenderTarget;

		Camera mCamera;
		ViewMatrix mViewMatrix;

		GLSLProgram mCompositingProgram;
		GLuint mCompositingVao = ~0;

		GLuint mViewMatrixBuffer = ~0;

		glm::mat4 mModelMatrix;

		bool mInitFailed = false;

		bool mLeftMousePressed = false;
		glm::dvec2 mInitialLocation;
		int mModifier = Modifier::modInvalid;
	};
}