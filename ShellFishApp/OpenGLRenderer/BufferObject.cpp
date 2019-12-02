#include "BufferObject.h"

namespace Graphics
{
	BufferObject::BufferObject(BufferObjectType type, void* data, unsigned int dataSize):
		mType(type),
		mData(data),
		mDataSize(dataSize)
	{
	}

	VertexBufferObject::VertexBufferObject(void* data, unsigned int dataSize) :
		BufferObject(BufferObjectType::VERTEX, data, dataSize)
	{
	}

	IndexBufferObject::IndexBufferObject(void* data, unsigned int dataSize):
		BufferObject(BufferObjectType::INDEX, data, dataSize)
	{
	}
	
	ColorBufferObject::ColorBufferObject(void* data, unsigned int dataSize):
		BufferObject(BufferObjectType::COLOR, data, dataSize)
	{
	}



}