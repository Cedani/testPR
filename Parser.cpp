/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** Parser
*/

#include "Parser.hpp"

Parser::Parser(const std::string &filepath, Folder &fol): _file(filepath), _filePath(filepath), _multipleComment(false), _folder(fol), _toPrint(false), _expr("^(?!\\/\\/)(?!define)\\w[(static)\\w(const)\\w a-zA-Z0-9_]+\\s[\\*]*[a-zA-Z_][a-zA-Z0-9_]+\\s?\\([a-zA-Z0-9_,\\s\\*\\[\\]\\+\\(\\)\\/]*\\)")
{
}

Parser::Parser(const Parser &other): _file(other._filePath), _filePath(other._filePath), _multipleComment(false), _singleComment(false), _folder(other._folder), _toPrint(true), _expr(other._expr)
{
}

Parser::~Parser()
{
    if (_toPrint)
        std::cout << _filePath << " finished" << std::endl;
    _file.close();
}

void Parser::loop()
{
    try {
        std::string tmp;
        std::smatch sm;

        if (!_file.is_open()) {
//            std::cout << _filePath << " not opened" << std::endl;
            throw Errors::DirectoryError(_filePath + " not opened", "");
        }
        while (getline(_file, tmp)) {
            std::string save = tmp;
            if (startMultipleComment(tmp))
                _fileString += tmp;
            if (endMultipleComment(save)) {
                _fileString += save;
                continue;
            }
            if (_multipleComment)
                continue;
            if (std::regex_search(tmp.cbegin(), tmp.cend(), sm, _expr))
                _functions.push_back(sm[0]);
            // std::cout << "here" << std::endl;
        }
        if (_functions.size() > 0)
            while (!_folder.addFile(_filePath, _functions));
    }  catch (const Errors::CompilingError &e) {
        throw e;
    } catch (const Errors::DirectoryError &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
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

const std::vector<std::string> &Parser::getFile(void) const
{
    return (_functions);
}
