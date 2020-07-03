#pragma once
#include "Model.h"

namespace model
{
	class SyntheticModel : public Model
	{
	public:
		bool load(const std::string& fileName = "");
	};
}