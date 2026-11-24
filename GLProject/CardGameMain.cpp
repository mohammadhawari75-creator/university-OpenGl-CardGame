#include "libs/glad_loader_docs.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "PolygonWithTexture.cpp"
#include "CubeWithTexture.cpp"
#include "Card.cpp"
#include "Room.cpp"
#include "Table.cpp"
#include "Clock.cpp"
#include "Bookshelf.cpp"
#include "Chest.cpp"
#include "Poster.cpp"
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include "stb_image.h"

using namespace std;
using namespace glm;

int SCR_WIDTH = 1280;
int SCR_HEIGHT = 720;

Camera camera(vec3(0.0f, 4.4f, 0.0f));
int cameraState = 1;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float floorY = -0.95f;
float ceilingY = 4.8f;
float opponentZ = -1.05f;
float playZ = 0.0f;
float deckZ = 1.05f;
vector<float> slotsX = {-1.2f, -0.6f, 0.0f, 0.6f, 1.2f};

vector<Card> cards = {};
vector<int> deck = {};
int playedCount = 0;
bool gPressed = false;

void processInput(GLFWwindow *window, float time);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void setCameraState(int state, float time);
void playRandomCard(float time);

unsigned int loadTexture(const char *path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture " << path << std::endl;
	stbi_image_free(data);

	return texture;
}

int main()
{
	glfwInit();
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Card Game", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_DEPTH_TEST);

	stbi_set_flip_vertically_on_load(true);

	Shader ourShader("./shaders/vs/L4.vs", "./shaders/fs/L4.fs");

	srand(time(0));

	unsigned int whiteTexture = loadTexture("./textures/white.jpg");
	unsigned int tableTexture = loadTexture("./textures/table_wood.jpg");
	unsigned int floorTexture = loadTexture("./textures/floor_wood.jpg");
	unsigned int darkWoodTexture = loadTexture("./textures/dark_wood.jpg");
	unsigned int wallTexture = loadTexture("./textures/wallpaper.jpg");
	unsigned int ceilingTexture = loadTexture("./textures/plaster.jpg");
	unsigned int feltTexture = loadTexture("./textures/felt.jpg");
	unsigned int clockTexture = loadTexture("./textures/clock_face.jpg");
	unsigned int posterTexture = loadTexture("./textures/poster.jpg");
	unsigned int cardBackTexture = loadTexture("./textures/card_back.jpg");
	unsigned int cardTextures[5];
	cardTextures[0] = loadTexture("./textures/card1.jpg");
	cardTextures[1] = loadTexture("./textures/card2.jpg");
	cardTextures[2] = loadTexture("./textures/card3.jpg");
	cardTextures[3] = loadTexture("./textures/card4.jpg");
	cardTextures[4] = loadTexture("./textures/card5.jpg");

	Room room(10.0f, floorY, ceilingY, floorTexture, wallTexture, ceilingTexture, darkWoodTexture);
	Table table(floorY, opponentZ, playZ, deckZ, slotsX, tableTexture, darkWoodTexture, feltTexture, whiteTexture);
	Clock clock(vec3(-3.6f, floorY, -4.65f), darkWoodTexture, clockTexture, whiteTexture);
	Bookshelf bookshelf(vec3(3.4f, floorY, -4.75f), darkWoodTexture, whiteTexture);
	Chest chest(vec3(1.7f, floorY, -4.4f), darkWoodTexture, whiteTexture);
	Poster poster(vec3(0.0f, 0.8f, -4.99f), posterTexture, whiteTexture);

	for (int i = 0; i < 5; i++)
	{
		Card card(cardTextures[i], cardBackTexture, vec3(slotsX[i], 0.012f, deckZ));
		cards.push_back(card);
		deck.push_back(i);
	}

	setCameraState(1, 0.0f);
	cout << "1: top view   2: player view   G: play a card" << endl;

	ourShader.use();

	mat4 projection = mat4(1.0f);
	projection = perspective(radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.05f, 100.0f);
	ourShader.setMat4("projection", projection);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		float time = (float)glfwGetTime();

		processInput(window, time);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mat4 view = mat4(1.0f);
		view = camera.GetViewMatrix();
		ourShader.setMat4("view", view);

		room.draw(ourShader);
		table.draw(ourShader);
		clock.draw(ourShader);
		bookshelf.draw(ourShader);
		chest.draw(ourShader);
		poster.draw(ourShader);
		for (int i = 0; i < cards.size(); i++)
			cards[i].draw(ourShader, time);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void setCameraState(int state, float time)
{
	cameraState = state;
	if (state == 1)
	{
		camera.Position = vec3(0.0f, 4.4f, 0.0f);
		camera.Yaw = -90.0f;
		camera.Pitch = -89.0f;
	}
	else
	{
		camera.Position = vec3(0.0f, 1.75f, 3.2f);
		camera.Yaw = -90.0f;
		camera.Pitch = -22.0f;
	}
	camera.ProcessMouseMovement(0.0f, 0.0f);

	for (int i = 0; i < cards.size(); i++)
	{
		if (state == 1)
			cards[i].setAngle(0.0f, time);
		else
			cards[i].setAngle(80.0f, time);
	}
}

void playRandomCard(float time)
{
	if (deck.size() == 0)
	{
		cout << "deck is empty" << endl;
		return;
	}

	int k = rand() % deck.size();
	int index = deck[k];
	deck.erase(deck.begin() + k);

	cards[index].inDeck = false;
	cards[index].moveTo(vec3(slotsX[playedCount], 0.012f, playZ), time);
	playedCount++;
	cout << "played card " << index + 1 << endl;
}

void processInput(GLFWwindow *window, float time)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && cameraState != 1)
		setCameraState(1, time);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && cameraState != 2)
		setCameraState(2, time);

	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && !gPressed)
	{
		playRandomCard(time);
		gPressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_RELEASE)
		gPressed = false;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}
