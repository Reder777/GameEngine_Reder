#pragma once

#include "reder/core/core.h"
#include <glm/glm.hpp>

namespace reder {
	class DLL_API shader {
	public:
		shader() {};
		~shader() {};

		virtual void bind() const =0;
		virtual void unbind() const =0;
		virtual std::string getName()const = 0;

		/*
		shader create functions
		1-------- by vertex and fragment source
		2-------- by file with name
		3-------- by file without name
		*/
		static ref<shader> createShader(const std::string& name,const std::string& vertexSource, const std::string& fragmentSource);
		static ref<shader> createShader(const std::string& name,const std::string& filePath);
		static ref<shader> createShader(const std::string& filePath);


		/*
		upload data to shader
		*/
		virtual void setInt(const std::string& name, const int value) = 0;
		virtual void setFloat(const std::string& name, const float value) = 0;
		virtual void setFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void setFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void setFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void setMat3(const std::string& name, const glm::mat3& value) = 0;
		virtual void setMat4(const std::string& name, const glm::mat4& value) = 0;
		virtual void setIntArray(const std::string& name, int* value,uint32_t count) = 0;
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