/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** Project
*/

#include "Project.hpp"

Project::Project()
{
}

Project::Project(const Project &other): _folder(other._folder)
{
}

void Project::initProject(const std::string &file, const std::string &line)
{
    try {
        _folder.clearFolder();
        _filepath = file;
        _lineCompil = line;
        _interp.setFilePath(_filepath);
        _interp.setLineCompilation(_lineCompil);
        _interp.initialization();
       if (_filepath[_filepath.size() - 1] != '/')
            _filepath.append("/");
        Reader _reader(_filepath);
        int i = 0;
        for (struct dirent *all = _reader.getAll(); all; all = _reader.getAll(), ++i) {
            std::string tmp(all->d_name);
            if (tmp.find(".h") == tmp.npos)
                continue;
            Parser _newParser(_reader.getPath(), _folder);
            _thread.push_back(std::thread(&Parser::loop, _newParser));
        }
        for (auto &t: _thread)
            t.join();
        _thread.clear();
    }  catch (const Errors::CompilingError &e) {
        throw e;
    } catch (const Errors::DirectoryError &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
    std::cout << "=================================================functions=================================================" << std::endl;
    for (const auto &e: _folder.getFiles()) {
        std::cout << "---------------------------" << e.first << ": " << "---------------------------" << std::endl;
        for (const auto &f: e.second)
            std::cout << f << std::endl;
    }
    std::cout << "=================================================functions=================================================" << std::endl;
}

Project::~Project()
{
}

void Project::displayFiles()
{
}

const Folder & Project::getFolder() const
{
    return (_folder);
}

void Project::addFiles(const std::string &filePath)
{
    try {
        Parser parser(filePath, _folder);
        parser.loop();
    }  catch (const Errors::CompilingError &e) {
        throw e;
    } catch (const Errors::DirectoryError &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}

void Project::addFunction(const std::string &filename, const std::string &function)
{
    _folder.addFile(filename, function);
}

void Project::initFile(const std::string &filepath, const std::string &filename)
{
    std::ofstream file(filename);

    std::cout << "filename: " << filename << std::endl;
    file << "#include " << "\""<< filepath << "\"" << std::endl;
    file << "#include <criterion/criterion.h>" << std::endl;
    file << "#include <criterion/redirect.h>" << std::endl;
    file << std::endl;
    file.close();
}

void Project::rejected(QMainWindow *win)
{
    QMessageBox::warning(win, "Error", "Didn't perform action");
}

void Project::askTestFile(QMainWindow *win, QString funcT, QString file, QString value)
{
    QString filename;
    if (file == "New file")
        filename = QInputDialog::getText(win, "Filename", "Enter filename");

    std::string filepath = _filepath;
    try {
        if (filepath[filepath.size() -1] == '/')
            filepath.erase(filepath.size() - 1);
        if (filename.size() > 0) {
            _tests[filepath + "/tests/" + filename.toUtf8().constData()] = std::vector<ATest>();
            initFile(value.toUtf8().constData(), filepath + "/tests/" + filename.toUtf8().constData());
            _tests[filepath + "/tests/" + filename.toUtf8().constData()].push_back(ATest(funcT.toUtf8().constData(), filepath + "/tests/" + filename.toUtf8().constData(), win));
        } else {
            _tests[file.toUtf8().constData()].push_back(ATest(funcT.toUtf8().constData(), file.toUtf8().constData(), win));
        }
    }  catch (const Errors::CompilingError &e) {
        QMessageBox::warning(win, "Error", e.what());
        _tests.erase(filepath + "/tests/" + filename.toUtf8().constData());
        return;
    } catch (const Errors::DirectoryError &e) {
        QMessageBox::warning(win, "Error", e.what());
        _tests.erase(filepath + "/tests/" + filename.toUtf8().constData());
        return;
    } catch (const std::exception &e) {
        QMessageBox::warning(win, "Error", e.what());
        _tests.erase(filepath + "/tests/" + filename.toUtf8().constData());
        return;
    }
}

void Project::addTestExistFile(QMainWindow *win, QString value, QString file)
{
    QDialog dialog(win);
    QFormLayout form(&dialog);
    QComboBox boxFile;
    QLabel labelFile("Choose a file");

    for (const auto &e: _folder.getFiles()) {
        if (e.first != value.toUtf8().constData())
            continue;
        for (const auto &j: e.second)
            boxFile.addItem(QString(j.c_str()));
    }
    form.addRow(&labelFile);
    form.addRow(&boxFile);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    int status = dialog.exec();
    if (status == QDialog::Accepted) {
        askTestFile(win, boxFile.itemText(boxFile.currentIndex()), file, value);
    } else if (status == QDialog::Rejected) {
        rejected(win);
    }
}

void Project::askTestFunction(QMainWindow *win, const QString &value)
{
    QDialog dialog(win);
    QFormLayout form(&dialog);
    QComboBox boxFile;
    QLabel labelFile("Choose a file");

    for (const auto &e: _folder.getFiles())
        boxFile.addItem(QString(e.first.c_str()));
    form.addRow(&labelFile);
    form.addRow(&boxFile);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    int status = dialog.exec();
    if (status == QDialog::Accepted) {
        addTestExistFile(win, boxFile.itemText(boxFile.currentIndex()), value);
    } else if (status == QDialog::Rejected) {
        rejected(win);
    }
}

void Project::askTestParams(QMainWindow *win)
{
    QDialog dialog(win);
    QFormLayout form(&dialog);
    QComboBox boxFile;
    QLabel labelFile("Choose a file");

    boxFile.addItem("New file");
    for (const auto &e: _tests)
        boxFile.addItem(QString(e.first.c_str()));
    form.addRow(&labelFile);
    form.addRow(&boxFile);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    int status = dialog.exec();
    if (status == QDialog::Accepted) {
        askTestFunction(win, boxFile.itemText(boxFile.currentIndex()));
    } else if (status == QDialog::Rejected) {
        rejected(win);
    }
}

void Project::addTest(QMainWindow *win)
{
    char buffer[1048] = {0};

    if (_filepath.empty()) {
        QMessageBox::warning(win, "Error", "Project is unintialized");
        return;
    }
    getcwd(buffer, 1048);
    if (chdir(_filepath.c_str()) == -1)
        throw Errors::DirectoryError("can't open" + _filepath, "");
    if (mkdir("tests", 0777) == -1 && errno != EEXIST) {
        perror("mkdir");
        throw Errors::DirectoryError("can't open tests directory", "");
    }
    std::string tmp(_filepath + "tests");
    if (chdir(tmp.c_str()) == -1)
        throw Errors::DirectoryError("can't open" + tmp, "");
    try {
        askTestParams(win);
    }   catch (const Errors::CompilingError &e) {
        throw e;
    } catch (const Errors::DirectoryError &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
    chdir(buffer);
}

void Project::generateSrcFiles(const std::string &fileNotEq)
{
    Reader _reader(_filepath);
    std::ofstream file(_filepath + "/tests/" + "Makefile");
    QDir dirName((_filepath + "/tests/").c_str());
    std::cout << dirName.currentPath().toUtf8().constData() << std::endl;
    int i = 0;

    file << "SRC\t=";
    for (struct dirent *all = _reader.getAll(); all; all = _reader.getAll(), ++i) {
        std::string tmp(all->d_name);
        if (tmp.find(".c") == tmp.npos || tmp.find(".cpp") != tmp.npos || tmp == fileNotEq)
            continue;
        if (i == 0)
            file << "\t\t" + std::string(dirName.relativeFilePath(_reader.getPath().c_str()).toUtf8().constData()) + "\t\\" << std::endl;
        else
            file << "\t\t\t\t" + std::string(dirName.relativeFilePath(_reader.getPath().c_str()).toUtf8().constData()) + "\t\\" << std::endl;
    }
    file << std::endl << "OBJ\t=\t$(SRC:.c=.o)" << std::endl;
//    file << std::endl << "UNIT\t=";
//    for (const auto &e: _tests) {
//        file << "\t\t" << e.first << "\t\\" << std::endl;
//    }
    file << std::endl << std::endl;
    file << "TARGET\t=\t" << "unit_tests" << std::endl;
    file << std::endl << "tests_run: $(TARGET)" << std::endl << std::endl << "$(TARGET) : $(OBJ)" << std::endl;
    file << "\t$(CC) -o $(TARGET) $(OBJ) --coverage -lcriterion" << std::endl;
    file << "\t./unit_tests" << std::endl;
    file << "clean: " << std::endl;
    file << "\t$(RM) $(OBJ)" << std::endl << "\t$(RM) *.gcda" << std::endl << "\t$(RM) *.gcno" <<std::endl;
    file << std::endl << "fclean: clean" << std::endl;
    file << "\t$(RM) $(TARGET)" << std::endl;
    file << std::endl << "re: fclean tests_run" << std::endl;
    file << std::endl << ".PHONY: clean fclean re tests_run" << std::endl;
    file.close();
}

void Project::assistGenMake(QMainWindow *win)
{
    QString fileName(QInputDialog::getText(win, "Main", "Enter file where is located your main function"));
    generateSrcFiles(fileName.toUtf8().constData());
}

void Project::generateMakefile(QMainWindow *win)
{
    char buffer[1048] = {0};

    if (_filepath.empty()) {
        QMessageBox::warning(win, "Error", "Project is unintialized");
        return;
    }
    getcwd(buffer, 1048);
    if (chdir(_filepath.c_str()) == -1)
        throw Errors::DirectoryError("can't open" + _filepath, "");
    if (mkdir("tests", 0777) == -1 && errno != EEXIST) {
        perror("mkdir");
        throw Errors::DirectoryError("can't open tests directory", "");
    }
    std::string tmp(_filepath + "tests");
    if (chdir(tmp.c_str()) == -1)
        throw Errors::DirectoryError("can't open" + tmp, "");
    try {
        assistGenMake(win);
    }   catch (const Errors::CompilingError &e) {
        throw e;
    } catch (const Errors::DirectoryError &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
    chdir(buffer);
}
