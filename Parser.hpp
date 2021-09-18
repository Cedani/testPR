/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include "Folder.hpp"
#include "Error.hpp"

class Parser {
    public:
        Parser(const std::string &filepath, Folder &fol);
        Parser(const Parser &other);
        ~Parser();

        void loop();
        const std::vector<std::string> &getFile(void) const;
    protected:
        bool startMultipleComment(std::string &);
        bool endMultipleComment(std::string &);
        std::ifstream _file;
        std::string _filePath;
        bool _multipleComment;
        bool _singleComment;
        Folder &_folder;
        bool _toPrint;
        std::regex _expr;
        std::string _fileString;
        std::vector <std::string> _functions;
};

#endif /* !PARSER_HPP_ */
