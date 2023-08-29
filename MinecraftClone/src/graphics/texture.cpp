#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Game {

	Texture::Texture(const std::string& path)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

		if (!data)
			return;
		
		m_Width = width;
		m_Height = height;
		glGenTextures(1, &m_Handle);

		glBindTexture(GL_TEXTURE_2D, m_Handle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		//Unbind the texture after configuration
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);
	}

	Texture::~Texture()
	{
		if(m_Handle != 0)
			glDeleteTextures(1, &m_Handle);
	}

	int Texture::getWidth()
	{
		return m_Width;
	}

	int Texture::getHeight()
	{
		return m_Height;
	}

	GLuint Texture::getGLHandle()
	{
		return m_Handle;
	}

	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_Handle);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}
