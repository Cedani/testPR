/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_
#include <iostream>
#include <exception>

namespace Errors {
    class DirectoryError;
    class CompilingError;
}

class Errors::DirectoryError : public std::exception {
    public:
        DirectoryError(const std::string &, const std::string & ) noexcept;
        ~DirectoryError();

        const char *what() const noexcept override;
        const std::string &where() const;
    private:
        std::string _message;
        std::string _where;
};

class Errors::CompilingError : public std::exception {
    public:
        CompilingError(const std::string &, const std::string & ) noexcept;
        ~CompilingError();

        const char *what() const noexcept override;
        const std::string &where() const;
    private:
        std::string _message;
        std::string _where;
};


#endif /* !ERROR_HPP_ */
