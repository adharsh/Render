#include <string>
#include "fileutils.h"

#include <fstream>
#include <iostream>
#include <vector>

namespace ginkgo {

	std::string FileUtils::read_file(const char* filepath)
	{
		FILE* file = fopen(filepath, "rt");	//we read as t -> textfile bc if b -> bytes then it would all be in one line like in bytes
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file); // binary streams -> number of bytes, text streams -> number of characters

		char* data = new char[length + 1]; // + Termination character
		memset(data, 0, length + 1);	//use memset to clear away any binary text
		fseek(file, 0, SEEK_SET);	//Back to beginning
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;

		return result;
	}

	Mesh* FileUtils::loadMesh(std::string filepath)
	{

		if (filepath.substr(filepath.rfind(".obj")).compare(".obj"))
		{
			std::cout << "Not an .obj file!" << std::endl;
			return nullptr;
		}

		std::vector<glm::vec3> vertices;
		std::vector<GLuint> indices;

		std::ifstream file(filepath);
		std::string line;

		if (!file.good())
			return nullptr;

		const int MAX_CHARS_PER_LINE = 512;
		const int MAX_TOKENS_PER_LINE = 20;
		const char* const DELIMITER = " ";

		while (!file.eof())
		{
			// read an entire line into memory
			char buf[MAX_CHARS_PER_LINE];
			file.getline(buf, MAX_CHARS_PER_LINE);

			// parse the line into blank-delimited tokens
			int n = 0; // a for-loop index

					   // array to store memory addresses of the tokens in buf
			const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0

														 // parse the line
			token[0] = strtok(buf, DELIMITER); // first token
			if (token[0]) // zero if line is blank
			{
				for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
				{
					token[n] = strtok(0, DELIMITER); // subsequent tokens
					if (!token[n]) break; // no more tokens
				}
			}

			for (int i = 0; i < n; i++) // n = #of tokens
				std::cout << "Token[" << i << "] = " << token[i] << std::endl;
			std::cout << std::endl;

		}


	}
}