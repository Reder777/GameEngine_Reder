#pragma once
#include "reder/core.h"

namespace reder {

	class DLL_API timeStamp {

	public:
		timeStamp(float time=0.0f) { m_timeStamp = time; }

		inline float getSeconds() const{ return m_timeStamp; }
		inline float getMillSeconds() const { return m_timeStamp * 1000.0f; }

		operator float() const { return m_timeStamp; }
	private:
		float m_timeStamp = 0.0f;
	};
}