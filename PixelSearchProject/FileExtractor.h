#pragma once
#include <string>
#include "Data.h"
#include <vector>
#include <array>

class FileExtractor {
public:
	FileExtractor(std::string fileName)
		: m_fileName(fileName) {}
	bool init(); 
	void parseFile(std::ifstream& file);
	void processBlock(const std::vector<std::string>& block);

private:
	std::vector<Data::Table> m_output; 
	std::vector<int> m_indices;
	std::string m_fileName;
	std::string m_fileContent;
	
};

