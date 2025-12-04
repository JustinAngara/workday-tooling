#include "FileExtractor.h"
#include "Data.h"
#include <fstream>
#include <string>
#include <iostream>

bool FileExtractor::init() {

    Data::Table t;
    
    std::ifstream file(m_fileName);
    if (file.is_open()) {
        parseTable(file);
        file.close();
    } else {
        return false;
    }
    return true;
}

void FileExtractor::parseTable(std::ifstream &file) {
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
        // semantics
        // a # with 2 characters per line post trim, 2nd line will become 
    }
}