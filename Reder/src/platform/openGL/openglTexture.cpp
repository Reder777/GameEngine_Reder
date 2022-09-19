#include "repch.h"
#include "openglTexture.h"
#include "stb_image.h"
#include "glad/glad.h"
#include "reder/core/log.h"
namespace reder {
	openglTexture2D::openglTexture2D(const uint32_t width, const uint32_t height)
		: m_width(width), m_height(height)
	{

		m_internalFormat = GL_RGBA8;
		m_dataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_textureId);
		glTextureStorage2D(m_textureId, 1, m_internalFormat, m_width, m_height);

		glTextureParameteri(m_textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_textureId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_textureId, GL_TEXTURE_WRAP_T, GL_REPEAT);

	}

	openglTexture2D::openglTexture2D(const std::string& path)
		:m_path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		RE_CORE_ASSERT(data, "Failed to load image!");
		if (data == NULL)RE_CORE_INFO("open png failed!");
		RE_CORE_INFO("channel = {0}",channels);
		m_width = width;
		m_height = height;
		/*
		some png photoes contains r\g\b\a 4 channels
		*/
		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		m_internalFormat = internalFormat;
		m_dataFormat = dataFormat;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_textureId);
		RE_CORE_INFO("texture {0}",m_textureId);
		glTextureStorage2D(m_textureId, 1, internalFormat, m_width, m_height);

		glTextureParameteri(m_textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_textureId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_textureId, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTextureSubImage2D(m_textureId, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, data);
	
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
	bool openglTexture2D::operator==(const texture& other) const
	{
		return m_textureId==((openglTexture2D&)other).m_textureId;
	}

	void openglTexture2D::setData(void* data, uint32_t size)
	{
		uint32_t bpp = m_dataFormat == GL_RGBA ? 4 : 3;
		RE_CORE_ASSERT(size == m_width * m_height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_textureId, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
	}

}