/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** StructClass
*/

#ifndef STRUCTCLASS_HPP_
#define STRUCTCLASS_HPP_
#include <iostream>
#include <vector>

class StructClass {
    public:
        StructClass(const std::string &, bool, const std::string &, const std::vector<std::string> &);
        ~StructClass();

    protected:
        std::string _structName;
        std::string _typedefName;
        bool _hasTypedef;
        std::vector<std::string> _type;
};

#endif /* !STRUCTCLASS_HPP_ */
