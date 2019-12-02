#pragma once
namespace Graphics
{
	enum class BufferObjectType
	{
		VERTEX,
		INDEX,
		COLOR,
		INVALID
	};

	class BufferObject
	{
	public:
		BufferObject(BufferObjectType type, void * data, unsigned int dataSize);

		virtual void create();

		virtual void bind();

		BufferObjectType getBufferObjectType() const { return mType; }
	
	protected:
		BufferObjectType mType = BufferObjectType::INVALID;

		void* mData;

		unsigned int mDataSize;

		unsigned long mBufferIdx;
	};


	class VertexBufferObject : public BufferObject
	{
	public:
		VertexBufferObject(void* data, unsigned int dataSize);


	private:
	};

	class IndexBufferObject :public BufferObject
	{
	public:
		IndexBufferObject(void* data, unsigned int dataSize);
	private:
	};

	class ColorBufferObject : public BufferObject
	{
	public:
		ColorBufferObject(void* data, unsigned int dataSize);
	};

}