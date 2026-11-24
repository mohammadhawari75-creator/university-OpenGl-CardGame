#ifndef ROOM_CPP
#define ROOM_CPP

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <learnopengl/shader_m.h>
#include "PolygonWithTexture.cpp"
#include "CubeWithTexture.cpp"

class Room
{
public:
	Room(float size, float floorY, float ceilingY, GLuint floorTexture, GLuint wallTexture, GLuint ceilingTexture, GLuint woodTexture)
	{
		surfaces = {};
		baseboards = {};
		float s = size / 2;
		float h = ceilingY - floorY;

		std::vector<glm::vec3> floorVertices = {glm::vec3(-s, floorY, s), glm::vec3(s, floorY, s), glm::vec3(s, floorY, -s), glm::vec3(-s, floorY, -s)};
		std::vector<glm::vec2> floorTexCoords = {glm::vec2(0.0f, 0.0f), glm::vec2(5.0f, 0.0f), glm::vec2(5.0f, 5.0f), glm::vec2(0.0f, 5.0f)};
		PolygonWithTexture floor(floorVertices, floorTexCoords);
		floor.setTexture(floorTexture);
		surfaces.push_back(floor);

		std::vector<glm::vec3> ceilingVertices = {glm::vec3(-s, ceilingY, -s), glm::vec3(s, ceilingY, -s), glm::vec3(s, ceilingY, s), glm::vec3(-s, ceilingY, s)};
		std::vector<glm::vec2> ceilingTexCoords = {glm::vec2(0.0f, 0.0f), glm::vec2(3.0f, 0.0f), glm::vec2(3.0f, 3.0f), glm::vec2(0.0f, 3.0f)};
		PolygonWithTexture ceiling(ceilingVertices, ceilingTexCoords, glm::vec3(0.8f));
		ceiling.setTexture(ceilingTexture);
		surfaces.push_back(ceiling);

		float u = size / 1.2f;
		float v = h / 1.2f;
		std::vector<glm::vec2> wallTexCoords = {glm::vec2(0.0f, 0.0f), glm::vec2(u, 0.0f), glm::vec2(u, v), glm::vec2(0.0f, v)};

		std::vector<glm::vec3> backWall = {glm::vec3(-s, floorY, -s), glm::vec3(s, floorY, -s), glm::vec3(s, ceilingY, -s), glm::vec3(-s, ceilingY, -s)};
		std::vector<glm::vec3> frontWall = {glm::vec3(s, floorY, s), glm::vec3(-s, floorY, s), glm::vec3(-s, ceilingY, s), glm::vec3(s, ceilingY, s)};
		std::vector<glm::vec3> leftWall = {glm::vec3(-s, floorY, s), glm::vec3(-s, floorY, -s), glm::vec3(-s, ceilingY, -s), glm::vec3(-s, ceilingY, s)};
		std::vector<glm::vec3> rightWall = {glm::vec3(s, floorY, -s), glm::vec3(s, floorY, s), glm::vec3(s, ceilingY, s), glm::vec3(s, ceilingY, -s)};

		PolygonWithTexture wall1(backWall, wallTexCoords);
		PolygonWithTexture wall2(frontWall, wallTexCoords);
		PolygonWithTexture wall3(leftWall, wallTexCoords);
		PolygonWithTexture wall4(rightWall, wallTexCoords);
		wall1.setTexture(wallTexture);
		wall2.setTexture(wallTexture);
		wall3.setTexture(wallTexture);
		wall4.setTexture(wallTexture);
		surfaces.push_back(wall1);
		surfaces.push_back(wall2);
		surfaces.push_back(wall3);
		surfaces.push_back(wall4);

		CubeWithTexture board1(glm::vec3(size, 0.18f, 0.04f), glm::vec3(1.0f), woodTexture);
		board1.transformation(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, floorY + 0.09f, -s + 0.02f)));
		CubeWithTexture board2(glm::vec3(size, 0.18f, 0.04f), glm::vec3(1.0f), woodTexture);
		board2.transformation(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, floorY + 0.09f, s - 0.02f)));
		CubeWithTexture board3(glm::vec3(0.04f, 0.18f, size), glm::vec3(1.0f), woodTexture);
		board3.transformation(glm::translate(glm::mat4(1.0f), glm::vec3(-s + 0.02f, floorY + 0.09f, 0.0f)));
		CubeWithTexture board4(glm::vec3(0.04f, 0.18f, size), glm::vec3(1.0f), woodTexture);
		board4.transformation(glm::translate(glm::mat4(1.0f), glm::vec3(s - 0.02f, floorY + 0.09f, 0.0f)));
		baseboards.push_back(board1);
		baseboards.push_back(board2);
		baseboards.push_back(board3);
		baseboards.push_back(board4);
	}

	void draw(Shader &shader)
	{
		for (int i = 0; i < surfaces.size(); i++)
			surfaces[i].draw(shader);
		for (int i = 0; i < baseboards.size(); i++)
			baseboards[i].draw(shader);
	}

private:
	std::vector<PolygonWithTexture> surfaces;
	std::vector<CubeWithTexture> baseboards;
};

#endif
