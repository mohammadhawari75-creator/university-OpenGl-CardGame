#ifndef BOOKSHELF_CPP
#define BOOKSHELF_CPP

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <learnopengl/shader_m.h>
#include "CubeWithTexture.cpp"

class Bookshelf
{
public:
	Bookshelf(glm::vec3 position, GLuint woodTexture, GLuint whiteTexture)
	{
		parts = {};
		float width = 1.7f;
		float height = 2.2f;
		float depth = 0.42f;
		glm::mat4 base = glm::translate(glm::mat4(1.0f), position);

		CubeWithTexture leftSide(glm::vec3(0.06f, height, depth), glm::vec3(1.0f), woodTexture);
		leftSide.transformation(glm::translate(base, glm::vec3(-width / 2, height / 2, 0.0f)));
		CubeWithTexture rightSide(glm::vec3(0.06f, height, depth), glm::vec3(1.0f), woodTexture);
		rightSide.transformation(glm::translate(base, glm::vec3(width / 2, height / 2, 0.0f)));
		CubeWithTexture back(glm::vec3(width, height, 0.03f), glm::vec3(0.7f), woodTexture);
		back.transformation(glm::translate(base, glm::vec3(0.0f, height / 2, -depth / 2)));
		CubeWithTexture top(glm::vec3(width + 0.12f, 0.08f, depth + 0.06f), glm::vec3(1.0f), woodTexture);
		top.transformation(glm::translate(base, glm::vec3(0.0f, height, 0.0f)));
		parts.push_back(leftSide);
		parts.push_back(rightSide);
		parts.push_back(back);
		parts.push_back(top);

		std::vector<glm::vec3> colors = {glm::vec3(0.55f, 0.1f, 0.1f), glm::vec3(0.1f, 0.25f, 0.5f), glm::vec3(0.15f, 0.4f, 0.2f),
										 glm::vec3(0.6f, 0.45f, 0.2f), glm::vec3(0.35f, 0.15f, 0.4f), glm::vec3(0.75f, 0.7f, 0.6f), glm::vec3(0.3f, 0.2f, 0.1f)};
		std::vector<float> bookWidths = {0.06f, 0.08f, 0.05f, 0.09f, 0.07f, 0.05f, 0.1f, 0.06f};
		std::vector<float> bookHeights = {0.34f, 0.3f, 0.38f, 0.28f, 0.36f, 0.32f, 0.4f, 0.3f};

		int n = 0;
		for (int s = 0; s < 4; s++)
		{
			float shelfY = 0.06f + s * 0.53f;
			CubeWithTexture shelf(glm::vec3(width, 0.04f, depth), glm::vec3(1.0f), woodTexture);
			shelf.transformation(glm::translate(base, glm::vec3(0.0f, shelfY, 0.0f)));
			parts.push_back(shelf);

			float x = -width / 2 + 0.06f;
			while (x < width / 2 - 0.15f)
			{
				float w = bookWidths[n % bookWidths.size()];
				float h = bookHeights[(n + s) % bookHeights.size()];
				CubeWithTexture book(glm::vec3(w, h, 0.3f), colors[(n * 3 + s) % colors.size()], whiteTexture);
				book.transformation(glm::translate(base, glm::vec3(x + w / 2, shelfY + 0.02f + h / 2, 0.02f)));
				parts.push_back(book);
				x += w + 0.005f;
				n++;
				if (n % 9 == 0)
					x += 0.12f;
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
