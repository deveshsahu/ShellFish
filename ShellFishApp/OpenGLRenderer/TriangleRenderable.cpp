#include "TriangleRenderable.h"
#include "glm/glm.hpp"
#include <vector>

namespace Graphics
{
	TriangleRenderable::TriangleRenderable(const std::string& name, std::vector<glm::vec3>& vertex, std::vector<unsigned int>& index) :
		BaseRenderable(name),
		mVertexData(vertex),
		mIndexData(index)
	{
	}

	TriangleRenderable::~TriangleRenderable()
	{
	}

	bool TriangleRenderable::init()
	{
		return true;
		mProgram.addShader("SimpleVertex");
		mProgram.addShader("SimpleFragment");
		if (!mProgram.createProgram())
			return false;
		updateVtx();
		return true;
	}

	void TriangleRenderable::drawBegin()
	{
		return;
		mProgram.useProgram();
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, mViewMatrixUniformBufferID); // Bound to binding pt 0
		glBindVertexArray(m_vao);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, )
	}

	void TriangleRenderable::draw()
	{
		glClearColor(1.0, 0.0, 0.0, 1.0);
		//glDrawElements(GL_TRIANGLES, mIndexData.size(), GL_UNSIGNED_INT, 0);
	}

	void TriangleRenderable::drawEnd()
	{
		glBindVertexArray(0);
	}

	void TriangleRenderable::updateVtx()
	{
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &mVtxBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, mVtxBufferId);
		glBufferData(GL_ARRAY_BUFFER, mVertexData.size() * sizeof(glm::vec3), mVertexData.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
		
		GLuint mIdxBufferId;
		glGenBuffers(1, &mIdxBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIdxBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndexData.size() * sizeof(unsigned int), mIndexData.data(), GL_STATIC_DRAW);

		unsetDirty(VTX);
	}
}//namespace Graphics