#pragma once
#include "reder/renderer/texture.h"

#include <glad/glad.h>
namespace reder {

	class openglTexture2D :public texture2D	{
	public:
		openglTexture2D(const uint32_t width, const uint32_t height);
		openglTexture2D(const std::string& path = 0);
		~openglTexture2D();

		inline virtual uint32_t getHeight() const override { return m_height; }
		inline virtual uint32_t getWidth() const override { return m_width; }

		virtual void bind(uint32_t slot = 0) const override;
		virtual bool operator ==(const texture& other) const override;
		virtual void setData(void* data, uint32_t size) override;
	private:
		uint32_t m_height, m_width;
		uint32_t m_textureId;
		GLenum m_internalFormat, m_dataFormat;
		std::string m_path;
	};
}