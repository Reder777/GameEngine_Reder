#pragma once
#include "reder/renderer/texture.h"


namespace reder {

	class openglTexture2D :public texture2D	{
	public:
		openglTexture2D(const std::string& path = 0);
		~openglTexture2D();

		inline virtual uint32_t getHeight() const override { return m_height; }
		inline virtual uint32_t getWidth() const override { return m_width; }

		virtual void bind(uint32_t slot = 0) const override;
	private:
		uint32_t m_height, m_width;
		uint32_t m_textureId;
		std::string m_path;
	};
}