#pragma once

#include "reder/core/core.h"

namespace reder {
	class DLL_API shader {
	public:
		shader() {};
		~shader() {};

		virtual void bind() const =0;
		virtual void unbind() const =0;
		virtual std::string getName()const = 0;

		static ref<shader> createShader(const std::string& name,const std::string& vertexSource, const std::string& fragmentSource);
		static ref<shader> createShader(const std::string& name,const std::string& filePath);
		static ref<shader> createShader(const std::string& filePath);
	private:
	};

	class DLL_API shaderLibrary {
	public:
		void addShader(const ref<shader>& shader);
		void addShader(const std::string& name, const ref<shader>& shader);

		ref<shader> loadShader(const std::string& filePath);
		ref<shader> loadShader(const std::string& name,const std::string& filePath);
		ref<shader> getByName(const std::string& name) const;
	private:
		const std::string pathToName(const std::string& filePath) const;
		std::unordered_map<std::string, ref<shader>> m_shaderLibrary;
	};


}