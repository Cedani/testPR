/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** Error
*/

#include "Error.hpp"

Errors::DirectoryError::DirectoryError(const std::string &mes, const std::string &whr) noexcept: _message("Directory Error : " + mes), _where(whr)
{
}

Errors::DirectoryError::~DirectoryError()
{
}

const char * Errors::DirectoryError::what() const noexcept
{
    return (_message.c_str());
}

const std::string &Errors::DirectoryError::where() const
{
    return (_where);
}

Errors::CompilingError::CompilingError(const std::string &mes, const std::string &whr) noexcept: _message("Compiling Error : " + mes), _where(whr)
{
}

Errors::CompilingError::~CompilingError()
{
}

const char * Errors::CompilingError::what() const noexcept
{
    return (_message.c_str());
}

const std::string &Errors::CompilingError::where() const
{
    return (_where);
}
