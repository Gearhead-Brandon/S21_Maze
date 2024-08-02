/**
 * @file FileReader.h
 * @brief Header file describing the class FileReader
 */

#ifndef FILE_READER_H
#define FILE_READER_H

#include <fstream>

namespace s21{

    /**
     * @brief Wrapper for std::ifstream
     */
    class FileReader {
    public:

        //! File stream
        std::ifstream file;

        /**
         * @brief Parametrized constructor
         * @param path - path to the file
         */
        FileReader(const std::string &path);

        /**
         * @brief Destructor
         */
        ~FileReader();
    };
}

#endif