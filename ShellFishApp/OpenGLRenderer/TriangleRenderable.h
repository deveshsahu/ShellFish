#pragma once
#include "BaseRenderable.h"
#include "GLSLProgram.h"
#include <glm/glm.hpp>

namespace Graphics
{
	class TriangleRenderable : public BaseRenderable
	{
	public:
		enum DIRTY
		{
			VTX = 1 << 0,
			CLR = 1 << 1
		};

	public:
		TriangleRenderable(const std::string& name, std::vector<glm::vec3>& vertex, std::vector<unsigned int>& index);
		~TriangleRenderable();

		bool init() override;
		void drawBegin() override;
		void draw() override;
		void drawEnd() override;

		void setColor(const glm::vec4& col) { mColor = col; }

	protected:
		void updateVtx();

	private:
		GLuint mVtxBufferId = ~0,
			mIdxBufferId = ~0;

		GLuint m_vao = ~0;

		std::vector <glm::vec3> mVertexData;
		std::vector <unsigned int> mIndexData;
		glm::vec4 mColor;

		GLSLProgram mProgram;
	};
}//namespace Graphics