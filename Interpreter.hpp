/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** Interpreter
*/

#ifndef INTERPRETER_HPP_
#define INTERPRETER_HPP_
#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include "Error.hpp"

class Interpreter {
    public:
        Interpreter();
        ~Interpreter();

        int isCompiling(const std::string &cmd);
        bool initialization();
        void setFilePath(const std::string &);
        void setLineCompilation(const std::string &);
    protected:
        std::vector<std::string> parseCommand(const std::string &cmd);
        void freeCharArray(char **result, int size);
        char **vectorToArray(const std::vector<std::string> &vec);
        void checkPathAndCompilation(const std::string &filepath, const std::string &cmp);
        std::string _filepath;
        std::string _lineCompil;
};

#endif /* !INTERPRETER_HPP_ */
