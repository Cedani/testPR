/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** main
*/

#include "include/Parser.hpp"

int main(void)
{
    Parser parser("server.h");

    std::cout << parser.getFile() << std::endl;
}