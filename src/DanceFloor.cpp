#include "DanceFloor.hpp"

std::vector<glm::vec4> defaultPalette
{
	{0.8f,0.8f,0.8f,1.0f},
	{0.8f,0.0f,0.0f,1.0f},
	{0.0f,0.0f,0.8f,1.0f},
	{0.0f,0.8f,0.0f,1.0f},
	{0.8f,0.8f,0.0f,1.0f},
	{0.8f,0.0f,0.8f,1.0f}
};

DanceFloor::DanceFloor(unsigned int width, unsigned int height, std::chrono::milliseconds period, std::vector<glm::vec4> palette)
	: _width(width), _height(height), _period(period), _palette(palette)
{
	_vboData = new Vector[_width * height * 4];
	
	// Create RNG for range 0.0f - 1.0f
	std::random_device rd;
	rng = new std::mt19937(rd());
	dist = new std::uniform_int_distribution<int>(0,_palette.size()-1);

	//Ekk
	float tileWidth = 2.0f / (float)_width;
	float tileHeight = 2.0f / (float)_height;
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			
			float x = i * tileWidth - 1.0f;
			float y = j * tileHeight - 1.0f;
			int n = (j * _width + i)*4;
			glm::vec4 col = _palette[dist->operator()(*rng)];
			_vboData[n].position = { x, y, 0.0f };
			_vboData[n].colour = col;
			_vboData[n + 1].position = { x + tileWidth, y, 0.0f };
			_vboData[n + 1].colour = col;
			_vboData[n + 2].position = { x + tileWidth, y + tileHeight, 0.0f };
			_vboData[n + 2].colour = col;
			_vboData[n + 3].position = { x, y + tileHeight, 0.0f };
			_vboData[n + 3].colour = col;
		}
	}

	//Create Vertex Array, Vertex Buffer and Index Buffer
	GL(glGenVertexArrays(1, &vao));
	GL(glBindVertexArray(vao));

	GL(glGenBuffers(1, &vbo));
	GL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GL(glBufferData(GL_ARRAY_BUFFER, sizeof(Vector) * width*height*4, _vboData, GL_DYNAMIC_DRAW));

	GL(glEnableVertexAttribArray(0));
	GL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector), (void*)0));
	GL(glEnableVertexAttribArray(1));
	GL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vector), (void*)sizeof(glm::vec3)));

	unsigned int* indices_data = new unsigned int[width*height * 6];

	int offset = 0;
	for (int i = 0; i < width * height*4; i += 4)
	{
		indices_data[offset] = i + 0;
		indices_data[offset + 1] = i + 1;
		indices_data[offset + 2] = i + 2;
		indices_data[offset + 3] = i + 2;
		indices_data[offset + 4] = i + 3;
		indices_data[offset + 5] = i + 0;

		offset += 6;
	}

	GL(glGenBuffers(1, &ibo));
	GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * width * height * 6, indices_data, GL_DYNAMIC_DRAW));

	delete[] indices_data;

	_lastUpdate = std::chrono::steady_clock::now();

}

DanceFloor::~DanceFloor()
{
	delete[] _vboData;
	delete dist;
	delete rng;
}

void DanceFloor::draw()
{
	GL(glBindVertexArray(vao));

	GL(glDrawElements(GL_TRIANGLES, _width*_height * 6, GL_UNSIGNED_INT, (void*)0));

}

void DanceFloor::update()
{
	if (_lastUpdate + _period > std::chrono::steady_clock::now())
		return;
	
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			glm::vec4 col = _palette[dist->operator()(*rng)];;
			int n = (j * _width + i) * 4;
			_vboData[n].colour = col;
			_vboData[n + 1].colour = col;
			_vboData[n + 2].colour = col;
			_vboData[n + 3].colour = col;

		}
	}

	GL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GL(glBufferSubData(GL_ARRAY_BUFFER, 0, _width * _height * 4 * sizeof(Vector), _vboData));

	_lastUpdate = std::chrono::steady_clock::now();
}
