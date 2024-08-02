#include "FileReader.h"
#include <iostream>

namespace s21{
    FileReader::FileReader(const std::string &path) 
        : file(path){}

    FileReader::~FileReader() {
        if(file.is_open())
            file.close();
    }
}