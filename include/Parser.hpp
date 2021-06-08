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

class Parser {
    public:
        Parser(const std::string &filepath);
        ~Parser();

        const std::string &getFile() const;
    protected:
        void loop();
        bool removeCommentSingleline(std::string &);
        // bool removeCommentMultipleLine(std::string &tmp);
        bool startMultipleComment(std::string &);
        bool endMultipleComment(std::string &);
        std::ifstream _file;
        std::string _fileString;
        std::string _filePath;
        bool _multipleComment;
        bool _singleComment;
};

#endif /* !PARSER_HPP_ */
