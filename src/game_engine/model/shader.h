#pragma once
#include "../defines.h"
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>

	struct Shader {
		virtual ~Shader();
		void init(const char* vertexShaderFilename, const char* fragmentShaderFilename);

		void bind();
		void unbind();

		GLuint getShaderId();

	private:
		GLuint compile(std::string shaderSource, GLenum type);
		std::string parse(const char* filename);
		GLuint createShader(const char* vertexShaderFilename, const char* fragmentShaderFilename);
		GLuint shaderId;
	};