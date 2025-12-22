#include "FileExtractor.h"
#include "Data.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>


bool FileExtractor::init() {

    
    std::ifstream file(m_fileName);
    if (file.is_open()) {
        parseFile(file);
        file.close();
    } else {
        return false;
    }
    return true;
}

// convert each indecie between the strings to the block
void FileExtractor::processBlock(const std::vector<std::string>& block) {
    if (block.size() < 2) return; // invalid table

    Data::Table table;
    table.title = block[0];
    table.company = block[1];

    std::string desc;
    for (size_t i = 2; i < block.size(); ++i) {
        desc += block[i] + '\n';
    }

    table.description = desc;
    m_output.push_back(std::move(table));
}

// main method
void FileExtractor::parseFile(std::ifstream& file) {
    std::string line;
    std::vector<std::string> block;

    while (std::getline(file, line)) {
        // reached the end of the block
        if (line.empty()) {
            if (!block.empty()) {
                processBlock(block);
                block.clear();
            }
        } else {
            block.push_back(line);
        }
    }

    // handle last block if file doesn't end with blank line
    if (!block.empty()) {
        processBlock(block);
    }
}

