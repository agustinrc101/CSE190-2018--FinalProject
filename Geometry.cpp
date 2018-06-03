#include "Geometry.h"
#include "stb_image.h"

Geometry::Geometry()
{
	initialized = false;
	transFirst = false;
	hasTexture = false;
}

Geometry::~Geometry()
{
	if (initialized)
	{
		// Delete previously generated buffers. Note that forgetting to do this can waste GPU memory in a 
		// large project! This could crash the graphics driver due to memory leaks, or slow down application performance!
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteBuffers(1, &NBO);
		if (hasTexture)
		{
			glDeleteBuffers(1, &textureID);
		}
	}
}

Geometry& Geometry::init(std::string filepath, std::string ppmpath)
{
	if (filepath.length())
	{
		initialized = true;
		toWorld = glm::mat4(1.0f);
		model = Model(filepath, ppmpath);

		//centerAndResize();
		scalePointAmount = 1;
		x = 0;
		y = 0;
		z = 0;
		totalRot = glm::mat4(1.0f);
		rotOffset = glm::mat4(1.0f);
		transFirst = false;

		return *this;
	}
}

void Geometry::update()
{
}

int Geometry::draw(glm::mat4 C, Shader* shaderProgram, int n)
{
	shaderProgram->use();
	// Now send these values to the shader program
	shaderProgram->setMat4("model", C * toWorld);
	shaderProgram->setInt("currentIndex", n);
	++n;
	model.Draw(*shaderProgram);
        return n;
}

void Geometry::addTexture(std::string file)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	int width, height, nrChannels;
	unsigned char *data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glBindVertexArray(VAO);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glGenBuffers(1, &TBO);
		glBindBuffer(GL_ARRAY_BUFFER, TBO);
		glBufferData(GL_ARRAY_BUFFER, texCoord.size() * sizeof(glm::vec3), &texCoord[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
			3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
			GL_FLOAT, // What type these components are
			GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
			sizeof(glm::vec3), // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
			(GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.
						 
		// Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Unbind the VAO now so we don't accidentally tamper with it.
		// NOTE: You must NEVER unbind the element array buffer associated with a VAO!*/
		glBindVertexArray(0);
		stbi_image_free(data);
		hasTexture = true;
	}
	else
	{
		std::cout << "Texture failed to load at path: " << file << std::endl;
		stbi_image_free(data);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

std::vector<glm::vec3>& Geometry::getVertices()
{
	return vertices;
}

std::vector<glm::vec3>& Geometry::getNormals()
{
	return normals;
}

std::vector<unsigned int>& Geometry::getIndices()
{
	return indices;
}

void Geometry::parse(const char * filepath)
{
	//TODO parse the OBJ file
	// Populate the face indices, vertices, and normals vectors with the OBJ Object data
	errno = 0;
	FILE* inFile;
	fopen_s(&inFile, filepath, "r");
	char vertexType[3] = { 0 };
	float x = 0;
	float y = 0;
	float z = 0;
	float red = 0;
	float green = 0;
	float blue = 0;
	float vertex;
	float texture;
	float normal;
	float notUsed = 0;
	std::vector<unsigned int> temp_indices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec3> temp_normals;
	std::vector<glm::vec2> temp_texCoord;

	if (inFile == NULL)
	{
		std::cerr << "Error loading file:" << filepath << std::endl;
		std::cin.ignore();
		exit(-1);
	}
	else
	{
		while (fscanf_s(inFile, "%s", vertexType) != EOF)
		{
			if (strncmp(vertexType, "vn", 2) == 0)
			{
				fscanf_s(inFile, "%f %f %f\n", &x, &y, &z);
				temp_normals.push_back(glm::vec3(x, y, z));
			}
			else if (strncmp(vertexType, "vt", 2) == 0)
			{
				fscanf_s(inFile, "%f %f\n", &x, &y);
				temp_texCoord.push_back(glm::vec2(x, y));
			}
			else if (strncmp(vertexType, "v", 1) == 0)
			{
				fscanf_s(inFile, "%f %f %f %f %f %f\n", &x, &y, &z, &red, &green, &blue);
				temp_vertices.push_back(glm::vec3(x, y, z));
			}
			else if (strncmp(vertexType, "f", 1) == 0)
			{
				for (int i = 0; i < 3; ++i)
				{
					for (int j = 0; j < 3; ++j)
					{
						fscanf_s(inFile, "/");
						if (j == 0)
						{
							if(fscanf_s(inFile, "%f", &vertex))
							{
								temp_indices.push_back(vertex - 1);
							}
						}
						else if (j == 1)
						{
							if(fscanf_s(inFile, "%f", &texture))
							{
								if (strcmp(filepath, "c:\\Users\\Wilson\\Documents\\School\\CSE167\\PA3\\CSE167StarterCode-master\\robot-parts\\head.obj") == 0)
								{
									std::cout << texture << std::endl;
								}
								tindices.push_back(texture - 1);
							}
						}
						else if (j == 2)
						{
							if(fscanf_s(inFile, "%f", &normal))
							{
								nindices.push_back(normal - 1);
							}
						}
					}
				}
				fscanf_s(inFile, "\n");
			}
			else
			{
				fscanf_s(inFile, "%*[^\n]\n");
			}
			//vertexType[1] = 0;
		}
	}
}

void Geometry::centerAndResize()
{
	int size = vertices.size();
	glm::vec3 center;
	float xMin = FLT_MAX;
	float xMax = FLT_MIN;
	float yMin = FLT_MAX;
	float yMax = FLT_MIN;
	float zMin = FLT_MAX;
	float zMax = FLT_MIN;
	float scaleDownAmount = 0;
	glm::vec4 intermVal;
	for (int i = 0; i < size; ++i)
	{
		xMin = (vertices[i].x < xMin) ? vertices[i].x : xMin;
		xMax = (vertices[i].x > xMax) ? vertices[i].x : xMax;
		yMin = (vertices[i].y < yMin) ? vertices[i].y : yMin;
		yMax = (vertices[i].y > yMax) ? vertices[i].y : yMax;
		zMin = (vertices[i].z < zMin) ? vertices[i].z : zMin;
		zMax = (vertices[i].z > zMax) ? vertices[i].z : zMax;
	}
	center = glm::vec3((xMax + xMin) / 2.0f, (yMax + yMin) / 2.0f, (zMax + zMin) / 2.0f);
	scaleDownAmount = 2 / std::max(std::max(xMax - xMin, yMax - yMin), zMax - zMin);
	for (int i = 0; i < vertices.size(); ++i)
	{
		intermVal = (glm::translate(glm::mat4(1.0f), (center * -1.0f)) * glm::vec4(vertices[i], 1));
		vertices[i] = glm::vec3(glm::scale(glm::mat4(1.0f), glm::vec3(scaleDownAmount)) * intermVal);
	}
}

void Geometry::centerForTerrain()
{
	int size = vertices.size();
	glm::vec3 center;
	float xMin = FLT_MAX;
	float xMax = FLT_MIN;
	float yMax = FLT_MIN;
	float zMin = FLT_MAX;
	float zMax = FLT_MIN;
	float scaleDownAmount = 0;
	glm::vec4 intermVal;
	for (int i = 0; i < size; ++i)
	{
		xMin = (vertices[i].x < xMin) ? vertices[i].x : xMin;
		xMax = (vertices[i].x > xMax) ? vertices[i].x : xMax;
		yMax = (vertices[i].y > yMax) ? vertices[i].y : yMax;
		zMin = (vertices[i].z < zMin) ? vertices[i].z : zMin;
		zMax = (vertices[i].z > zMax) ? vertices[i].z : zMax;
	}
	center = glm::vec3((xMax + xMin) / 2.0f, yMax, (zMax + zMin) / 2.0f);
	for (int i = 0; i < vertices.size(); ++i)
	{
		vertices[i] = (glm::translate(glm::mat4(1.0f), (center * -1.0f)) * glm::vec4(vertices[i], 1));
	}
}

glm::mat4 Geometry::getToWorld(glm::mat4 C)
{
	return C;
}
