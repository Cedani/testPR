/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** Folder
*/

#ifndef FOLDER_HPP_
#define FOLDER_HPP_
#include <iostream>
#include <unordered_map>
#include <vector>
#include <mutex>

class Folder {
    public:
        Folder();
        Folder(const Folder &);
        ~Folder();

        bool addFile(const std::string &, const std::vector<std::string> &);
        bool addFile(const std::string &, const std::string &);
        const std::unordered_map<std::string, std::vector<std::string>> &getFiles(void) const;
        void clearFolder();
    private:
        std::mutex _lock;
        std::unordered_map<std::string, std::vector<std::string>> _files;
};

#endif /* !FOLDER_HPP_ */
