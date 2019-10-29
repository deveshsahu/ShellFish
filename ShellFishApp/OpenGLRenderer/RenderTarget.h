#pragma once
#include "opengl.h"
#include <vector>
namespace Graphics
{
	enum rtAttachmentFlag
	{
		RT_DEPTH,
	};

	enum rtTargetFlag
	{
		RT_READ,
		RT_WRITE,
		RT_BOTH
	};

	class RenderTarget
	{
	public:
		RenderTarget(int bufferFlags, int width, int height, unsigned int texUnit);
		bool create();
		void bind();
	
		void bindColorTexture();

	private:
		GLuint m_FrameBufferID;
		GLuint mColorTextureID;
		GLuint mDepthTextureID;

		GLuint mTexUnit;

		int mAttachmentFlags;

		int m_Width, m_Height;
	};
}