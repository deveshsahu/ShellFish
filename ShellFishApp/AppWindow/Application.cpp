#include <iostream>
#include <stdexcept>
#include <memory>

#include "MainWindow.h"
#include "../DataModel/Model.h"
//#include "../OpenGLView/"

int main()
{
	// Controller
	controller::MainWindow myWindow;
	std::shared_ptr<model::Model> myModel;

	try
	{
		myWindow.run();
	}
	catch (const std::runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
		return EXIT_FAILURE;
	}
}
