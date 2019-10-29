#pragma once
#include <string>
namespace loader
{
	class GLTFLoader
	{
	public:

		static std::shared_ptr<sg::Node> loadFromBinFile(const std::string& filepath);
		static std::shared_ptr<sg::Node> loadFromASCIIFile(const std::string& filepath);
	};
}