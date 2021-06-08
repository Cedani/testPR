/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** Parser
*/

#include "include/Parser.hpp"

Parser::Parser(const std::string &filepath): _file(filepath), _filePath(filepath), _multipleComment(false)
{
    loop();
}

Parser::~Parser()
{
    std::cout << _filePath << " finished" << std::endl;
}

void Parser::loop()
{
    std::string tmp;

    while (getline(_file, tmp)) {
        std::string save = tmp;
        if (startMultipleComment(tmp)) {
            _fileString += tmp;
            // continue;
        }
        if (endMultipleComment(save)) {
            _fileString += save;
            continue;
        }
        if (_multipleComment) {
            // std::cout << "multiple" << std::endl;
            continue;
        }
        if (removeCommentSingleline(tmp)) {
            _fileString += tmp;
            continue;
        }
        _fileString += tmp + "\n";
    }
}

bool Parser::startMultipleComment(std::string &tmp)
{
    std::size_t idx = tmp.find("/*", 0);

    if (_multipleComment)
        return false;
    if (!_multipleComment && idx == tmp.npos) {
        _multipleComment = false;
        return (false);
    }
    _multipleComment = true;
    tmp = (idx == 0) ? "" : tmp.substr(0, idx) + "\n";
    return (true);
}

bool Parser::endMultipleComment(std::string &tmp)
{
    std::size_t idx = tmp.find("*/", 0);

    if (idx == tmp.npos)
        return (false);
    _multipleComment = false;
    if (idx != tmp.size() - 2)
        tmp = tmp.substr(idx + 2) + "\n";
    else
        tmp = "";
    return (true);
}

bool Parser::removeCommentSingleline(std::string &tmp)
{
    std::size_t idx = tmp.find("//", 0);

    if (idx == tmp.npos)
        return (false);
    tmp = (idx == 0) ? "" : tmp.substr(0, idx) + '\n';
    return (true);
}

const std::string &Parser::getFile(void) const
{
    return (_fileString);
}