#pragma once

#include <vector>
namespace Graphics
{
	class BufferObject;
	/**
	 * @brief Singleton class to manage all buffer types
	 */
	class BufferManager
	{
	public:
		static BufferManager& getInstance()
		{
			static BufferManager instance;
			return instance;
		}

		BufferManager(BufferManager const&) = delete;
		void operator=(BufferManager const&) = delete;

	private:
		BufferManager() {}

		std::vector<BufferObject> mBufferObjectList;
	};
}