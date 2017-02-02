#define cerr(x) std::cerr << x << std::endl
#pragma warning(disable:4996) 

#include "ObjLoader.h"

#include <iostream>
#include <fstream>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

namespace ginkgo {

	//struct Vertex
	//{
	//	Vertex(float x, float y, float z)
	//	{
	//		this->x = x;
	//		this->y = y;
	//		this->z = z;
	//	}
	//
	//	int index;
	//	float x, y, z;
	//};


	ObjMaterial& MaterialLib::getMaterialByName(std::string name)
	{
		for (ObjMaterial material : materials)
		{
			if (material.materialName.compare(name))
			{
				return material;
			}
		}
		ObjMaterial emptyMat;
		return emptyMat;
	}

	//struct UV
	//{
	//	int index;
	//	float u, v;
	//};
	void Face::triangulate(std::vector<unsigned int> vect)
	{
		if (vertices.size() == 3)
		{
			indices.emplace_back(vect[0]);
			indices.emplace_back(vect[1]);
			indices.emplace_back(vect[2]);
		}
		else if (vertices.size() == 4)
		{
			/*indices.emplace_back(vect[0]);
			indices.emplace_back(vect[1]);
			indices.emplace_back(vect[2]);

			indices.emplace_back(vect[3]);
			indices.emplace_back(vect[1]);
			indices.emplace_back(vect[2]);*/

			indices.emplace_back(vect[0]);
			indices.emplace_back(vect[1]);
			indices.emplace_back(vect[3]);
			
			indices.emplace_back(vect[2]);
			indices.emplace_back(vect[1]);
			indices.emplace_back(vect[3]); 
		}
	}


	std::vector<float>& ObjIntermediate::createFloatChart(std::vector<float>& fList, std::string *tokens, unsigned int tSize)
	{
		for (unsigned int i = 0; i < tSize; i++)
		{
			std::string cStr = "" + tokens[i];
			if (tokens[0].compare(cStr))
				fList.push_back(std::stof(cStr));
		}
		return fList;
	}

	void ObjIntermediate::LoadObj(std::string path)
	{
		std::vector<glm::vec3> vertexList;
		std::vector<glm::vec2> uvList;
		std::vector<glm::vec3> normalList;
		std::vector<MaterialLib> matLibList;
		std::vector<Face> faceList;
		std::vector<unsigned int> indices;
		std::string returnLine;

		std::ifstream fileStream;
		fileStream.open(path);

		if (fileStream.fail())
		{
			cerr("Failed to Open File specified.");
			return;
		}
		std::vector<std::string> tokens;
		std::vector<float> fList;
		path = path.substr(0, path.find_last_of('/'));

		while (fileStream.good())
		{
			getline(fileStream, returnLine);
			if (returnLine.empty())
				getline(fileStream, returnLine);
			boost::split(tokens, returnLine, boost::is_any_of(" "));
			if (!tokens[0].compare("mtllib"))
			{
				MaterialLib matLib;
				if (tokens.size() > 2)
					for (unsigned int i = 0; i < tokens.size(); i++)
					{
						tokens[1] += tokens[i + 1];
						tokens.erase(tokens.begin() + 1, tokens.begin() + 1 + i);
					}

				parseMaterial(path + "/" + tokens[1], matLib);
				matLibList.emplace_back(matLib);
			}
			//else if (tokens[0].compare("#"));
			else if (!tokens[0].compare("v"))
			{
				fList = createFloatChart(fList, &tokens[0], tokens.size());
				vertexList.emplace_back(glm::vec3(fList[0], fList[1], fList[2]));
				/*vertexList[vertexList.size() - 1].index = vertexList.size();*/
			}
			else if (!tokens[0].compare("vt"))
			{
				fList = createFloatChart(fList, &tokens[0], tokens.size());
				glm::vec2 uvTemp;
				uvTemp.x = fList[0]; uvTemp.y = fList[1];
				uvList.emplace_back(uvTemp);
				/*uvList[uvList.size() - 1].index = uvList.size();*/
			}
			else if (!tokens[0].compare("vn"))
			{
				fList = createFloatChart(fList, &tokens[0], tokens.size());
				normalList.emplace_back(glm::vec3(fList[0], fList[1], fList[2]));
				/*normalList[normalList.size() - 1].index = normalList.size();*/
			}
			else if (!tokens[0].compare("f"))
			{
				Face faceOut;
				parseFace(&tokens[0], tokens.size(), faceOut, vertexList, uvList, normalList);
				faceList.emplace_back(faceOut);
			}
			fList.clear();
			//show(&tokens[0], tokens.size());
		}
		for (const auto &a : faceList)
		{
			for (unsigned int i = 0; i < a.indices.size(); i++)
				indices.emplace_back(a.indices[i]);
		}

		for (unsigned int i = 0; i < indices.size(); i++)
			indices[i]--;

		matLib = matLibList;
		vertex = vertexList;
		normals = normalList;
		UV = uvList;
		face = faceList;
		this->indices = indices;
	}

	void ObjIntermediate::show(std::string* tokens, unsigned int size)
	{
		for (unsigned int i = 0; i < size; i++)
			std::cout << tokens[i].data() << " ";
		std::cout << std::endl;
	}

	void ObjIntermediate::parseFace(std::string* tokens, unsigned int tSize, Face& faceOut, std::vector<glm::vec3>& vertexList, std::vector<glm::vec2>& uvList, std::vector<glm::vec3>& normalList)
	{
		std::string exToken = tokens[1];
		int crash = -1;
		std::vector<unsigned int> index;
		if (boost::contains(exToken, "//"))
			crash = 3; //Vertex, UV, Normal OR Vertex, no UV, Normal
		else if (boost::contains(exToken, "/"))
		{
			crash = 2;
			int temp = 0;
			for (unsigned int i = 0; i < exToken.length(); i++)
				if (exToken.at(i) == '/') temp++;
			if (temp >= 2)
				crash = 4;
			//Vertex, UV, no Normal
		}
		else
			crash = 1;	//Vertex, no UV, no Normal

		if (crash == 1)
		{
			faceOut.usingDefinedUVs = false;
			faceOut.usingDefinedNormals = false;
			for (unsigned int a = 1; a < tSize; a++)
			{
				faceOut.vertices.emplace_back(vertexList[std::stoi(tokens[a])]);
				index.emplace_back(stoi(tokens[a]));
			}
		}
		else if (crash == 2)
		{
			faceOut.usingDefinedUVs = true;
			faceOut.usingDefinedNormals = false;
			for (unsigned int a = 1; a < tSize; a++)
			{
				std::vector<std::string> tookens;
				boost::split(tookens, tokens[a], boost::is_any_of("/"));
				index.emplace_back(std::stoi(tookens[0]));
				faceOut.vertices.emplace_back(vertexList[std::stoi(tookens[0]) - 1]);
				faceOut.UVs.emplace_back(uvList[std::stoi(tookens[2]) - 1]);
			}
		}
		else if (crash == 3)
		{
			faceOut.usingDefinedUVs = false;
			faceOut.usingDefinedNormals = true;
			for (unsigned int a = 1; a < tSize; a++)
			{
				std::vector<std::string> tookens;
				boost::split(tookens, tokens[a], boost::is_any_of("//"));
				index.emplace_back(std::stoi(tookens[0]));
				faceOut.vertices.emplace_back(vertexList[std::stoi(tookens[0]) - 1]);
				faceOut.normals.emplace_back(normalList[std::stoi(tookens[2]) - 1]);
			}
		}
		else if (crash == 4)
		{
			faceOut.usingDefinedUVs = true;
			faceOut.usingDefinedNormals = true;
			for (unsigned int a = 1; a < tSize; a++)
			{
				std::vector<std::string> tookens;
				boost::split(tookens, tokens[a], boost::is_any_of("/"));
				index.emplace_back(std::stoi(tookens[0]));
				faceOut.vertices.emplace_back(vertexList[std::stoi(tookens[0]) - 1]);
				faceOut.UVs.emplace_back(uvList[stoi(tookens[2]) - 1]);
				faceOut.normals.emplace_back(normalList[stoi(tookens[4]) - 1]);
			}
		}
		faceOut.triangulate(index);
	}

	void ObjIntermediate::parseMaterial(std::string path, MaterialLib& outMaterial)
	{
		std::ifstream fileStream;
		std::vector<std::string> tokens;
		std::string returnLine;
		fileStream.open(path);

		int currentMaterialIndex = -1;
		if (fileStream.fail())
		{
			cerr("Failed to open file specified.");
			return;
		}
		while (fileStream.good())
		{
			getline(fileStream, returnLine);
			if (returnLine.empty())
				getline(fileStream, returnLine);
			boost::split(tokens, returnLine, boost::is_any_of(" "));

			returnLine.begin();
			if (!tokens[0].compare("newmtl"))
			{
				currentMaterialIndex++;
				ObjMaterial newMat;
				outMaterial.materials.emplace_back(newMat);
				outMaterial.materials[currentMaterialIndex].materialName = tokens[1];
			}
			if (!tokens[0].compare("Ka"))
			{
				outMaterial.materials[currentMaterialIndex].ambientColor = glm::vec3(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
			}
			if (!tokens[0].compare("map_Ka"))
			{
				outMaterial.materials[currentMaterialIndex].ambientTexture = tokens[1];
			}
			//show(&tokens[0], tokens.size());
		}
	}
}