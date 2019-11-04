#include <iostream>
#include <stdexcept>
#include <memory>

#include "MainWindow.h"
#include "../DataModel/Model.h"

int main()
{
	// Controller
	controller::MainWindow myWindow;
	std::shared_ptr<model::Model> myModel = std::make_shared<model::Model>();
	myModel->load("D:\\Downloads\\FirefoxDownloads\\GLTF Samples\\Lantern.glb");
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
