#include "repch.h"
#include "openglTexture.h"
#include "stb_image.h"
#include "glad/glad.h"
#include "reder/log.h"
namespace reder {
	openglTexture2D::openglTexture2D(const std::string& path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		RE_CORE_ASSERT(data, "Failed to load image!");
		if (data == NULL)RE_CORE_INFO("open png failed!");
		RE_CORE_INFO("channel = {0}",channels);
		m_width = width;
		m_height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_textureId);
		glTextureStorage2D(m_textureId, 1, GL_RGB8, m_width, m_height);

		glTextureParameteri(m_textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		/*
		wwww                    wwww                    wwww       wwww
		  wwww                wwwwwwww                wwww         wwww
		    wwww            wwww    wwww            wwww           wwww 
			  wwww        wwww        wwww        wwww             wwww
			    wwww    wwww            wwww    wwww               wwww
				  wwwwwwww                wwwwwwww 
				    wwww                    wwww                   wwww
				     ww                      ww                    wwww

		some png photoes contains r\g\b\a 4 channels
		*/
		if (channels == 4) {
			glTextureSubImage2D(m_textureId, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else if (channels == 3) {
			glTextureSubImage2D(m_textureId, 0, 0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		stbi_image_free(data);
	}

	openglTexture2D::~openglTexture2D()
	{
		glDeleteTextures(1, &m_textureId);
	}

	void openglTexture2D::bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_textureId);
	}
}