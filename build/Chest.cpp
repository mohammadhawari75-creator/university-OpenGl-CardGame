#ifndef CHEST_CPP
#define CHEST_CPP

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <learnopengl/shader_m.h>
#include "CubeWithTexture.cpp"

class Chest
{
public:
	Chest(glm::vec3 position, GLuint woodTexture, GLuint whiteTexture)
	{
		parts = {};
		float width = 0.95f;
		float height = 0.5f;
		float depth = 0.58f;
		glm::vec3 gold(0.95f, 0.72f, 0.3f);
		glm::mat4 base = glm::translate(glm::mat4(1.0f), position);

		CubeWithTexture box(glm::vec3(width, height, depth), glm::vec3(1.0f), woodTexture);
		box.transformation(glm::translate(base, glm::vec3(0.0f, height / 2, 0.0f)));
		parts.push_back(box);

		CubeWithTexture band1(glm::vec3(0.07f, height + 0.01f, depth + 0.02f), gold, whiteTexture);
		band1.transformation(glm::translate(base, glm::vec3(-0.32f, height / 2, 0.0f)));
		CubeWithTexture band2(glm::vec3(0.07f, height + 0.01f, depth + 0.02f), gold, whiteTexture);
		band2.transformation(glm::translate(base, glm::vec3(0.32f, height / 2, 0.0f)));
		CubeWithTexture lock(glm::vec3(0.14f, 0.16f, 0.02f), gold, whiteTexture);
		lock.transformation(glm::translate(base, glm::vec3(0.0f, height - 0.1f, depth / 2 + 0.01f)));
		parts.push_back(band1);
		parts.push_back(band2);
		parts.push_back(lock);

		glm::mat4 hinge = glm::translate(base, glm::vec3(0.0f, height, -depth / 2));
		hinge = glm::rotate(hinge, glm::radians(-70.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		CubeWithTexture lid(glm::vec3(width + 0.02f, 0.12f, depth + 0.02f), glm::vec3(1.0f), woodTexture);
		lid.transformation(glm::translate(hinge, glm::vec3(0.0f, 0.06f, depth / 2)));
		parts.push_back(lid);

		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				float x = -0.35f + i * 0.14f;
				float z = -0.2f + j * 0.13f;
				float y = height + 0.01f + ((i + j) % 3) * 0.012f;
				CubeWithTexture coin(glm::vec3(0.08f, 0.012f, 0.08f), gold, whiteTexture);
				glm::mat4 model = glm::translate(base, glm::vec3(x, y, z));
				model = glm::rotate(model, glm::radians(i * 25.0f + j * 40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				coin.transformation(model);
				parts.push_back(coin);
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
