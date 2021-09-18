/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** Reader
*/

#ifndef READER_HPP_
#define READER_HPP_

#include <iostream>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <vector>
#include "Error.hpp"


class Reader {
    public:
        Reader(const std::string &path);
        ~Reader();

        struct dirent *getAll();
        // const std::string otherDirectory();
        const std::string getPath();
    private:
        std::string _path;
        DIR *_directory;
        struct dirent *_all;
        std::vector<std::string> _otherDirectory;
        bool isDirectory(const std::string &path);
};

#endif /* !READER_HPP_ */
