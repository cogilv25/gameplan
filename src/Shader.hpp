#pragma once
#include <memory>
#include <glad/glad.h>
#include "utilities.hpp"

	extern std::shared_ptr<char> loadFileAsCharArray(const char* path);

	class Shader
	{
	private:
		bool _valid;
	protected:
		Shader();
		void initialize(const char* vertexShaderPath, const char* fragmentShaderPath);
	public:
		unsigned int ID;
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

		void setBool(const char* name, bool value);
		void setInt(const char* name, int value);
		void setFloat(const char* name, float value);
		void setVec4(const char* name, float x, float y, float z, float w);
		void setMat4(const char* name, float* valuePtr);
		
		inline bool isValidShader() { return _valid; }


		friend class Renderer;
	};