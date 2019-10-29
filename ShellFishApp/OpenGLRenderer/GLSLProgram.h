#pragma once
#include "GLUtils.h"
#include "ShaderLibrary.h"

#include <vector>

namespace Graphics
{
	class GLSLProgram
	{
	public:
		GLSLProgram() = default;
		bool createProgram();
		void addShader(const std::string& shaderName);
		void useProgram();
		GLuint getProgramHandle() const;

	private:
		GLuint m_ProgramID = GLUtils::INVALID;
		std::vector<std::shared_ptr<Shader>> m_ShaderList;
	};
}