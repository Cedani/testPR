#ifndef TESTPR_HPP
#define TESTPR_HPP

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDialog>
#include <QInputDialog>
#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include "Project.hpp"
#include "Folder.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class TestPR; }
QT_END_NAMESPACE

class TestPR : public QMainWindow
{
    Q_OBJECT

public:
    TestPR(QWidget *parent = nullptr);
    ~TestPR();

private:
    void updateDisplayFiles();
    Ui::TestPR *ui;
    Project _project;
    QString _displayFiles;
//    std::vector<Project> _projects;

private slots:
    void on_actionNew_triggered();
    void on_addFile_clicked();
    void on_addFunction_clicked();
    void acceptAddFunction(QLineEdit *, QLineEdit *);
    void rejectedAddFunction();
    void on_addTest_clicked();
    void on_genMake_clicked();
};
#endif // TESTPR_HPP
