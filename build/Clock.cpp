#ifndef CLOCK_CPP
#define CLOCK_CPP

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <learnopengl/shader_m.h>
#include "PolygonWithTexture.cpp"
#include "CubeWithTexture.cpp"

class Clock
{
public:
	Clock(glm::vec3 position, GLuint woodTexture, GLuint faceTexture, GLuint whiteTexture)
	{
		parts = {};
		face = {};
		glm::vec3 gold(0.95f, 0.72f, 0.3f);
		glm::mat4 base = glm::translate(glm::mat4(1.0f), position);

		CubeWithTexture bottom(glm::vec3(0.8f, 0.25f, 0.5f), glm::vec3(1.0f), woodTexture);
		bottom.transformation(glm::translate(base, glm::vec3(0.0f, 0.125f, 0.0f)));
		CubeWithTexture middle(glm::vec3(0.62f, 1.4f, 0.42f), glm::vec3(1.0f), woodTexture);
		middle.transformation(glm::translate(base, glm::vec3(0.0f, 0.95f, 0.0f)));
		CubeWithTexture head(glm::vec3(0.8f, 0.75f, 0.5f), glm::vec3(1.0f), woodTexture);
		head.transformation(glm::translate(base, glm::vec3(0.0f, 2.025f, 0.0f)));
		CubeWithTexture roof(glm::vec3(0.92f, 0.08f, 0.58f), glm::vec3(1.0f), woodTexture);
		roof.transformation(glm::translate(base, glm::vec3(0.0f, 2.44f, 0.0f)));
		CubeWithTexture window(glm::vec3(0.42f, 1.1f, 0.01f), glm::vec3(0.05f, 0.04f, 0.03f), whiteTexture);
		window.transformation(glm::translate(base, glm::vec3(0.0f, 0.95f, 0.212f)));
		CubeWithTexture ring(glm::vec3(0.6f, 0.6f, 0.01f), gold, whiteTexture);
		ring.transformation(glm::translate(base, glm::vec3(0.0f, 2.025f, 0.252f)));
		parts.push_back(bottom);
		parts.push_back(middle);
		parts.push_back(head);
		parts.push_back(roof);
		parts.push_back(window);
		parts.push_back(ring);

		CubeWithTexture rod(glm::vec3(0.025f, 0.75f, 0.01f), gold, whiteTexture);
		rod.transformation(glm::translate(base, glm::vec3(0.0f, 1.075f, 0.225f)));
		CubeWithTexture ball(glm::vec3(0.16f, 0.16f, 0.02f), gold, whiteTexture);
		ball.transformation(glm::translate(base, glm::vec3(0.0f, 0.65f, 0.23f)));
		parts.push_back(rod);
		parts.push_back(ball);

		CubeWithTexture minuteHand(glm::vec3(0.018f, 0.2f, 0.006f), glm::vec3(0.05f), whiteTexture);
		minuteHand.transformation(glm::translate(base, glm::vec3(0.0f, 2.105f, 0.268f)));
		CubeWithTexture hourHand(glm::vec3(0.13f, 0.025f, 0.006f), glm::vec3(0.05f), whiteTexture);
		hourHand.transformation(glm::translate(base, glm::vec3(0.045f, 2.025f, 0.272f)));
		parts.push_back(minuteHand);
		parts.push_back(hourHand);

		std::vector<glm::vec3> faceVertices = {glm::vec3(-0.26f, -0.26f, 0.0f), glm::vec3(0.26f, -0.26f, 0.0f), glm::vec3(0.26f, 0.26f, 0.0f), glm::vec3(-0.26f, 0.26f, 0.0f)};
		std::vector<glm::vec2> faceTexCoords = {glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f)};
		PolygonWithTexture clockFace(faceVertices, faceTexCoords);
		clockFace.setTexture(faceTexture);
		clockFace.transformation(glm::translate(base, glm::vec3(0.0f, 2.025f, 0.262f)));
		face.push_back(clockFace);
	}

	void draw(Shader &shader)
	{
		for (int i = 0; i < parts.size(); i++)
			parts[i].draw(shader);
		face[0].draw(shader);
	}

private:
	std::vector<CubeWithTexture> parts;
	std::vector<PolygonWithTexture> face;
};

#endif
