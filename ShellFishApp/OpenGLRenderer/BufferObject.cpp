#include "BufferObject.h"

namespace Graphics
{
	BufferObject::BufferObject(BufferObjectType type, void* data, unsigned int dataSize, ID id):
		mType(type),
		mData(data),
		mDataSize(dataSize),
		mID(id)
	{
	}

	VertexBufferObject::VertexBufferObject(void* data, unsigned int dataSize, ID id) :
		BufferObject(BufferObjectType::VERTEX, data, dataSize, id)
	{
	}

	IndexBufferObject::IndexBufferObject(void* data, unsigned int dataSize, ID id):
		BufferObject(BufferObjectType::INDEX, data, dataSize, id)
	{
	}
	
	ColorBufferObject::ColorBufferObject(void* data, unsigned int dataSize, ID id):
		BufferObject(BufferObjectType::COLOR, data, dataSize, id)
	{
	}



}