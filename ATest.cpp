/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** ATest
*/

#include "ATest.hpp"

ATest::ATest(const std::string &proto, const std::string &filePath, QMainWindow *w): _filePath(filePath), _win(w)
{
//    std::string tmpName;
    initType();
    calcFunctionName(proto);
    calcArguments(proto);
    try {
        askType();
        if (_type == "Manual") {
            checkAllInput();
            return;
        }
        checkValidType();
        askForArgs();
        std::cout << "hello"<< std::endl;
        if (_type == "Stream") {
            checkStream();
        } else {
            generateFile();
        }
    } catch (const Errors::CompilingError &e) {
        throw e;
    } catch (const Errors::DirectoryError &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}

void ATest::calcArguments(const std::string &proto)
{
    std::string args(proto.substr(proto.find('(') + 1));
    std::size_t idx = 0;

    for (; idx != args.npos; idx = args.find(',', idx + 1)) {
        std::size_t endArg = args.find(',', idx + 1);
        if (endArg == args.npos)
            endArg = args.find(')');
        std::size_t tmp = args.find('*', idx);
        if (tmp == args.npos || tmp > endArg)
            tmp = args.find(' ', idx);
        _argsType.push_back(args.substr(((idx == ',') ? idx + 1 : idx), tmp + 1));
    }
}

void ATest::validFunctionName()
{
    while (_funcName[0] == '*')
        _funcName.erase(0);
}

ATest::~ATest()
{
}

void ATest::calcFunctionName(const std::string &proto)
{
    std::string type(proto.substr(0, proto.find('(')));
    std::size_t idx = 0;

    if ((idx = type.find('*')) != type.npos) {
        _functionType = type.substr(0, idx + 1);
        _funcName = type.substr(idx + 1);
    }
    else {
        idx = type.find(' ');
        _functionType = type.substr(0, idx + 1);
        _funcName = type.substr(idx + 1);
    }
}

std::size_t ATest::findLastSpaceBefore(char c, int idx, std::string tmp)
{
    std::size_t i = idx;
    std::size_t last = i;
    for (; i != tmp.npos && i < tmp.find(c, idx); last = i, i = tmp.find(' ', i + 1));
    return (last);
}

void ATest::initType()
{
    _allowedType.push_back("char");
    _allowedType.push_back("int");
    _allowedType.push_back("short int");
    _allowedType.push_back("short");
    _allowedType.push_back("long int");
    _allowedType.push_back("long");
    _allowedType.push_back("long long int");
    _allowedType.push_back("long long");
    _allowedType.push_back("float");
    _allowedType.push_back("double");
    _allowedType.push_back("long double");
    _allowedType.push_back("void");
}

void ATest::askType()
{
    QDialog dialog(_win);
    QComboBox boxAsk;
    QFormLayout form(&dialog);
    QLabel label("Choose mode of test creating");

    boxAsk.addItem("Quick");
    boxAsk.addItem("Stream");
    boxAsk.addItem("Manual");
    form.addRow(&label);
    form.addRow(&boxAsk);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    form.addRow(&buttonBox);
    int status = dialog.exec();
    if (status == QDialog::Accepted) {
       _type = boxAsk.itemText(boxAsk.currentIndex()).toUtf8().constData();
    } else if (status == QDialog::Rejected) {
        throw Errors::DirectoryError("Error", "Didn't perform action");
    }
}

void ATest::checkValidType()
{
    for (const auto &e: _allowedType) {
        if (_functionType.find(e) != _functionType.npos)
            return;
    }
    throw Errors::CompilingError("Not allowed type of function", "");
}

void ATest::writeHeader()
{
    std::ofstream file(_fileName);

    file << "#include " << "\""<< _filePath << "\"" << std::endl;
    file << "#include <criterion/criterion.h>" << std::endl;
    file << "#include <criterion/redirect.h>" << std::endl;
    file << std::endl;
    file.close();
}

void ATest::generateFile()
{
    std::size_t i = 0;
    std::ofstream file(_filePath, std::ios_base::app);

    if (!file.is_open()) {
        std::cout << _filePath << std::endl;
        std::cout << "error " << std::endl;
        return;
    }
    file << "Test (" << "Test" + _funcName  << ", " << _testName  << ") {" << std::endl;
    for (const auto &e: _argsValue) {
//        if (e.first.find("char") != e.first.npos && (e.first.find("*") != e.first.npos || e.first.find("[") != e.first.npos))
//            file << "\t" << e.first << "= " << e.second << ";" << std::endl;
//        else
            file << "\t" << e.first << "= " << e.second << ";" << std::endl;
    }
    file << "\t" <<_functionType << " result = " << _funcName << "(";
    for (const auto &e: _argsValue) {

        file << e.second;
        ++i;
        if (i != _argsValue.size())
            file << ", ";
    }
    file << ");" << std::endl;
    if (_functionType.find("char *") != _functionType.npos) {
        file << "\tcr_assert_str_eq(\"" << _expectedValue << "\", " << "result);" << std::endl;
    } else {
        file << "\tcr_assert_eq(" << _expectedValue << ", " << "result);" << std::endl;
    }
    file << "}" << std::endl << std::endl;
    file.close();
}

void ATest::checkStream()
{
    std::size_t i = 0;
    std::ofstream file(_filePath, std::ios_base::app);

    if (!file.is_open()) {
        std::cout << _filePath << std::endl;
    }
    file << "Test (" << "Test" + _funcName  << ", " << _testName  << ") {" << std::endl;
    for (const auto &e: _argsValue) {
            file << "\t" << e.first << "= " << e.second << ";" << std::endl;
    }
    file << "\tcr_redirect_stdout();" << std::endl;
    file << "\t" << _funcName << "(";
    for (const auto &e: _argsValue) {
        file << e.second;
        ++i;
        if (i != _argsValue.size())
            file << ", ";
    }
    file << ");" << std::endl;
//    if (_functionType.find("char *") != _functionType.npos) {
        file << "\tcr_assert_stdout_eq_str(\"" << _expectedValue << "\");" << std::endl;
//    } else {
//        file << "\tcr_assert_stdout_eq(\"" << _expectedValue << "\", " << "result);" << std::endl;
//    }
    file << "}" << std::endl << std::endl;
    file.close();
}

void ATest::checkAllInput()
{
    QDialog dialog(_win);
    QPlainTextEdit file;
    QFormLayout form(&dialog);
    QLabel label("Enter your test code");
    std::ofstream fileStream(_filePath, std::ios_base::app);

    form.addRow(&label);
    form.addRow(&file);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    int status = dialog.exec();
    if (status == QDialog::Accepted) {
        fileStream << file.toPlainText().toUtf8().constData();
    } else if (status == QDialog::Rejected) {
        throw Errors::DirectoryError("didn't perform action", "");
    }
    fileStream.close();
}

void ATest::askForArgs()
{
    int i = 0;
    std::string tmp;
    QString result;

    _testName = QInputDialog::getText(_win, "Test name", "Enter test Name").toUtf8().constData();
    for (const auto &e: _argsType) {
        std::cout << " ------------------------------------------------------" + e << std::endl;
        if (i == 0 && (_functionType.find("void") == _functionType.npos || _type == "Stream")) {
            if (_functionType.find("int") != e.npos) {
                result = QString::number(QInputDialog::getInt(_win, "Args", QString("Enter expected value")));
            } else if (_functionType.find("double") != e.npos || e.find("float") != e.npos) {
                result = QString::number(QInputDialog::getDouble(_win, "Args", QString("Enter expected value")));
            } else {
                result = QString(QInputDialog::getText(_win, "Args", QString("Enter expected value")));
            }
            if (result.size() <= 0)
                throw Errors::DirectoryError("Value not entered", "");
            _expectedValue = result.toUtf8().constData();
        } else {
            result = QInputDialog::getText(_win, "Args", QString("Enter expected value"));
            if (result.size() <= 0)
                throw Errors::DirectoryError("Value not entered", "");
            _expectedValue = result.toUtf8().constData();
        }
        ++i;
        if (e.find("int") != e.npos) {
            result = QString::number(QInputDialog::getInt(_win, "Args", QString("Enter %1. args").arg(i)));
        } else if (e.find("double") != e.npos || e.find("float") != e.npos) {
            result = QString::number(QInputDialog::getDouble(_win, "Args", QString("Enter %1. args").arg(i)));
        } else {
            result = QInputDialog::getText(_win, "Args", QString("Enter %1. args").arg(i));
        }
        if (result.size() <= 0)
            throw Errors::DirectoryError("Value not entered", "");
        std::string value = e + " var" + std::to_string(i++);
        if (value.find("char") != value.npos && (value.find("*") != value.npos || value.find("[") != value.npos))
            _argsValue[value] = std::string("strdup(\"") +  result.toUtf8().constData() + "\")";
        else if (value.find("char") != value.npos) {
            _argsValue[value] = std::string("'") +  result.toUtf8().constData() + "'";
        } else
            _argsValue[value] = result.toUtf8().constData();
    }
}
