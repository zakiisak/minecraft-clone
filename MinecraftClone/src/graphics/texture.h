#pragma once
#include <GL/glew.h>
#include <string>

namespace Game {
	class Texture {
	public:
		Texture(const std::string& path);
		~Texture();

		int getWidth();
		int getHeight();
		GLuint getGLHandle();

		void bind();
		void unbind();
	private:
		GLuint m_Handle = 0;
		uint8_t m_Width = 0;
		uint8_t m_Height = 0;
	};
}