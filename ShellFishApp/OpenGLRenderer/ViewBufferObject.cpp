#include "viewBufferObject.h"
#include "opengl.h"

namespace Graphics
{
	ViewBufferObject::ViewBufferObject()
	{
	}

	void ViewBufferObject::setProjectionMatrix(const glm::mat4& mat)
	{
		mViewMatrix.projection = mat;
		mViewMatrix.viewProjection = mat * mViewMatrix.view;
		mDirty = true;
	}

	void ViewBufferObject::setViewMatrix(const glm::mat4& mat)
	{
		mViewMatrix.view = mat;
		mViewMatrix.viewProjection = mViewMatrix.projection * mat;
		mDirty = true;
	}

	void ViewBufferObject::init()
	{
		glGenBuffers(1, &mUBOhandle);
		glBindBuffer(GL_UNIFORM_BUFFER, mUBOhandle);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(viewmatrix), NULL, GL_STATIC_DRAW);
		glBindBufferRange(GL_UNIFORM_BUFFER, 0, mUBOhandle, 0, sizeof(viewmatrix)); // Bind to binding point 0
		mDirty = true;
	}

	void ViewBufferObject::update(bool force)
	{
		if (force || mDirty)
		{
			glBindBuffer(GL_UNIFORM_BUFFER, mUBOhandle);
			glBufferData(GL_UNIFORM_BUFFER, sizeof(viewmatrix), &mViewMatrix, GL_STATIC_DRAW);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
			mDirty = false;
		}
	}

	void ViewBufferObject::bind()
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, mUBOhandle);
	}

	void ViewBufferObject::setDirty()
	{
		mDirty = true;
	}
}