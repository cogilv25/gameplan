#pragma once
#include <chrono>
#include <random>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "utilities.hpp"

extern std::vector<glm::vec4> defaultPalette;

class DanceFloor
{
	//DanceFloor properties
	unsigned int _width;
	unsigned int _height;
	std::vector<glm::vec4> _palette;
	std::chrono::milliseconds _period;

	//Internal variables
	//Timing + RNG
	std::chrono::steady_clock::time_point _lastUpdate;
	std::mt19937 * rng;
	std::uniform_int_distribution<int>* dist;

	//OpenGL buffers
	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;

	//Drawing data
	struct Vector
	{
		glm::vec3 position;
		glm::vec4 colour;
	};

	Vector * _vboData;
public:
	DanceFloor(unsigned int width = 10, unsigned int height = 10, std::chrono::milliseconds frequencyPeriod = std::chrono::milliseconds(1000),
		std::vector<glm::vec4> palette = defaultPalette);
	~DanceFloor();
	void draw();
	void update();
};

