#include "FileExtractor.h"
#include <fstream>
#include <string>
#include <iostream>

bool FileExtractor::init() {
    std::ifstream file(m_fileName);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << '\n';
        }
        file.close();
    } else {
        return false;
    }
    return true;
}