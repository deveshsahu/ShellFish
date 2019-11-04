#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include <unordered_map>

namespace model
{
	class Model;
}

namespace view
{
	class SceneGraphViewer;
}

namespace controller
{
	class MainWindow
	{
	public:
		MainWindow() = default;
		~MainWindow() = default;

		void run();

		// Glfw Callbacks
		static void onCheckError(int error, const char* description);
		static void onWindowResized(GLFWwindow*, int, int);
		static void onMouseMove(GLFWwindow*, double, double);
		static void onMouseButton(GLFWwindow*, int, int, int);
		static void onMouseScroll(GLFWwindow*, double, double);

		void createWindow();
		void activateContext();
		bool loadFile();

	private:
		void mInitWindow();
		void mMainLoop();
		void mCleanup();

	private:
		GLFWwindow* mGLWindow;
		std::shared_ptr<model::Model> mModel;
		std::shared_ptr<view::SceneGraphViewer> mViewer;
	};
}

