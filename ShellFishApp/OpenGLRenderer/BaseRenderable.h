#pragma once

#include "opengl.h"
#include <glm/glm.hpp>
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
		void setModelMatrix(const glm::mat4& mat) { mModelMatrix = mat; }
		glm::mat4 getModelMatrix() const { return mModelMatrix; }

		void unsetDirty(int flag) { m_DirtyFlag &= ~flag; }
		void setDirty(int flag) { m_DirtyFlag |= flag; }
		bool isDirty(int flag) { return m_DirtyFlag & flag; }

	protected:
		std::string m_Name;
		size_t m_DirtyFlag = 0;
		glm::mat4 mModelMatrix = glm::mat4(1.f);
	};
}// namespace Graphics