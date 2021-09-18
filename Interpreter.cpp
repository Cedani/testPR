/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** Interpreter
*/

#include "Interpreter.hpp"

Interpreter::Interpreter()
{
}

Interpreter::~Interpreter()
{
}

char **Interpreter::vectorToArray(const std::vector<std::string> &vec)
{
    int i = 0;
    char **result = new char* [vec.size() + 1];

    for (const auto &e: vec) {
        result[i] = new char[e.size() + 1];
        memset(result[i], 0, e.size() + 1);
        strcpy(result[i++], e.c_str());
    }
    result[i] = nullptr;
    return (result);
}

void Interpreter::checkPathAndCompilation(const std::string &filepath, const std::string &cmp)
{
    char buffer[1048] = {0};

    getcwd(buffer, 1048);
    if (chdir(filepath.c_str()) == -1)
        throw Errors::DirectoryError("chdir: " + filepath + " wrong filepath", "Interpreter.cpp, line 38");
    if (isCompiling(cmp) == 0)
        std::cout << "success" << std::endl;
    else
        throw Errors::CompilingError("Wrong line of compilation", "Interpreter.cpp, line 46");
    chdir(buffer);
}

bool Interpreter::initialization()
{
    try {
        checkPathAndCompilation(_filepath, _lineCompil);
    }  catch (const Errors::CompilingError &e) {
        throw e;
    } catch (const Errors::DirectoryError &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
    return (true);
}

std::vector<std::string> Interpreter::parseCommand(const std::string &cmd)
{
    std::vector<std::string> _vec;
    int i = 0;

    for (std::size_t idx = 0; idx != cmd.npos; idx = cmd.find(' ', idx + 1)) {
        std::string tmp;
        std::size_t test = cmd.find(' ', idx + 1);
        if (test == cmd.npos)
            tmp = cmd.substr(idx);
        else
            tmp = cmd.substr(idx, test - idx);
        if (tmp[0] == ' ')
            tmp.erase(0, 1);
        _vec.push_back(tmp);
        i += 1;
    }
    return (_vec);
}

int Interpreter::isCompiling(const std::string &cmd)
{
    std::vector<std::string> _vec = parseCommand(cmd);
    char **result = vectorToArray(_vec);
    int pid = 0;
    int status = 0;

    pid = fork();
    if (pid == 0) {
        if (execvp(result[0], result) == -1) {
            perror("execvp");
            exit (84);
        }
        exit(0);
    } else if (pid != -1)
        waitpid(pid, &status, 0);
    freeCharArray(result, _vec.size());
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (-84);
}

void Interpreter::freeCharArray(char **result, int size)
{
    for (int i = 0; i < size; ++i)
        delete[] result[i];
    delete[] result;
}

void Interpreter::setFilePath(const std::string &file)
{
    _filepath = file;
}

void Interpreter::setLineCompilation(const std::string &line)
{
    _lineCompil = line;
}
