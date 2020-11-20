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
		Face face;
		std::vector <FaceVertex> faceInfo;
		for (int i = 0; i < 3; i++)
		{
			FaceVertex f;
			std::getline(sin, token, '/');
			if (token.size() > 0)
			{
				f.vertexIndex = std::stoi(token) - 1;
			}
			std::getline(sin, token, '/');
			if (token.size() > 0)
			{
				f.texture = std::stoi(token) - 1;
				f.texture = true;
			}
			std::getline(sin, token, ' ');
			if (token.size() > 0)
			{
				f.normalIndex = std::stoi(token) - 1;
				f.normal = true;
			}
			faceInfo.push_back(f);
		}
		face.i = faceInfo[0];
		face.j = faceInfo[1];
		face.k = faceInfo[2];
		faceData.push_back(face);
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

	void mesh::loadMeshData(std::string& filename)
	{
		std::ifstream ifile(filename);
		std::string line;
		while (std::getline(ifile, line)) {
			std::stringstream sline(line);
			parseLine(sline);
		}
		texturesLoaded = (texcoordIdx.size() > 0);
		normalsLoaded = (normalIdx.size() > 0);
	}
}