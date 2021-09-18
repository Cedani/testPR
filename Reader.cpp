/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** Reader
*/

#include "Reader.hpp"

Reader::Reader(const std::string &path): _path(path), _directory(opendir(path.c_str())), _all(nullptr)
{
    if (!_directory)
        throw Errors::DirectoryError("no such file or directory", "Rea.hpp, Reader::Reader(), line 62");
}

Reader::~Reader()
{
    closedir(_directory);
}

bool Reader::isDirectory(const std::string &path)
{
    DIR *tmp = opendir(path.c_str());

    if (!tmp)
        return (false);
    closedir(tmp);
    return (true);
}

const std::string Reader::getPath()
{
    return (_path + _all->d_name);
}

struct dirent *Reader::getAll()
{
    _all = readdir(_directory);
    std::size_t idx = 0;
    if (_all && _all->d_name[0] != '.') {
        std::string filepath(_path + _all->d_name);
        if (isDirectory(filepath)) {
            _otherDirectory.push_back(filepath);
        }
    } else if (!_otherDirectory.empty()) {
        while (!_all && !_otherDirectory.empty()) {
            closedir(_directory);
            _directory = opendir(_otherDirectory[0].c_str());
            _path = _otherDirectory[0] + "/";
            idx = _path.find('/');
            if (idx != _path.npos && idx != _path.size() - 1 && _path[idx + 1] == '/')
                _path.erase(idx);
            _otherDirectory.erase(_otherDirectory.cbegin());
            _all = readdir(_directory);
        }
    }
    return (_all);
}
