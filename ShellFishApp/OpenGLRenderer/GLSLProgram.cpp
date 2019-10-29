#include "GLSLProgram.h"

namespace Graphics
{
	bool GLSLProgram::createProgram()
	{
		m_ProgramID = glCreateProgram();
		for (const auto& shader : m_ShaderList)
			glAttachShader(m_ProgramID, shader->m_id);
		glLinkProgram(m_ProgramID);

		// Check if program creation failed
		GLint status;
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
			return false;

		return true;
	}

	void GLSLProgram::addShader(const std::string & shaderName)
	{
		if (auto shader = ShaderLibrary::getInstance().getShader(shaderName))
			m_ShaderList.push_back(shader);
	}

	void GLSLProgram::useProgram()
	{
		glUseProgram(m_ProgramID);
	}

	GLuint GLSLProgram::getProgramHandle() const
	{
		return m_ProgramID;
	}
}//namespace Graphics
