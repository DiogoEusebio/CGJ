#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Constants.h"

namespace egn
{
	struct mesh {
		typedef struct Vertex
		{
			GLfloat x, y, z;
		} Vertex;

		typedef struct VertexTexture
		{
			GLfloat u, v;
		} VertexTexture;

		typedef struct Normal
		{
			GLfloat nx, ny, nz;
		} Normal;

		typedef struct FaceVertex
		{
			int vertexIndex, textureIndex, normalIndex;
			bool texture = false;
			bool normal = false;
		} FaceVertex;

		typedef struct Face
		{
			FaceVertex i, j, k;
		} Face;


		GLuint VaoId;
		bool texturesLoaded, normalsLoaded;
		std::vector <Vertex> vertexData;
		std::vector <VertexTexture> textureData;
		std::vector <Normal> normalData;
		std::vector <Face> faceData;

		std::vector <unsigned int> vertexIdx, texcoordIdx, normalIdx;


		mesh();
		void parseVertex(std::stringstream& sin);
		void parseTexcoord(std::stringstream& sin);
		void parseNormal(std::stringstream& sin);
		void parseFace(std::stringstream& sin);
		void parseLine(std::stringstream& sin);
		void loadMeshData(std::string& filename);
	};
};
