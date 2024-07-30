#ifndef FILE_READER_H
#define FILE_READER_H

#include <fstream>

namespace s21{
    class FileReader {
    public:
        std::ifstream file;

        FileReader(const std::string &path);

        ~FileReader();

    private:
        bool is_open;
    };
}

#endif