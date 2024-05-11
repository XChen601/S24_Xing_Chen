#include"pch.h"
#include"ShaderOpenGL.h"
#include"glad/glad.h"
#include"Utility.h"

namespace Nugget
{
	ShaderOpenGL::ShaderOpenGL(const std::string& vertexFile, const std::string& fragmentFile)
	{
		std::string vertexShaderCode{ ReadFile(vertexFile) };
		const char* vertexShaderSource{ vertexShaderCode.c_str() };

		std::string fragmentShaderCode{ ReadFile(fragmentFile) };
		const char* fragmentShaderSource{ fragmentShaderCode.c_str()};

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			NUGGET_ERROR("ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog)
		}

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			NUGGET_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog)
		}

		mShaderProg = glCreateProgram();
		glAttachShader(mShaderProg, vertexShader);
		glAttachShader(mShaderProg, fragmentShader);
		glLinkProgram(mShaderProg);

		// check for linking errors
		glGetProgramiv(mShaderProg, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			NUGGET_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog)
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}


	ShaderOpenGL::ShaderOpenGL(std::string&& vertexFile, std::string&& fragmentFile)
	{
		std::string vertexShaderCode{ ReadFile(move(vertexFile)) };
		const char* vertexShaderSource{ vertexShaderCode.c_str() };

		std::string fragmentShaderCode{ ReadFile(move(fragmentFile)) };
		const char* fragmentShaderSource{ fragmentShaderCode.c_str() };

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			NUGGET_ERROR("ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog)
		}

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			NUGGET_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog)
		}

		mShaderProg = glCreateProgram();
		glAttachShader(mShaderProg, vertexShader);
		glAttachShader(mShaderProg, fragmentShader);
		glLinkProgram(mShaderProg);

		// check for linking errors
		glGetProgramiv(mShaderProg, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			NUGGET_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog)
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	ShaderOpenGL::~ShaderOpenGL()
	{
		glDeleteProgram(mShaderProg);
	}

	
	void ShaderOpenGL::Bind()
	{
		glUseProgram(mShaderProg);
	}


	std::string ShaderOpenGL::ReadFile(const std::string& fileName)
	{
		std::string result;
		std::ifstream inputFile{ fileName };

		std::string line;
		while (inputFile)
		{
			std::getline(inputFile, line);
			result.append(line);
			result.append("\n");
		}
		
		return result;
	}


	std::string ShaderOpenGL::ReadFile(std::string&& fileName)
	{	
		std::string result;
		std::ifstream inputFile{ move(fileName) };

		std::string line;
		while (inputFile)
		{
			std::getline(inputFile, line);
			result.append(line);
			result.append("\n");
		}

		return result;
	}
}