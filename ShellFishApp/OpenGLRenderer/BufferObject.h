#pragma once
#include <cstdint>
namespace Graphics
{
	enum class BufferObjectType
	{
		VERTEX,
		INDEX,
		COLOR,
		INVALID
	};

	using ID = uint32_t;

	class BufferObject
	{
	public:
		BufferObject(BufferObjectType type, void * data, unsigned int dataSize, ID id);

		virtual void create();

		virtual void bind();

		BufferObjectType getBufferObjectType() const { return mType; }

		ID getID() const { return mID; }
	
	protected:
		BufferObjectType mType = BufferObjectType::INVALID;

		void* mData;

		unsigned int mDataSize;

		unsigned long mBufferIdx;

		const ID mID;
	};

	// Refer http://www.songho.ca/opengl/gl_vbo.html
	class VertexBufferObject : public BufferObject
	{
	public:
		VertexBufferObject(void* data, unsigned int dataSize, ID id);
	private:
	};

	class IndexBufferObject :public BufferObject
	{
	public:
		IndexBufferObject(void* data, unsigned int dataSize, ID id);
	private:
	};

	class ColorBufferObject : public BufferObject
	{
	public:
		ColorBufferObject(void* data, unsigned int dataSize, ID id);
	};

}