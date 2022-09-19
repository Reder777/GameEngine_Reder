#pragma once
#include "reder/core/core.h"
#include <string>

namespace reder {
	class texture {
	public:
		virtual ~texture() = default;

		virtual uint32_t getHeight() const = 0;
		virtual uint32_t getWidth() const = 0;

		virtual void bind(uint32_t slot = 0) const = 0;	
		virtual bool operator ==(const texture& other) const = 0;
		virtual void setData(void* data, uint32_t size) = 0;
	};

	class texture2D : public texture
	{
	public:
		static ref<texture2D> createTexture(const std::string& path);
		static ref<texture2D> createTexture(const uint32_t width, const uint32_t height);
	};
}