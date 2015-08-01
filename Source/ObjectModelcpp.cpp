#include "Renderer.h"
#include "PlayerModel.h"
#include <GL/glew.h>
#include "tiny_obj_loader.h"
#include "AssetsDir.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>

using namespace std;
using namespace tinyobj;
using namespace glm;

GLuint VBO;
GLuint IBO;

ObjectModel::PlayerModel() : Model(), awesomeSheepList()
{
	// Vector Array for Shape
	vector<shape_t> shapes;
	vector<material_t> materials;

	// Import the Sheep
	string name = LoadObj(shapes, materials, HOLY_SHEEP, HOLY_SHEEP_MATERIAL);

	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Adds elements of the sheep (Body, Iris, Eye)

	// Main loop for creating the sheep
	for (int index = 0; index < shapes.size(); ++index)
	{
		// Unsigned Integer for Vertex, Indices, Size and Color Vertex
		unsigned int v;
		unsigned int i;
		unsigned int s;
		unsigned int colorVertexBuffer;

		// Vertex Buffer
		glGenBuffers(1, &v);
		glBindBuffer(GL_ARRAY_BUFFER, v);
		glBufferData(GL_ARRAY_BUFFER, shapes[index].mesh.positions.size() * sizeof(float), &shapes[index].mesh.positions[0], GL_STATIC_DRAW);

		// Depending on the index different color for different part of sheep
		float colorForShape;

		if (index == 0) // The Iris of Sheep (Gray)
		{
			colorForShape = 0;
		}
		else if (index == 1) // The Eye of Sheep (Black)
		{
			colorForShape = 0;
		}
		else if (index == 2) // The Body of Sheep (White)
		{
			colorForShape = 1;
		}

		// Color Buffer
		vector<float> colors(shapes[index].mesh.positions.size() * sizeof(float), colorForShape);
		glGenBuffers(1, &colorVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, colors.size(), &colors[0], GL_STATIC_DRAW);

		// Index Buffer
		glGenBuffers(1, &i);
		glBindBuffer(GL_ARRAY_BUFFER, i);
		glBufferData(GL_ARRAY_BUFFER, shapes[index].mesh.indices.size() * sizeof(int32), &shapes[index].mesh.indices[0], GL_STATIC_DRAW);

		s = shapes[index].mesh.indices.size() * sizeof(int32);

		awesomeSheepList.push_back(v);
		awesomeSheepList.push_back(i);
		awesomeSheepList.push_back(s);
		awesomeSheepList.push_back(colorVertexBuffer);
	}

	SetScaling(vec3(5));
}

void PlayerModel::Draw()
{
	glBindVertexArray(mVertexArrayID);

	for (int index = 0; index < awesomeSheepList.size(); index += 4)
	{
		unsigned int vertex = awesomeSheepList[index];
		unsigned int indice = awesomeSheepList[index + 1];
		unsigned int size = awesomeSheepList[index + 2];
		unsigned int color = awesomeSheepList[index + 3];

		GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
		glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);

		// First Attribute (Vertex Position)
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex);
		glVertexAttribPointer(0,				// attribute. No particular reason for 0, but must match the layout in the shader.
			3,				// size
			GL_FLOAT,		// type
			GL_FALSE,		// normalized?
			0,	// stride
			(void*)0		// array buffer offset
			);

		// Third Attribute (Normal)
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vertex);
		glVertexAttribPointer(1,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0    // Normal is Offseted by vec3 (see class Vertex)
			);

		// Third Attribute (Color)
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, color);
		glVertexAttribPointer(2,				// attribute. No particular reason for 0, but must match the layout in the shader.
			3,				// size
			GL_FLOAT,		// type
			GL_FALSE,		// normalized?
			0,	// stride
			(void*)0		// array buffer offset
			);

		// Bind the Buffer.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indice);

		// Draw the elements.
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

		// Close the Buffers.
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}

}