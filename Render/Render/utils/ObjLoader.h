#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>

namespace ginkgo {

	class ObjIntermediate
	{
	private:
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
		std::vector<unsigned int> indices;
	public:
		void LoadObj(std::string path);
		
		const std::vector<glm::vec3>& getPositionList() const { return positions; }
		const std::vector<glm::vec2>& getUVList() const { return uvs; }
		const std::vector<glm::vec3>& getNomalList() const { return normals; }
		const std::vector<unsigned int>& getIndexList() const { return indices; }

	};


}