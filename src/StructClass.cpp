/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** StructClass
*/

#include "include/StructClass.hpp"

StructClass::StructClass(const std::string &name, bool hasTypedef, const std::string &typeDef, const std::vector<std::string> &typeStruct): _structName(name), _hasTypedef(hasTypedef), _typedefName(typeDef), _type(typeStruct)
{
}

StructClass::~StructClass()
{
}
