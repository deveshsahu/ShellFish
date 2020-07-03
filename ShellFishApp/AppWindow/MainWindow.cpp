#include "MainWindow.h"
//#include "MouseEvent.h"
#include "../DataModel/Model.h"
#include "../OpenGLView/SceneGraphViewer.h"
#include "glm/glm.hpp"
#include <iostream>

namespace controller
{
	MainWindow* MainWindow::mstaticWindowPtr = nullptr;

	void MainWindow::run()
	{
		mInitWindow();
		mMainLoop();
		mCleanup();
	}

	void MainWindow::onWindowResized(GLFWwindow* window, int width, int height)
	{
		if (mstaticWindowPtr)
		{
			mstaticWindowPtr->mWidth = width;
			mstaticWindowPtr->mHeight = height;
			mstaticWindowPtr->mViewer->resizeWindow(width, height);
		}
	}

	void MainWindow::onMouseMove(GLFWwindow* w, double xpos, double ypos)
	{
		if (!w)
			return;
	}

	void MainWindow::onMouseButton(GLFWwindow* w, int button, int action, int mods)
	{
		if (!w)
			return;

		//glfwGetCursorPos(w, &evt.xpos, &evt.ypos);
		/*
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			//evt.button = Graphics::MouseButton::mbLeft;
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			//evt.button = Graphics::MouseButton::mbRight;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			//evt.button = Graphics::MouseButton::mbMiddle;
			break;
		}
		switch (action)
		{
		case GLFW_PRESS:
			//evt.state = Graphics::ButtonState::bsPressed;
			break;
		case GLFW_RELEASE:
			//evt.state = Graphics::ButtonState::bsReleased;
			break;
		default:
			break;
		}

		switch (mods)
		{
		case GLFW_MOD_CONTROL:
			//evt.mods = Graphics::Modifier::modCtrl;
			break;
		case GLFW_MOD_ALT:
			//evt.mods = Graphics::Modifier::modAlt;
			break;
		case GLFW_MOD_SHIFT:
			//evt.mods = Graphics::Modifier::modShift;
			break;
		default:
			//evt.mods = Graphics::Modifier::modInvalid;
		}*/
	}

	void MainWindow::onMouseScroll(GLFWwindow* w, double xoffset, double yoffset)
	{
		if (!w)
			return;
	}

	void MainWindow::createWindow()
	{
	}

	void MainWindow::activateContext()
	{
		glfwMakeContextCurrent(mGLWindow);
	}

	void MainWindow::addModel(std::weak_ptr<model::Model> model)
	{
		mModel = model;
	}

	void MainWindow::onCheckError(int error, const char* description)
	{
		std::cout << "ERROR: " << description << std::endl;
	}

	void MainWindow::mInitWindow()
	{
		glfwSetErrorCallback(onCheckError);
		if (!glfwInit())
			exit(EXIT_FAILURE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		//glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif // DEBUG

		mGLWindow = glfwCreateWindow(mWidth, mHeight, "Main Window", nullptr, nullptr);
		glfwSetWindowUserPointer(mGLWindow, this);
		// Window Resize
		glfwSetWindowSizeCallback(mGLWindow, MainWindow::onWindowResized);
		// Mouse Move
		glfwSetCursorPosCallback(mGLWindow, MainWindow::onMouseMove);
		// Mouse buttonm
		glfwSetMouseButtonCallback(mGLWindow, MainWindow::onMouseButton);
		// Mouse scroll
		glfwSetScrollCallback(mGLWindow, MainWindow::onMouseScroll);

		// Initialize
		glfwMakeContextCurrent(mGLWindow);
		mViewer = std::make_shared<view::SceneGraphViewer>(glm::ivec2(mWidth, mHeight));
		mViewer->init();
		mstaticWindowPtr = this;
	}

	void MainWindow::mMainLoop()
	{
		while (!glfwWindowShouldClose(mGLWindow))
		{
			glfwMakeContextCurrent(mGLWindow);
			if (auto model = mModel.lock())
				mViewer->render(model->getRoot());
			glfwSwapBuffers(mGLWindow);
			glfwWaitEvents();
		}
	}

	void MainWindow::mCleanup()
	{
		glfwDestroyWindow(mGLWindow);
		glfwTerminate();
	}
}