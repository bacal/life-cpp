#include "grid.hpp"

namespace life{

	grid::grid(int n)
	:n{n}
	{
		data.resize(n);
		for(int i=0; i<n; i++)
		{
			data[i].resize(n);
		}
	}

	glm::vec3 grid::calculate_color(cell c) const
	{
		return glm::vec3{0,0,0};
	}

	void grid::update_cell(int r, int c, bool state, int time)
	{
		state?data[r][c].animate():data[r][c].kill(time);
	}

	std::vector<int> grid::calculate_indices() const
	{
		std::vector<int> indices;
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				// Upper Triangle
				indices.emplace_back((6*i)+j);
				indices.emplace_back((6*i)+1+j);
				indices.emplace_back(6*(i+1)+j);

				// Lower Triangle
				indices.emplace_back(6*(i+1)+j);
				indices.emplace_back((6*(i+1))+1+j);
				indices.emplace_back(j+1);
			}
		}
		return indices;
	}

	std::vector<vertex> grid::calculate_vertices(int width) const
	{
		std::vector<vertex> vertices;
		int scale = width/n;

		for (int i=0; i<n+1; i++)
		{
			for (int j=0; j<n+1; j++)
			{
				if(i == n && j==n)
				{
					vertices.push_back(vertex{glm::vec3{(i*scale),(j*scale),0.0f}, calculate_color(data[i-1][j-1])});
				}
				else if(i==n && j!=n)
				{
					vertices.push_back(vertex{glm::vec3{(i*scale),(j*scale),0.0f}, calculate_color(data[i-1][j])});
				}
				else if (j==n && i!=n)
				{
					vertices.push_back(vertex{glm::vec3{(i*scale),(j*scale),0.0f}, calculate_color(data[i][j-1])});
				}
				else
				{
					vertices.push_back(vertex{glm::vec3{(i*scale),(j*scale),0.0f}, calculate_color(data[i][j])});
				}
			}
		}
		return vertices;
	}

	void grid::draw() const
	{

	}

}