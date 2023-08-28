#include "shader.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

namespace Game {
	Shader::Shader(const std::string& vertex_path, const std::string& fragment_path)
	{

		// Create the shaders
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Read the Vertex Shader code from the file
		std::string vertexShaderCode;
		std::ifstream vertexShaderStream(vertex_path.c_str(), std::ios::in);
		if (vertexShaderStream.is_open()) {
			std::stringstream sstr;
			sstr << vertexShaderStream.rdbuf();
			vertexShaderCode = sstr.str();
			vertexShaderStream.close();
		}
		else {
			printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_path.c_str());
			getchar();
			return;
		}

		// Read the Fragment Shader code from the file
		std::string fragmentShaderCode;
		std::ifstream fragmentShaderStream(fragment_path.c_str(), std::ios::in);
		if (fragmentShaderStream.is_open()) {
			std::stringstream sstr;
			sstr << fragmentShaderStream.rdbuf();
			fragmentShaderCode = sstr.str();
			fragmentShaderStream.close();
		}

		GLint Result = GL_FALSE;
		int InfoLogLength;

		// Compile Vertex Shader
		printf("Compiling shader : %s\n", vertex_path.c_str());
		char const* VertexSourcePointer = vertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		// Check Vertex Shader
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			printf("%s\n", &VertexShaderErrorMessage[0]);
		}

		// Compile Fragment Shader
		printf("Compiling shader : %s\n", fragment_path.c_str());
		char const* FragmentSourcePointer = fragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		// Check Fragment Shader
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			printf("%s\n", &FragmentShaderErrorMessage[0]);
		}

		// Link the program
		printf("Linking program\n");
		m_ShaderProgram = glCreateProgram();
		glAttachShader(m_ShaderProgram, VertexShaderID);
		glAttachShader(m_ShaderProgram, FragmentShaderID);
		glLinkProgram(m_ShaderProgram);

		// Check the program
		glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &Result);
		glGetProgramiv(m_ShaderProgram, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(m_ShaderProgram, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			printf("%s\n", &ProgramErrorMessage[0]);
		}

		glDetachShader(m_ShaderProgram, VertexShaderID);
		glDetachShader(m_ShaderProgram, FragmentShaderID);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderProgram);
	}

	GLuint Shader::getProgram()
	{
		return m_ShaderProgram;
	}

	void Shader::enable()
	{
		glUseProgram(m_ShaderProgram);
	}

	void Shader::disable()
	{
		glUseProgram(0);
	}
}