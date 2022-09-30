#define KILN_IMPL_SHADER
#include <string>
#include <string_view>
#include <fstream>
#include <sstream>
#include "shader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "opengl.hpp"
#include "log.hpp"
namespace life
{



shader::shader(const char* file_path)
{
	read_file(file_path);
	if (!compile())
		LOG_INFO("shader [{}] compiled successfuly.", file_path);
	else
		LOG_ERROR("shader [{}] failed to compile.", file_path);
}

shader::shader(std::string& vertex_data, std::string& fragment_data)
{
	this->vertex_data = vertex_data;
	this->fragment_data = fragment_data;
	if (!compile())
		LOG_INFO("shader compiled successfuly.");
	else
		LOG_ERROR("shader failed to compile.");

}


shader::~shader()
{
	glDeleteShader(vertex_id);
	glDeleteShader(fragment_id);
}

int shader::compile()
{
	int success = 0;
	vertex_id = glCreateShader(GL_VERTEX_SHADER);
	const char* src = vertex_data.c_str();
	glShaderSource(vertex_id, 1, &src, nullptr);
	glCompileShader(vertex_id);

	glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char* str = new char[1024];
		glGetShaderInfoLog(vertex_id, 1024, nullptr, str);
		LOG_ERROR("error: failed to compile vertex shader.");
		LOG_ERROR("{}", str);
		return SHADER_VERTEX_ERROR;
	}


	src = fragment_data.c_str();
	fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_id, 1, &src, nullptr);
	glCompileShader(fragment_id);

	glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char* str = new char[1024];
		glGetShaderInfoLog(fragment_id, 1024, nullptr, str);
		LOG_ERROR("error: failed to compile fragment shader.");
		LOG_ERROR("{}", str);
		return SHADER_FRAGMENT_ERROR;
	}


	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_id);
	glAttachShader(program_id, fragment_id);
	glLinkProgram(program_id);
	glGetShaderiv(program_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		char* str = new char[1024];
		glGetShaderInfoLog(vertex_id, 1024, nullptr, str);
		LOG_ERROR("error: failed to link shader.");
		LOG_ERROR("{}", str);
		return SHADER_LINK_ERROR;
	}

	return SHADER_SUCCESS;
}

void shader::read_file(const char* file_path)
{
	std::ifstream instream{ file_path };
	if (!instream.is_open())
	{
		LOG_ERROR("Failed to open file: {}", file_path);
		return;
	}
	std::stringstream raw_data;
	raw_data << instream.rdbuf();

	LOG_INFO("Texture data: {}", raw_data.str());

	const std::string& str = raw_data.str();

	std::size_t vertex_pos = str.find("#type vertex");
	std::size_t fragment_pos = str.find("#type fragment");

	LOG_RAW("Vertex Pos: {}\nFragment pos: {}\n", vertex_pos, fragment_pos);
	if (fragment_pos != std::string::npos)
	{
		if (vertex_pos != std::string::npos)
		{
			fragment_data = fragment_pos > vertex_pos ? str.substr(fragment_pos + 14, str.size()) : str.substr(fragment_pos + 14, vertex_pos);
			vertex_data = fragment_pos < vertex_pos ? str.substr(vertex_pos + 13, str.size()) : str.substr(vertex_pos + 13, fragment_pos - 14);
		}
		else
		{
			fragment_data = str.substr(15, str.size());
		}
	}
	else if (vertex_pos != std::string::npos)
	{
		vertex_data = str.substr(11, str.size());
	}
	else
	{
		LOG_ERROR("Error: file does not contain shader code, or is missing the type declaration: [#type vertex] or [#type fragment]");
	}

	LOG_ERROR("Vertex data:\n{}\n\nFragment data:\n{}", vertex_data, fragment_data);
}

void shader::bind() const
{
	glUseProgram(program_id);
}

void shader::push_mat4(std::string_view name,glm::mat4 mat4) const
{
	glUniformMatrix4fv(glGetUniformLocation(program_id, name.data()), 1, false, glm::value_ptr(mat4));

}

void shader::push_mat3(std::string_view name, glm::mat3 mat3) const
{
	glUniformMatrix3fv(glGetUniformLocation(program_id, name.data()),1,false,glm::value_ptr(mat3));
}
void shader::push_vec4(std::string_view name, glm::vec4 vec4) const
{
	glUniform4f(glGetUniformLocation(program_id, name.data()),vec4.x,vec4.y,vec4.z,vec4.w);

}
void shader::push_vec3(std::string_view name, glm::vec3 vec3) const
{
	glUniform3f(glGetUniformLocation(program_id, name.data()), vec3.x, vec3.y, vec3.z);

}
void shader::push_vec2(std::string_view name, glm::vec2 vec2) const
{
	glUniform2f(glGetUniformLocation(program_id, name.data()), vec2.x, vec2.y);

}
void shader::push_int(std::string_view name, int value) const
{
	glUniform1i(glGetUniformLocation(program_id, name.data()), value);
}
void shader::push_float(std::string_view name, float value) const
{
	glUniform1f(glGetUniformLocation(program_id, name.data()), value);

}

}