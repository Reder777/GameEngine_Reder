#pragma once
#include "reder/core.h"

namespace reder {

	enum class renderGraphicsLibrary {
		None = 0, Opengl = 1
	};

	class rendererAPI {
	public:
		inline static renderGraphicsLibrary getLibrary() {
			return library_used;
		}
	private:
		static renderGraphicsLibrary library_used;
	};
}