/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** Project
*/

#ifndef PROJECT_HPP_
#define PROJECT_HPP_
#include <iostream>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "StructClass.hpp"

class Project {
    public:
        Project(const std::string &filepath);
        ~Project();

    protected:
        std::vector<StructClass> _structClasses;
};

#endif /* !PROJECT_HPP_ */
