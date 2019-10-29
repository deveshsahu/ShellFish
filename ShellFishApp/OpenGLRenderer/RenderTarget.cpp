#include "RenderTarget.h"
#include <iostream>
namespace Graphics
{
	RenderTarget::RenderTarget(int bufferFlags, int width, int height, unsigned int texUnit):
		mAttachmentFlags(bufferFlags),
		m_Width(width),
		m_Height(height),
		mTexUnit(texUnit)
	{
	}

	bool RenderTarget::create()
	{
		glCreateFramebuffers(1, &m_FrameBufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);

		glActiveTexture(GL_TEXTURE0 + mTexUnit);
		glGenTextures(1, &mColorTextureID);
		glBindTexture(GL_TEXTURE_2D, mColorTextureID);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, m_Width, m_Height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, mColorTextureID, 0);

		// Optional attachments
		if (mAttachmentFlags | RT_DEPTH)
		{
			/*glGenRenderbuffers(1, &m_DepthBufferID);
			glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBufferID);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Width, m_Height);*/
			glGenTextures(1, &mDepthTextureID);
			glBindTexture(GL_TEXTURE_2D, mDepthTextureID);
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, m_Width, m_Height);

			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, mDepthTextureID, 0);
		}
		GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, DrawBuffers);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cerr << "ERROR: Frambuffer is incomplete!" << std::endl;
			return false;
		}
		return true;
	}
	void RenderTarget::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
		glViewport(0, 0, m_Width, m_Height);
		glActiveTexture(GL_TEXTURE0 + mTexUnit);
	}
	void RenderTarget::bindColorTexture()
	{
		glBindTexture(GL_TEXTURE_2D, mColorTextureID);
	}
}