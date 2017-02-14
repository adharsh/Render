#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace ginkgo {

	struct ObjMaterial
	{
		std::string ambientTexture;
		std::string materialName;
		glm::vec3 ambientColor;

		ObjMaterial() : ambientColor(0, 0, 0) {}
	};
	
	struct MaterialLib
	{
		int index;
		std::vector<ObjMaterial> materials;

		ObjMaterial& getMaterialByName(const std::string& name);
	};

	struct Face
	{
		bool usingDefinedUVs;
		bool usingDefinedNormals;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> UVs;
		std::vector<glm::vec3> normals;
		std::vector<unsigned int> indices;
		
		void triangulate(const std::vector<unsigned int>& vect);
	};

	class ObjIntermediate
	{
	private:
		unsigned int index;
		std::vector<glm::vec3> vertex;
		std::vector<glm::vec2> UV;
		std::vector<glm::vec3> normals;
		std::vector<MaterialLib> matLib;
		std::vector<Face> face;
		std::vector<unsigned int> indices;
		std::vector<float>& createFloatChart(std::vector<float>& fList, std::string *tokens, unsigned int tSize);
	public:
		void LoadObj(std::string path);
		void show(std::string* tokens, unsigned int size) const;
		void parseFace(std::string* tokens, unsigned int tSize, Face& faceOut, std::vector<glm::vec3>& vertexList, std::vector<glm::vec2>& uvList, std::vector<glm::vec3>& normalList);
		void parseMaterial(std::string path, MaterialLib& outMaterial);

		const std::vector<glm::vec3>& getVertexList() const { return vertex; }
		const std::vector<glm::vec2>& getUVList() const { return UV; }
		const std::vector<glm::vec3>& getNomalList() const { return normals; }
		const std::vector<MaterialLib>& getMatlibList() const { return matLib; }
		const std::vector<Face>& getFaceList() const { face; }
		const std::vector<unsigned int>& getIndexList() const { return indices; }

	};


}