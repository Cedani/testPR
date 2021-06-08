/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** test
*/

#include <iostream>
#include <regex>
#include <fstream>
#include <sstream>

int main(int ac, char *av[])
{
    std::ifstream file(av[1]);
    std::stringstream streamStr;
    // std::string str("_tester \n _second");
    std::regex expr("/[a-zA-Z0-9_]+\\s[\\*]*[a-zA-Z_][a-zA-Z0-9_]+\\s?\\([a-zA-Z0-9_,\\s\\*\\[\\]\\+\\(\\)]*\\)/g");
    std::smatch sm;

    streamStr << file.rdbuf();
    std::string str(streamStr.str());
    // std::regex_match(str, sm, expr);

    std::regex_match(str.cbegin(), str.cend(), sm, expr);
    // std::cout << str << std::endl;
    std::cout << sm.size() << std::endl;
    return (0);
}