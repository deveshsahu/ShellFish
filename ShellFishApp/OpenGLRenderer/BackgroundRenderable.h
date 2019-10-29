#pragma once
#include "BaseRenderable.h"
#include "GLSLProgram.h"
#include "glm/glm.hpp"
namespace Graphics
{

	class BackgroundRenderable : public BaseRenderable
	{
		enum DIRTY
		{
			VTX = 1 << 0,
			TEX = 1 << 1
		};

	public:
		enum bkgType
		{
			SOLID = 0,
			IMG = 1,
			GRADIANT = 2,
			SIZE
		};

		struct bkgInfo
		{
			bkgType type = bkgType::SOLID;
			std::string filename;
			glm::vec4 color = glm::vec4(0.6, 0.65, 0.7, 0.7);
			glm::vec4 color2;
		};

	public:
		BackgroundRenderable(const std::string & name);

		inline void setInfo(const bkgInfo& info);

		bool init() override;
		void drawBegin() override;
		void draw() override;
		void drawEnd() override;

	private:
		void mUpdateVtx();
		void mUpdateTex();
		void mUploadInfo();

	private:

		bkgInfo mInfo;

		GLuint m_vao;
		GLuint m_vbo;
		GLuint m_tex;
		GLuint mUniformBlock;

		GLSLProgram mProgram;
	};
}