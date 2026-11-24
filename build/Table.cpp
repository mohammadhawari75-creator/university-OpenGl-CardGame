#ifndef TABLE_CPP
#define TABLE_CPP

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <learnopengl/shader_m.h>
#include "CubeWithTexture.cpp"

class Table
{
public:
	Table(float floorY, float opponentZ, float playZ, float deckZ, std::vector<float> slotsX,
		  GLuint woodTexture, GLuint darkWoodTexture, GLuint feltTexture, GLuint whiteTexture)
	{
		parts = {};

		CubeWithTexture top(glm::vec3(4.4f, 0.1f, 3.4f), glm::vec3(1.0f), woodTexture);
		top.transformation(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.05f, 0.0f)));
		parts.push_back(top);

		CubeWithTexture edge(glm::vec3(4.5f, 0.06f, 3.5f), glm::vec3(1.0f), darkWoodTexture);
		edge.transformation(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.11f, 0.0f)));
		parts.push_back(edge);

		float legHeight = -floorY - 0.14f;
		std::vector<glm::vec3> legPositions = {glm::vec3(-1.95f, 0.0f, -1.45f), glm::vec3(1.95f, 0.0f, -1.45f), glm::vec3(-1.95f, 0.0f, 1.45f), glm::vec3(1.95f, 0.0f, 1.45f)};
		for (int i = 0; i < 4; i++)
		{
			CubeWithTexture leg(glm::vec3(0.16f, legHeight, 0.16f), glm::vec3(1.0f), darkWoodTexture);
			legPositions[i].y = floorY + legHeight / 2;
			leg.transformation(glm::translate(glm::mat4(1.0f), legPositions[i]));
			parts.push_back(leg);
		}

		std::vector<float> zonesZ = {opponentZ, playZ, deckZ};
		std::vector<glm::vec3> zonesColor = {glm::vec3(0.45f, 0.13f, 0.12f), glm::vec3(0.38f, 0.28f, 0.18f), glm::vec3(0.14f, 0.32f, 0.18f)};
		for (int i = 0; i < 3; i++)
		{
			CubeWithTexture zone(glm::vec3(3.8f, 0.006f, 0.9f), zonesColor[i], feltTexture);
			zone.transformation(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.003f, zonesZ[i])));
			parts.push_back(zone);

			for (int j = 0; j < slotsX.size(); j++)
			{
				CubeWithTexture slot(glm::vec3(0.51f, 0.002f, 0.66f), glm::vec3(0.08f, 0.06f, 0.04f), whiteTexture);
				slot.transformation(glm::translate(glm::mat4(1.0f), glm::vec3(slotsX[j], 0.0065f, zonesZ[i])));
				parts.push_back(slot);
			}
		}
	}

	void draw(Shader &shader)
	{
		for (int i = 0; i < parts.size(); i++)
			parts[i].draw(shader);
	}

private:
	std::vector<CubeWithTexture> parts;
};

#endif
