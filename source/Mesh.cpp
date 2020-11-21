#include "../header/MasterHeader.h"
#include <vector>

namespace egn
{
	mesh::mesh(){}

	void mesh::parseVertex(std::stringstream& sin)
	{
		Vertex v;
		sin >> v.x >> v.y >> v.z;
		vertexData.push_back(v);
	}

	void mesh::parseTexcoord(std::stringstream& sin)
	{
		VertexTexture t;
		sin >> t.u >> t.v;
		textureData.push_back(t);
	}

	void mesh::parseNormal(std::stringstream& sin)
	{
		Normal n;
		sin >> n.nx >> n.ny >> n.nz;
		normalData.push_back(n);
	}

	void mesh::parseFace(std::stringstream& sin)
	{
		std::string token;
		for (int i = 0; i < 3; i++)
		{
			std::getline(sin, token, '/');
			if (token.size() > 0) vertexIdx.push_back(std::stoi(token));
			std::getline(sin, token, '/');
			if (token.size() > 0) texcoordIdx.push_back(std::stoi(token));
			std::getline(sin, token, ' ');
			if (token.size() > 0) normalIdx.push_back(std::stoi(token));
		}
	}

	void mesh::parseLine(std::stringstream& sin)
	{
		std::string s;
		sin >> s;
		if (s.compare("v") == 0) parseVertex(sin);
		else if (s.compare("vt") == 0) parseTexcoord(sin);
		else if (s.compare("vn") == 0) parseNormal(sin);
		else if (s.compare("f") == 0) parseFace(sin);
	}

	void mesh::loadMeshData(const std::string& filename)
	{
		std::ifstream ifile(filename);
		std::string line;
		while (std::getline(ifile, line)) {
			std::stringstream sline(line);
			parseLine(sline);
		}
		texturesLoaded = (texcoordIdx.size() > 0);
		normalsLoaded = (normalIdx.size() > 0);
		//int debugcount = 0;
		//std::cout << vertexData.size() << std::endl;
		for (unsigned int i = 0; i < vertexIdx.size(); i++) {
			unsigned int vi = vertexIdx[i];
			//std::cout << vi << " " << debugcount++ << std::endl;
			Vertex v = vertexData[vi - 1];
			Vertices.push_back(v);	
		}
		//for (int i = 0; i < vertexIdx.size(); i++)
		
	}



	void mesh::createBufferObjects()
	{

		GLuint VboVertices;

		glGenVertexArrays(1, &VaoId);
		glBindVertexArray(VaoId);
		{
			glGenBuffers(1, &VboVertices);
			glBindBuffer(GL_ARRAY_BUFFER, VboVertices);
			{
				glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(VERTICES);
				glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			}
			
		}
		//MAY CAUSE PROBLEMS DEPENDING ON GRAPHICS CARD MANUFACTURER
		//glBindVertexArray(0);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glDeleteBuffers(1, &VboVertices);
	}

	void mesh::destroyBufferObjects()
	{
		glBindVertexArray(VaoId);
		glDisableVertexAttribArray(VERTICES);
		glDeleteVertexArrays(1, &VaoId);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void mesh::draw()
	{
		glBindVertexArray(VaoId);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)Vertices.size());
	}
}