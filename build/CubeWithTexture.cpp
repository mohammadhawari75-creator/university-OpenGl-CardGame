#ifndef CUBE_WITH_TEXTURE_CPP
#define CUBE_WITH_TEXTURE_CPP

#include <vector>
#include <glm/glm.hpp>
#include <learnopengl/shader_m.h>
#include "PolygonWithTexture.cpp"

class CubeWithTexture
{
public:
	CubeWithTexture(glm::vec3 size, glm::vec3 color, GLuint texture)
	{
		this->size = size;
		this->color = color;
		this->texture = texture;
		faces = {};
		model = glm::mat4(1.0f);

		float x = size.x / 2;
		float y = size.y / 2;
		float z = size.z / 2;

		std::vector<glm::vec2> texCoords = {glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f)};

		std::vector<glm::vec3> vertices1 = {glm::vec3(-x, -y, z), glm::vec3(x, -y, z), glm::vec3(x, y, z), glm::vec3(-x, y, z)};
		std::vector<glm::vec3> vertices2 = {glm::vec3(x, -y, -z), glm::vec3(-x, -y, -z), glm::vec3(-x, y, -z), glm::vec3(x, y, -z)};
		std::vector<glm::vec3> vertices3 = {glm::vec3(x, -y, z), glm::vec3(x, -y, -z), glm::vec3(x, y, -z), glm::vec3(x, y, z)};
		std::vector<glm::vec3> vertices4 = {glm::vec3(-x, -y, -z), glm::vec3(-x, -y, z), glm::vec3(-x, y, z), glm::vec3(-x, y, -z)};
		std::vector<glm::vec3> vertices5 = {glm::vec3(-x, y, z), glm::vec3(x, y, z), glm::vec3(x, y, -z), glm::vec3(-x, y, -z)};
		std::vector<glm::vec3> vertices6 = {glm::vec3(-x, -y, -z), glm::vec3(x, -y, -z), glm::vec3(x, -y, z), glm::vec3(-x, -y, z)};

		faces.push_back(PolygonWithTexture(vertices1, texCoords, color));
		faces.push_back(PolygonWithTexture(vertices2, texCoords, color));
		faces.push_back(PolygonWithTexture(vertices3, texCoords, color));
		faces.push_back(PolygonWithTexture(vertices4, texCoords, color));
		faces.push_back(PolygonWithTexture(vertices5, texCoords, color));
		faces.push_back(PolygonWithTexture(vertices6, texCoords, color));

		for (int i = 0; i < faces.size(); i++)
			faces[i].setTexture(this->texture);
	}

	void transformation(glm::mat4 t)
	{
		model = t;
	}

	void draw(Shader &shader)
	{
		for (int i = 0; i < faces.size(); i++)
		{
			faces[i].transformation(model);
			faces[i].draw(shader);
		}
	}

private:
	glm::vec3 size;
	glm::vec3 color;
	GLuint texture;
	glm::mat4 model;
	std::vector<PolygonWithTexture> faces;
};

#endif
