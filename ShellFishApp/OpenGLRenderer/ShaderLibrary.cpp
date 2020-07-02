#include "ShaderLibrary.h"
#include "utils.h"
#include <iostream>

namespace Graphics
{
	using namespace GLUtils;
	ShaderLibrary & ShaderLibrary::getInstance()
	{
		static ShaderLibrary shaderLibrary;
		return shaderLibrary;
	}

	void ShaderLibrary::addShaderFromFile(const std::string& name, const std::string& filePath, SHADER_TYPE type)
	{
		if (type >= SHADER_TYPE::NUM)
		{
			std::cerr << "ERROR: Incorrect shader type\n";
			return;
		}
		auto sourceCode = utils::loadFile(filePath);
		if (sourceCode.empty())
		{
			std::cerr << "ERROR: Could not find shader file \"" << filePath << "\"" << std::endl;
			return;
		}

		auto id = glCreateShader(getShaderEnum(type));
		if (id == 0)
		{
			std::cerr << "ERROR: glCreateShader returned 0\n";
			return;
		}
		GLchar* shaderSource[] = { sourceCode.data() };
		glShaderSource(id, 1, shaderSource, NULL);
		glCompileShader(id);
		GLint result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			std::cerr << "ERROR: Shader compilation failed\n";
			GLint logLen;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLen);
			if (logLen > 0)
			{
				char* log = new char[logLen];
				GLsizei written;
				glGetShaderInfoLog(id, logLen, &written, log);
				std::cout << "INFO: " << log << std::endl;
				delete[] log;
			}
			return;
		}
		m_ShaderList.emplace_back(std::make_shared<Shader>(id, type, name));
	}

	std::shared_ptr<Shader> ShaderLibrary::getShader(const std::string& name)
	{
		for (auto shader : m_ShaderList)
		{
			if (shader->m_name == name)
				return shader;
		}
		return std::shared_ptr<Shader>();
	}

	void ShaderLibrary::initializeDefaultShaders()
	{
		// Load shaders
		addShaderFromFile("SimpleVertex", "../Shader/simple.vs", SHADER_TYPE::VERT);
		addShaderFromFile("SimpleFragment", "../Shader/simple.fs", SHADER_TYPE::FRAG);
		addShaderFromFile("BackgroundVertex", "../Shader/background.vs", SHADER_TYPE::VERT);
		addShaderFromFile("BackgroundFragment", "../Shader/background.fs", SHADER_TYPE::FRAG);
		addShaderFromFile("ResolveVertex", "../Shader/resolve.vs", SHADER_TYPE::VERT);
		addShaderFromFile("ResolveFragment", "../Shader/resolve.fs", SHADER_TYPE::FRAG);
	}
	ShaderLibrary::ShaderLibrary()
	{
		initializeDefaultShaders();
	}
}