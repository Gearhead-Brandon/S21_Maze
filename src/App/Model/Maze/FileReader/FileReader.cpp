#include "FileReader.h"
#include <iostream>

namespace s21{
    FileReader::FileReader(const std::string &path) 
        : file(path), is_open(file.is_open()) {}

    FileReader::~FileReader() {
        if(is_open)
            file.close();
    }
}