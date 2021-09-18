/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** Folder
*/

#include "Folder.hpp"

Folder::Folder()
{
}

Folder::Folder(const Folder &other): _files(other._files)
{

}

Folder::~Folder()
{
}


bool Folder::addFile(const std::string &filepath, const std::vector<std::string> &func)
{
    bool wasAdded = false;
    {
        std::unique_lock<std::mutex> lockGuard(_lock);
        if (_files.find(filepath) != _files.end())
            _files[filepath] = func;
        else
            for (const auto &e: func)
                _files[filepath].push_back(e);
        wasAdded = true;
    }
    return (wasAdded);
}

bool Folder::addFile(const std::string &filepath, const std::string &func)
{
    bool wasAdded = false;
    {
        std::unique_lock<std::mutex> lockGuard(_lock);
        if (_files.find(filepath) != _files.end())
            _files[filepath].push_back(func);
        else {
            std::vector<std::string> tmp;
            tmp.push_back(func);
            _files[filepath] = tmp;
        }
        wasAdded = true;
    }
    return (wasAdded);
}


const std::unordered_map<std::string, std::vector<std::string>> & Folder::getFiles(void) const
{
    return (_files);
}

void Folder::clearFolder()
{
    _files.clear();
}
