#ifndef CARD_CPP
#define CARD_CPP

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <learnopengl/shader_m.h>
#include "PolygonWithTexture.cpp"

class Card
{
public:
	bool inDeck;

	Card(GLuint frontTexture, GLuint backTexture, glm::vec3 position)
	{
		this->frontTexture = frontTexture;
		this->backTexture = backTexture;
		this->position = position;
		width = 0.45f;
		height = 0.6f;
		inDeck = true;
		faces = {};

		startPosition = position;
		targetPosition = position;
		moveStart = 0.0f;
		moving = false;

		angle = 0.0f;
		startAngle = 0.0f;
		targetAngle = 0.0f;
		angleStart = 0.0f;

		float x = width / 2;
		float z = height / 2;

		std::vector<glm::vec3> frontVertices = {glm::vec3(-x, 0.004f, z), glm::vec3(x, 0.004f, z), glm::vec3(x, 0.004f, -z), glm::vec3(-x, 0.004f, -z)};
		std::vector<glm::vec2> frontTexCoords = {glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f)};
		PolygonWithTexture front(frontVertices, frontTexCoords);
		front.setTexture(this->frontTexture);

		std::vector<glm::vec3> backVertices = {glm::vec3(-x, -0.004f, z), glm::vec3(x, -0.004f, z), glm::vec3(x, -0.004f, -z), glm::vec3(-x, -0.004f, -z)};
		std::vector<glm::vec2> backTexCoords = {glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f)};
		PolygonWithTexture back(backVertices, backTexCoords);
		back.setTexture(this->backTexture);

		faces.push_back(front);
		faces.push_back(back);
	}

	void moveTo(glm::vec3 target, float time)
	{
		startPosition = position;
		targetPosition = target;
		moveStart = time;
		moving = true;
	}

	void setAngle(float angle, float time)
	{
		startAngle = this->angle;
		targetAngle = angle;
		angleStart = time;
	}

	void draw(Shader &shader, float time)
	{
		if (moving)
		{
			float t = time - moveStart;
			if (t >= 1.0f)
			{
				t = 1.0f;
				moving = false;
			}
			position = startPosition + (targetPosition - startPosition) * t;
			position.y = startPosition.y + sin(t * 3.14159f) * 0.4f;
		}

		float t = (time - angleStart) * 2.0f;
		if (t > 1.0f)
			t = 1.0f;
		angle = startAngle + (targetAngle - startAngle) * t;

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, height / 2));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -height / 2));

		faces[0].transformation(model);
		faces[1].transformation(model);
		faces[0].draw(shader);
		faces[1].draw(shader);
	}

private:
	float width;
	float height;
	GLuint frontTexture;
	GLuint backTexture;
	std::vector<PolygonWithTexture> faces;

	glm::vec3 position;
	glm::vec3 startPosition;
	glm::vec3 targetPosition;
	float moveStart;
	bool moving;

	float angle;
	float startAngle;
	float targetAngle;
	float angleStart;
};

#endif
