#pragma once
#include "glm/glm.hpp"
namespace Graphics
{
	struct ViewMatrix
	{
		glm::mat4 view;
		//glm::mat4 model;
		glm::mat4 viewprojection;
	};
}