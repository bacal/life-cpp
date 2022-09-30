#pragma once
#include "cell.hpp"
#include <vector>
#include <glm/glm.hpp>

namespace life
{
	struct vertex
	{
		glm::vec2 position;
		glm::vec3 color;
	};

	/**
	 * calculate colors will calculate based on index.
	 * when generating the vertex vector,
	 */

	class grid
	{
	 private:
		std::vector<std::vector<cell>> data;
		std::vector<glm::vec3> calculate_colors(cell c) const;
		int n;
		bool updated;
		std::vector<glm::vec2> vertices;
		std::vector<int> indices;
		void calculate_vertices(int width);
		void calculate_indices();
	 public:
		explicit grid(int n); // creates an n by n grid
		void update_cell(int r, int c, bool state, int time);
		std::vector<int> get_indices() const;
		std::vector<vertex> get_vertices() const;
	};

}