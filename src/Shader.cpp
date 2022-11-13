#include "Shader.hpp"
#include <iostream>


	Shader::Shader()
	{
		_valid = false;
		ID = 0;
	}

	void Shader::initialize(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		ID = 0;
		_valid = true;

		auto vertexShaderSource = loadFileAsCharArray(vertexShaderPath);
		auto fragmentShaderSource = loadFileAsCharArray(fragmentShaderPath);
		auto vertexShaderSourcePointer = vertexShaderSource.get();
		auto fragmentShaderSourcePointer = fragmentShaderSource.get();

		if (vertexShaderSource == 0 || fragmentShaderSource == 0)
		{
			std::cerr << "Shader Source Path Doesn't Exist\n";
			_valid = false;
			return;
		}

		int result;
		char info[512];

		unsigned int vert = glCreateShader(GL_VERTEX_SHADER), frag = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(vert, 1, &vertexShaderSourcePointer, 0);
		glCompileShader(vert);

		glGetShaderiv(vert, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(vert, 512, 0, info);
			std::cerr << "Vertex Shader Couldn't Compile:\n" << info << "\n\n";
			_valid = false;
		}

		glShaderSource(frag, 1, &fragmentShaderSourcePointer, 0);
		glCompileShader(frag);

		glGetShaderiv(frag, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(frag, 512, 0, info);
			std::cerr << "Fragment Shader Couldn't Compile:\n" << info << "\n\n";
			_valid = false;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vert);
		glAttachShader(ID, frag);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &result);
		if (!result)
		{
			glGetProgramInfoLog(ID, 512, 0, info);
			std::cout << "Shader Program couldn't Link:\n" << info << "\n\n";
			_valid = false;
		}

		glDeleteShader(vert);
		glDeleteShader(frag);
	}

	Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		initialize(vertexShaderPath, fragmentShaderPath);
	}

	void Shader::setBool(const char* name, bool value)
	{
		glUniform1i(glGetUniformLocation(ID, name),(int)value);
	}

	void Shader::setInt(const char* name, int value)
	{
		glUniform1i(glGetUniformLocation(ID, name), value);
	}

	void Shader::setFloat(const char* name, float value)
	{
		glUniform1f(glGetUniformLocation(ID, name), value);
	}

	void Shader::setVec4(const char* name, float x, float y, float z, float w)
	{

		glUniform4f(glGetUniformLocation(ID, name), x,y,z,w);
	}

	void Shader::setMat4(const char* name, float* valuePtr)
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, valuePtr);
	}