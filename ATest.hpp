/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** ATest
*/

#ifndef ATEST_HPP_
#define ATEST_HPP_
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QPlainTextEdit>
#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QComboBox>
#include "Error.hpp"
#define UNSD __attribute__((unused))


class ATest {
    public:
        ATest(const std::string &, const std::string &, QMainWindow *);
        ~ATest();

        void askForArgs();
        void generateFile();
        void initType();
        void checkFuncType();
    protected:
        void calcFunctionName(const std::string &);
        void calcArguments(const std::string &);
        void validFunctionName();
        void checkValidType();
        void writeHeader();
        void checkStream();
        void checkAllInput();
        std::size_t findLastSpaceBefore(char, int, std::string);
        void askType();
        std::string _type;
        std::string _functionType;
        std::vector<std::string> _argsType;
        std::unordered_map<std::string, std::string> _argsValue;
        std::string _expectedValue;
        std::string _testName;
        std::string _fileName;
        std::vector<std::string> _allowedType;
        std::string _funcName;
        std::string _filePath;
        QMainWindow *_win;
};

#endif /* !ATEST_HPP_ */
