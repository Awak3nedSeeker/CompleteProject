#pragma once
#include "Defines.h"
#pragma warning(disable : 4996)


Mesh ModelLoader(const char* filename, float scale, vector<Vertex_3D>& Vertexlist, vector<UINT>& indices)
{
	Vertexlist.clear();
	indices.clear();

	Mesh Skybox;
	vector<XMFLOAT3> _vec;
	vector<XMFLOAT3> _tex;
	vector<XMFLOAT3> _nrm;

	FILE * file = fopen(filename, "r");
	if (file == NULL) {
		printf("Impossible to open the file!\n");
	}

	unsigned int numVertices = 0;
	int vcount = 0;

	while (1) 
	{

		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);

		if (res == EOF) 
		{
			break;
		}

		if (strcmp(lineHeader, "v") == 0) {
			XMFLOAT3 Vertex;
			fscanf(file, "%f %f %f\n", &Vertex.x, &Vertex.y, &Vertex.z);
			Vertex = { (Vertex.x * scale), (Vertex.y * scale), (Vertex.z * scale) };
			_vec.push_back(Vertex);
		}

		else if (strcmp(lineHeader, "vt") == 0) 
		{
			XMFLOAT3 UV;
			fscanf(file, "%f %f\n", &UV.x, &UV.y);
			UV = { UV.x, UV.y, 1 };
			_tex.push_back(UV);
		}

		else if (strcmp(lineHeader, "vn") == 0) 
		{
			XMFLOAT3 NRM;
			fscanf(file, "%f %f %f\n", &NRM.x, &NRM.y, &NRM.z);
			NRM = { NRM.x, NRM.y, NRM.z };
			_nrm.push_back(NRM);
		}

		else if (strcmp(lineHeader, "f") == 0) 
		{
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			
			if (matches != 9) 
			{
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				break;
			}

			Vertex_3D tempvert;

			tempvert = { { _vec[vertexIndex[0] - 1] }, { _tex[uvIndex[0] - 1] }, { _nrm[normalIndex[0] - 1] } };
			Vertexlist.push_back(tempvert);
			indices.push_back(vcount);
			vcount++;

			tempvert = { { _vec[vertexIndex[1] - 1] }, { _tex[uvIndex[1] - 1] }, { _nrm[normalIndex[1] - 1] } };
			Vertexlist.push_back(tempvert);
			indices.push_back(vcount);
			vcount++;

			tempvert = { { _vec[vertexIndex[2] - 1] }, { _tex[uvIndex[2] - 1] }, { _nrm[normalIndex[2] - 1] } };
			Vertexlist.push_back(tempvert);
			indices.push_back(vcount);
			vcount++;
		}
	}

	numVertices = vcount;

	numVerts = unsigned int(Vertexlist.size());
	numIndices = unsigned int(indices.size());

	Vertex_3D* modelVerts = new Vertex_3D[numVerts];
	unsigned int* modelIndices = new unsigned int[numIndices];

	for (int i = 0; i < int(numVerts); i++)
	{
		modelVerts[i] = Vertexlist[i];
		modelIndices[i] = indices[i];
	}

	for (size_t i = 0; i < _tex.size(); i++)
	{
		_tex[i].y = 1 - _tex[i].y;
	}

	Skybox.Vert = modelVerts;
	Skybox.indi = modelIndices;

	return Skybox;
}