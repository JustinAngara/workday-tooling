#pragma once
#include <string>
#include <vector>
// call on main stack, do not init anywhere else
class FileExtractor {
public:
	FileExtractor(std::string fileName)
		: m_fileName(fileName) {}
	bool init(); 
	void parseTable(std::ifstream& file);
private:
	std::string m_fileName;
	
};

