#include "MainWindow.h"
//#include "MouseEvent.h"
#include "../DataModel/Model.h"
#include "../OpenGLRenderer/Graphics.h"
#include <assert.h>
#include <iostream>

static const int WIDTH = 800;
static const int HEIGHT = 600;

namespace controller
{
	void MainWindow::run()
	{
		mInitWindow();
		mMainLoop();
		mCleanup();
	}

	void MainWindow::onWindowResized(GLFWwindow* window, int width, int height)
	{

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

	bool MainWindow::loadFile()
	{
		mModel = std::make_shared<model::Model>();
		if (!mModel->load("D:\\FirefoxDownloads\\GLTF Samples\\Lantern.glb"))
			return false;
		return true;
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

		mGLWindow = glfwCreateWindow(WIDTH, HEIGHT, "Main Window", nullptr, nullptr);
		assert(mGLWindow != nullptr);
		glfwSetWindowUserPointer(mGLWindow, this);
		// Window Resize
		glfwSetWindowSizeCallback(mGLWindow, MainWindow::onWindowResized);
		// Mouse Move
		glfwSetCursorPosCallback(mGLWindow, MainWindow::onMouseMove);
		// Mouse button
		glfwSetMouseButtonCallback(mGLWindow, MainWindow::onMouseButton);
		// Mouse scroll
		glfwSetScrollCallback(mGLWindow, MainWindow::onMouseScroll);
	}

	void MainWindow::mMainLoop()
	{
		//auto scene = mActiveScene.lock();
		while (!glfwWindowShouldClose(mGLWindow))
		{
			glfwMakeContextCurrent(mGLWindow);
			//Graphics::OpenGLGraphics::getInstance().render();
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