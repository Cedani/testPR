/*
** EPITECH PROJECT, 2021
** testPR
** File description:
** Project
*/

#ifndef PROJECT_HPP_
#define PROJECT_HPP_
#include <QMainWindow>
#include <QInputDialog>
#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QMessageBox>
#include "Reader.hpp"
#include "Interpreter.hpp"
#include "Parser.hpp"
#include "Folder.hpp"
#include "Error.hpp"
#include "ATest.hpp"
#include <thread>
#include <QDir>

class Project {
    public:
        Project();
        Project(const Project &);
        ~Project();

        void displayFiles();
        const Folder &getFolder() const;
        void addFiles(const std::string &);
        void initProject(const std::string &, const std::string &);
        void addFunction(const std::string &, const std::string &);
        void addTest(QMainWindow *);
        void initFile(const std::string &, const std::string &);
        void generateMakefile(QMainWindow *);
        void generateSrcFiles(const std::string &);
    private:
        void assistGenMake(QMainWindow *);
        void askTestFunction(QMainWindow *, const QString &);
        void askTestFile(QMainWindow *, QString, QString file, QString value);
        void rejected(QMainWindow *);
//        void addTestNewFile();
        void addTestExistFile(QMainWindow *, QString, QString file);
        void askTestParams(QMainWindow *);
        Interpreter _interp;
        Folder _folder;
        std::vector<std::thread> _thread;
        std::string _filepath;
        std::string _lineCompil;
        std::unordered_map<std::string, std::vector<ATest>> _tests;
};

#endif /* !PROJECT_HPP_ */
