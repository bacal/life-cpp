#pragma once
#include <glm/glm.hpp>
#define SHADER_SUCCESS 0
#define SHADER_VERTEX_ERROR (1<<0)
#define SHADER_FRAGMENT_ERROR (1<<1)
#define SHADER_LINK_ERROR (1<<2)
namespace life
{
class shader
{
private:
	std::string vertex_data = "";
	std::string fragment_data = "";

	unsigned int vertex_id;
	unsigned int fragment_id;
	unsigned int program_id;
	void read_file(const char* file_path);
	int compile();
public:
	shader(std::string& vertex_data, std::string& fragment_data);
	shader(const char* file_path);
	~shader();
	void push_mat4(std::string_view name, glm::mat4 mat4) const;
	void push_mat3(std::string_view name, glm::mat3 mat3) const;
	void push_vec4(std::string_view name, glm::vec4 vec4) const;
	void push_vec3(std::string_view name, glm::vec3 vec3) const;
	void push_vec2(std::string_view name, glm::vec2 vec2) const;
	void push_int(std::string_view name, int value) const;
	void push_float(std::string_view name, float value) const;
	void bind() const;

};
}