#include <iostream>
#include <stdexcept>
#include <memory>

#include "MainWindow.h"
#include "../DataModel/Model.h"

int main(int argc, char* argv[])
{
	std::string filePath;
	if (argc > 1)
	{
		filePath = argv[1]; // Check if filname is valid;
	}
	else
	{
		filePath = "..\\..\\..\\shellfish\\BoxVertexColors.glb";
	}

	// Controller
	controller::MainWindow myWindow;
	std::shared_ptr<model::Model> myModel = std::make_shared<model::Model>();
	myModel->load(filePath);
	myWindow.addModel(myModel);

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
