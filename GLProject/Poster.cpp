#ifndef POSTER_CPP
#define POSTER_CPP

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <learnopengl/shader_m.h>
#include "PolygonWithTexture.cpp"
#include "CubeWithTexture.cpp"

class Poster
{
public:
	Poster(glm::vec3 position, GLuint posterTexture, GLuint whiteTexture)
	{
		width = 1.2f;
		height = 1.6f;
		pieces = {};
		tape = {};

		std::vector<glm::vec3> split = {
			glm::vec3(-0.07f, 0.8f, 0.0f), glm::vec3(-0.04f, 0.68f, 0.0f), glm::vec3(-0.09f, 0.55f, 0.0f), glm::vec3(-0.03f, 0.42f, 0.0f),
			glm::vec3(-0.06f, 0.3f, 0.0f), glm::vec3(0.0f, 0.18f, 0.0f), glm::vec3(-0.04f, 0.05f, 0.0f), glm::vec3(0.03f, -0.08f, 0.0f),
			glm::vec3(0.0f, -0.2f, 0.0f), glm::vec3(0.06f, -0.33f, 0.0f), glm::vec3(0.02f, -0.45f, 0.0f), glm::vec3(0.08f, -0.58f, 0.0f),
			glm::vec3(0.04f, -0.7f, 0.0f), glm::vec3(0.1f, -0.8f, 0.0f)};

		std::vector<glm::vec3> corner = {
			glm::vec3(0.6f, 0.35f, 0.0f), glm::vec3(0.55f, 0.42f, 0.0f), glm::vec3(0.53f, 0.5f, 0.0f), glm::vec3(0.46f, 0.53f, 0.0f),
			glm::vec3(0.44f, 0.61f, 0.0f), glm::vec3(0.36f, 0.63f, 0.0f), glm::vec3(0.33f, 0.7f, 0.0f), glm::vec3(0.25f, 0.72f, 0.0f),
			glm::vec3(0.22f, 0.78f, 0.0f), glm::vec3(0.15f, 0.8f, 0.0f)};

		std::vector<glm::vec3> left = {glm::vec3(-0.6f, -0.8f, 0.0f)};
		std::vector<glm::vec3> leftPaper = {glm::vec3(-0.6f, -0.8f, 0.0f)};
		for (int i = split.size() - 1; i >= 0; i--)
		{
			left.push_back(split[i]);
			leftPaper.push_back(split[i] + glm::vec3(0.02f, 0.0f, 0.0f));
		}
		left.push_back(glm::vec3(-0.6f, 0.8f, 0.0f));
		leftPaper.push_back(glm::vec3(-0.6f, 0.8f, 0.0f));

		std::vector<glm::vec3> right = {glm::vec3(0.1f, -0.8f, 0.0f), glm::vec3(0.6f, -0.8f, 0.0f)};
		std::vector<glm::vec3> rightPaper = {glm::vec3(0.1f, -0.8f, 0.0f), glm::vec3(0.6f, -0.8f, 0.0f)};
		for (int i = 0; i < corner.size(); i++)
		{
			right.push_back(corner[i]);
			rightPaper.push_back(corner[i] + glm::vec3(0.015f, 0.015f, 0.0f));
		}
		for (int i = 0; i < split.size() - 1; i++)
		{
			right.push_back(split[i]);
			rightPaper.push_back(split[i] - glm::vec3(0.02f, 0.0f, 0.0f));
		}

		glm::vec3 paperColor(0.85f, 0.82f, 0.75f);
		PolygonWithTexture leftPaperPiece = makePiece(leftPaper, glm::vec3(-0.27f, 0.0f, 0.0f), whiteTexture, paperColor);
		PolygonWithTexture leftPiece = makePiece(left, glm::vec3(-0.27f, 0.0f, 0.0f), posterTexture, glm::vec3(1.0f));
		PolygonWithTexture rightPaperPiece = makePiece(rightPaper, glm::vec3(0.27f, 0.0f, 0.0f), whiteTexture, paperColor);
		PolygonWithTexture rightPiece = makePiece(right, glm::vec3(0.27f, 0.0f, 0.0f), posterTexture, glm::vec3(1.0f));

		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
		leftPaperPiece.transformation(model);
		leftPiece.transformation(glm::translate(model, glm::vec3(0.0f, 0.0f, 0.004f)));

		glm::vec3 tapePoint(0.14f, 0.77f, 0.0f);
		glm::mat4 rightModel = glm::translate(model, tapePoint);
		rightModel = glm::rotate(rightModel, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		rightModel = glm::translate(rightModel, -tapePoint);
		rightModel = glm::translate(rightModel, glm::vec3(0.03f, 0.0f, 0.0f));
		rightPaperPiece.transformation(rightModel);
		rightPiece.transformation(glm::translate(rightModel, glm::vec3(0.0f, 0.0f, 0.004f)));

		pieces.push_back(leftPaperPiece);
		pieces.push_back(leftPiece);
		pieces.push_back(rightPaperPiece);
		pieces.push_back(rightPiece);

		glm::vec3 tapeColor(0.85f, 0.8f, 0.6f);
		std::vector<glm::vec3> tapePositions = {glm::vec3(-0.6f, 0.8f, 0.006f), glm::vec3(-0.6f, -0.8f, 0.006f), tapePoint + glm::vec3(0.0f, 0.0f, 0.006f)};
		std::vector<float> tapeAngles = {35.0f, -35.0f, -8.0f};
		for (int i = 0; i < 3; i++)
		{
			CubeWithTexture t(glm::vec3(0.18f, 0.06f, 0.002f), tapeColor, whiteTexture);
			glm::mat4 m = glm::translate(model, tapePositions[i]);
			m = glm::rotate(m, glm::radians(tapeAngles[i]), glm::vec3(0.0f, 0.0f, 1.0f));
			t.transformation(m);
			tape.push_back(t);
		}
	}

	void draw(Shader &shader)
	{
		for (int i = 0; i < pieces.size(); i++)
			pieces[i].draw(shader);
		for (int i = 0; i < tape.size(); i++)
			tape[i].draw(shader);
	}

private:
	float width;
	float height;
	std::vector<PolygonWithTexture> pieces;
	std::vector<CubeWithTexture> tape;

	PolygonWithTexture makePiece(std::vector<glm::vec3> points, glm::vec3 center, GLuint texture, glm::vec3 color)
	{
		std::vector<glm::vec3> vertices = {center};
		for (int i = 0; i < points.size(); i++)
			vertices.push_back(points[i]);
		vertices.push_back(points[0]);

		std::vector<glm::vec2> texCoords = {};
		for (int i = 0; i < vertices.size(); i++)
			texCoords.push_back(glm::vec2(vertices[i].x / width + 0.5f, vertices[i].y / height + 0.5f));

		PolygonWithTexture piece(vertices, texCoords, color);
		piece.setTexture(texture);
		return piece;
	}
};

#endif
