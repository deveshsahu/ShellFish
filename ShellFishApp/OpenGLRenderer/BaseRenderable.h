#pragma once

#include "opengl.h"
#include <string>

namespace Graphics
{
	class BaseRenderable
	{
	public:
		BaseRenderable(const std::string& name) : m_Name(name) {}
		virtual ~BaseRenderable() {}

		/**@brief Create any underlying data structure eg file loading */
		virtual bool create() { return true; }

		/**@brief Initialize buffers, etc. that require context to be current */
		virtual bool init() { return true; }

		/**@brief Prepare for rendering, eg clearing buffers etc */
		virtual void drawBegin() {};

		/**@brief Bind and draw */
		virtual void draw() = 0;

		/**@brief Unbind and post render cleanup */
		virtual void drawEnd() {}

		std::string getName() { return m_Name; }

		void setViewMatrixUniformBuffer(GLuint bufferID) { mViewMatrixUniformBufferID = bufferID; }

		void unsetDirty(int flag) { m_DirtyFlag &= ~flag; }
		void setDirty(int flag) { m_DirtyFlag |= flag; }
		bool isDirty(int flag) { return m_DirtyFlag & flag; }

	protected:
		std::string m_Name;
		size_t m_DirtyFlag = 0;
		GLuint mViewMatrixUniformBufferID = ~0;
	};
}// namespace Graphics