#include "WindowManager.h"
namespace controller
{
	WindowManager::~WindowManager()
	{
	}

	WindowManager& WindowManager::getInstance()
	{
		static WindowManager instance;
		return instance;
	}

	WindowManager::WindowManager()
	{
	}
}