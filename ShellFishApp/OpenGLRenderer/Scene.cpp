#include "Scene.h"
#include "GLUtils.h"
#include "BackgroundRenderable.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
namespace Graphics
{
	Scene::Scene(int width, int height) :
		mWidth(width),
		mHeight(height),
		mModelRenderTarget(rtTargetFlag::RT_BOTH, width, height, 1),
		mBackgroundRenderTarget(rtTargetFlag::RT_BOTH, width, height, 0)
	{
	}

	Scene::Scene(const std::string& filename, int width, int height):
		mWidth(width),
		mHeight(height),
		mModelRenderTarget(rtTargetFlag::RT_BOTH, width, height, 1),
		mBackgroundRenderTarget(rtTargetFlag::RT_BOTH, width, height, 0)
	{
		
	}

	void Scene::init()
	{
		GLUtils::printInfo();
		if (!mModelRenderTarget.create())
		{
			mInitFailed = true;
			return;
		}

		mCamera.updateCamera();

		auto vmat = mCamera.getViewMatrix();
		auto vpmat = mCamera.getViewProjectionMatrix();
		GLubyte * viewMatrixData = new GLubyte[128];
		memcpy(viewMatrixData, &vmat[0][0], sizeof(glm::mat4));
		memcpy(viewMatrixData + 64, &vpmat[0][0], sizeof(glm::mat4));

		glGenBuffers(1, &mViewMatrixBuffer);
		glBindBuffer(GL_UNIFORM_BUFFER, mViewMatrixBuffer);
		glBufferData(GL_UNIFORM_BUFFER, 128, viewMatrixData, GL_DYNAMIC_DRAW);

		for (auto& renderable : mRenderables)
		{
			if (!renderable->init())
			{
				std::cerr << "ERROR: Failed to initialize renderables!" << std::endl;
				mInitFailed = true;
				return;
			}
			renderable->setViewMatrixUniformBuffer(mViewMatrixBuffer);
		}

		if (mBackgroundRenderTarget.create())
		{
			if (!mBackgroundRenderable->init())
			{
				std::cerr << "ERROR: Failed to initialize background!" << std::endl;
				mInitFailed = true;
			}
		}

		// Initialize compositing program
		mCompositingProgram.addShader("ResolveVertex");
		mCompositingProgram.addShader("ResolveFragment");
		if (!mCompositingProgram.createProgram())
		{
			std::cerr << "ERROR: Failed to create Compositing program!" << std::endl;
		}
		glGenVertexArrays(1, &mCompositingVao);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK); // Discard back face
	}

	void Scene::render()
	{
		if (mInitFailed)
			return;
		mBeginFrame();
		mDraw();
		mEndFrame();
	}

	void Scene::resize(int width, int height)
	{
		mWidth = width;
		mHeight = height;
	}

	void Scene::mouseMove(double xpos, double ypos)
	{
		if (mLeftMousePressed)
		{
			if (mModifier == Modifier::modCtrl)
			{
				double deltax = (xpos - mInitialLocation.x) * 0.001,
					deltay = -(ypos - mInitialLocation.y) * 0.001;
				mModelMatrix = glm::translate(glm::mat4(1.f), glm::vec3((float)deltax, (float)deltay, 0.f)) * mModelMatrix;
				mInitialLocation.x = xpos;
				mInitialLocation.y = ypos;
				mUploadViewMatrix();
			}
			else
			{
				double deltax = (xpos - mInitialLocation.x) * 0.1 * 3.14 / 180.0;
				double deltay = (ypos - mInitialLocation.y) * 0.1 * 3.14 / 180.0;
				mModelMatrix = glm::rotate(glm::mat4(1.f), (float)deltax, glm::vec3(0, 1, 0)) * mModelMatrix;
				mModelMatrix = glm::rotate(glm::mat4(1.f), (float)deltay, glm::vec3(1, 0, 0)) * mModelMatrix;
				mInitialLocation.x = xpos;
				mInitialLocation.y = ypos;
				mUploadViewMatrix();
			}
		}
	}

	void Scene::mouseButton(MouseButtonEvent evt)
	{
		switch (evt.button)
		{
		case Graphics::mbLeft:
		{
			if (evt.state == ButtonState::bsPressed)
			{
				mLeftMousePressed = true;
				mModifier = evt.mods;
				mInitialLocation.x = evt.xpos;
				mInitialLocation.y = evt.ypos;
			}
			else if (evt.state == ButtonState::bsReleased)
			{
				mLeftMousePressed = false;
				mModifier = Modifier::modInvalid;
			}
		}
			break;
		case Graphics::mbRight:
			break;
		case Graphics::mbMiddle:
			break;
		default:
			break;
		}
	}

	void Scene::mouseScroll(double xoffset, double yoffset)
	{
		float scale = yoffset > 0 ? 1.f / 0.9f : 0.9f;
		mModelMatrix = glm::scale(glm::mat4(1.f), glm::vec3(scale)) * mModelMatrix;
		mUploadViewMatrix();
	}

	void Scene::dispose()
	{
		
	}

	void Scene::addRenderable(std::shared_ptr<BaseRenderable> renderable)
	{
		mRenderables.push_back(renderable);
	}

	void Scene::addBackground(const std::string filepath)
	{
		mBackgroundRenderable = std::make_shared<BackgroundRenderable>("Background");
	}

	void Scene::mUploadViewMatrix()
	{
		auto vmat = mCamera.getViewMatrix() * mModelMatrix;
		auto vpmat = mCamera.getViewProjectionMatrix() * mModelMatrix;
		GLubyte * viewMatrixData = new GLubyte[128];
		memcpy(viewMatrixData, &vmat[0][0], sizeof(glm::mat4));
		memcpy(viewMatrixData + 64, &vpmat[0][0], sizeof(glm::mat4));
		glBindBuffer(GL_UNIFORM_BUFFER, mViewMatrixBuffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, 128, viewMatrixData);
		delete[] viewMatrixData;
	}

	void Scene::mBeginFrame()
	{
	}

	void Scene::mDraw()
	{
		mModelRenderTarget.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto& renderable : mRenderables)
		{
			renderable->drawBegin();
			renderable->draw();
			renderable->drawEnd();
		}
	}

	void Scene::mEndFrame()
	{
		mBackgroundRenderTarget.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mBackgroundRenderable->drawBegin();
		mBackgroundRenderable->draw();
		mBackgroundRenderable->drawEnd();
		GLUtils::checkForOpenGLError(__FILE__, __LINE__);

		glBindFramebuffer(GL_FRAMEBUFFER, 0); // Switch to default frame buffer
		glViewport(0, 0, mWidth, mHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mCompositingProgram.useProgram();
		glActiveTexture(GL_TEXTURE1);
		mModelRenderTarget.bindColorTexture();
		glActiveTexture(GL_TEXTURE0);
		mBackgroundRenderTarget.bindColorTexture();
		glBindVertexArray(mCompositingVao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

}