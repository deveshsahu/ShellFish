#include "BackgroundRenderable.h"
#include "utils.h"
#include <glm/glm.hpp>
#include <vector>

namespace Graphics
{
	BackgroundRenderable::BackgroundRenderable(const std::string& name):
		BaseRenderable(name)
	{
		setDirty(VTX);
	}

	/*void BackgroundRenderable::setInfo(const bkgInfo & info)
	{
		mInfo = info;
	}*/

	bool BackgroundRenderable::init()
	{
		mProgram.addShader("BackgroundVertex");
		mProgram.addShader("BackgroundFragment");
		if (!mProgram.createProgram())
			return false;

		mUpdateVtx();

		if (mInfo.type == bkgType::IMG)
			mUpdateTex();

		GLint blockSize;
		auto program = mProgram.getProgramHandle();
		GLuint blockIndex = glGetUniformBlockIndex(program, "bkgInfo");
		glGetActiveUniformBlockiv(program, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
		GLubyte * blockBuffer = (GLubyte*)malloc(blockSize);

		const GLchar* names[] = {"type", "color", "color2"};
		GLuint indices[3];
		glGetUniformIndices(program, 3, names, indices);
		GLint offset[3];
		glGetActiveUniformsiv(program, 3, indices, GL_UNIFORM_OFFSET, offset);

		memcpy(blockBuffer + offset[0], &mInfo.type, sizeof(int));
		memcpy(blockBuffer + offset[1], &mInfo.color, sizeof(float) * 4);
		memcpy(blockBuffer + offset[2], &mInfo.color2, sizeof(float) * 4);

		glGenBuffers(1, &mUniformBlock);
		glBindBuffer(GL_UNIFORM_BUFFER, mUniformBlock);
		glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer, GL_DYNAMIC_DRAW);

		return true;
	}

	void BackgroundRenderable::draw()
	{
		mProgram.useProgram();
		glActiveTexture(GL_TEXTURE0);

		glBindBufferBase(GL_UNIFORM_BUFFER, 1, mUniformBlock); // Binding point-> binding = 1
		glBindVertexArray(m_vao);
		if (mInfo.type == bkgType::IMG)
			glBindTexture(GL_TEXTURE_2D, m_tex);
		GLUtils::checkForOpenGLError(__FILE__, __LINE__);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}

	void BackgroundRenderable::mUpdateVtx()
	{
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		std::vector<glm::vec2> data = {
			glm::vec2(-1, -1),
			glm::vec2( 1, -1),
			glm::vec2(-1,  1),
			glm::vec2( 1, 1)
		};
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec2), data.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		unsetDirty(VTX);
	}

	void BackgroundRenderable::mUpdateTex()
	{

		int width = 512, height = 512;
		auto data = utils::loadImageFile(mInfo.filename, width, height);
		if (data)
		{
			glActiveTexture(GL_TEXTURE0); // sampler refers to bindin 0
			glGenTextures(1, &m_tex);
			glBindTexture(GL_TEXTURE_2D, m_tex);
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			free(data);
		}
		else
			mInfo.type = bkgType::SOLID;
		unsetDirty(TEX);
	}
	void BackgroundRenderable::mUploadInfo()
	{
	}
}