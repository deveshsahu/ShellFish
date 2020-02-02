#pragma once
#include "BufferObject.h"
#include "UniqueIDGenerator.h"
#include <memory>
#include <map>
namespace Graphics
{
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

		VertexBufferObject createVertexBufferObject(void* data, unsigned int dataSize);
		IndexBufferObject createIndexBufferObject(void* data, unsigned int dataSize);
		ColorBufferObject createColorBufferObject(void* data, unsigned int dataSize);

	private:
		BufferManager() {}

		ID generate()
		{
			static UniqueIDGenerator instance;
			return instance.generate();
		}

		std::map<ID, VertexBufferObject> mVertexBufferObjectMap;
		std::map<ID, IndexBufferObject> mIndexBufferObjectMap;
		std::map<ID, ColorBufferObject> mColorBufferObjectMap;
	};
}