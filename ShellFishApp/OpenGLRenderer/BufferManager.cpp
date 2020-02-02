#include "BufferManager.h"

namespace Graphics
{

	VertexBufferObject BufferManager::createVertexBufferObject(void* data, unsigned int dataSize)
	{
		auto id = generate();
		VertexBufferObject vbo(data, dataSize, id);
		mVertexBufferObjectMap.emplace(id, vbo);
		return vbo;
	}

	IndexBufferObject BufferManager::createIndexBufferObject(void* data, unsigned int dataSize)
	{
		auto id = generate();
		IndexBufferObject ibo(data, dataSize, id);
		mIndexBufferObjectMap.emplace(id, ibo);
		return ibo;
	}

	ColorBufferObject BufferManager::createColorBufferObject(void* data, unsigned int dataSize)
	{
		auto id = generate();
		ColorBufferObject cbo(data, dataSize, id);
		mColorBufferObjectMap.emplace(id, cbo);
		return cbo;
	}
}