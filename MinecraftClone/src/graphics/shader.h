#pragma once
#include <gl/glew.h>
#include <string>

namespace Game {
	class Shader {
	public:
		Shader(const std::string& vertex_path, const std::string& fragment_path);
		~Shader();

		GLuint getProgram();

		void enable();
		void disable();

	private:
		GLuint m_ShaderProgram = 0;
	};
}