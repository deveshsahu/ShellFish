#pragma once
#include <glm/glm.hpp>
namespace Graphics
{
	// Needs to be padded as per std140
	struct viewmatrix
	{
		glm::mat4 view;				// 64 bits
		glm::mat4 projection;		// 64 bits
		glm::mat4 viewProjection;	// 64 bits
	};

	class ViewBufferObject
	{
	public:
		ViewBufferObject();

		void setProjectionMatrix(const glm::mat4& mat);
		void setViewMatrix(const glm::mat4& mat);
		void init();
		void update(bool force = false);
		void bind();
		void setDirty();

	private:
		bool mDirty = true;
		viewmatrix mViewMatrix;
		unsigned int mUBOhandle = ~0U;
	};
}