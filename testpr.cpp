#include "testpr.hpp"
#include "ui_testpr.h"

TestPR::TestPR(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TestPR)
{
    ui->setupUi(this);
    ui->statusbar->hide();
    ui->plainTextEdit->setReadOnly(true);
}

TestPR::~TestPR()
{
    delete ui;
}

void TestPR::updateDisplayFiles()
{
    Folder folder = _project.getFolder();
    QString displayFIles;
    for (const auto &e: folder.getFiles()) {
        displayFIles.append(QString::fromStdString(e.first + ":\n"));
        for (const auto &f: e.second) {
            displayFIles.append(QString::fromStdString(f + "\n"));
        }
    }
    ui->plainTextEdit->document()->setPlainText(displayFIles);
    _displayFiles = displayFIles;
}

void TestPR::on_actionNew_triggered()
{
    QString filename(QFileDialog::getExistingDirectory(this, "Open the Folder"));
    QString line(QInputDialog::getMultiLineText(this, "Compilation", "Enter used command for compilation of the project"));

    try {
        _project.initProject(filename.toUtf8().constData(), line.toUtf8().constData());
    }  catch (const Errors::CompilingError &e) {
        QMessageBox::warning(this, "Error", e.what());
        return;
    } catch (const Errors::DirectoryError &e) {
        QMessageBox::warning(this, "Error", e.what());
        return;
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
        return;
    }
    updateDisplayFiles();
}

void TestPR::on_addFile_clicked()
{
    QString filename(QFileDialog::getOpenFileName(this, "Open a file"));

    try {
        _project.addFiles(filename.toUtf8().constData());
    }  catch (const Errors::CompilingError &e) {
        QMessageBox::warning(this, "Error", e.what());
        return;
    } catch (const Errors::DirectoryError &e) {
        QMessageBox::warning(this, "Error", e.what());
        return;
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
        return;
    }
    updateDisplayFiles();
}

void TestPR::acceptAddFunction(QLineEdit *filename, QLineEdit *function)
{
    try {
        QString file = filename->text();
        QString func = function->text();
        if (file.size() == 0 || func.size() == 0)
            throw Errors::DirectoryError("Field empty", "");
        _project.addFunction(file.toUtf8().constData(), func.toUtf8().constData());
        updateDisplayFiles();
    } catch (const Errors::CompilingError &e) {
        QMessageBox::warning(this, "Error", e.what());
        return;
    } catch (const Errors::DirectoryError &e) {
        QMessageBox::warning(this, "Error", e.what());
        return;
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
        return;
    }
}

void TestPR::rejectedAddFunction()
{
    QMessageBox::warning(this, "Error", "didn't add functions");
}

void TestPR::on_addFunction_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    QLabel *labelQuestion = new QLabel("Enter filename and function");
    QLineEdit *filename = new QLineEdit(&dialog);
    QLineEdit *function = new QLineEdit(&dialog);

    form.addRow(labelQuestion);
    form.addRow("Enter filename", filename);
    form.addRow("Enter function", function);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    int status = dialog.exec();
    if (status == QDialog::Accepted)
        acceptAddFunction(filename, function);
    else if (status == QDialog::Rejected)
        rejectedAddFunction();
    delete labelQuestion;
    delete filename;
    delete function;
}
void TestPR::on_addTest_clicked()
{
    try {
        _project.addTest(this);
    } catch (const Errors::CompilingError &e) {
        QMessageBox::warning(this, "Error", e.what());
        return;
    } catch (const Errors::DirectoryError &e) {
        QMessageBox::warning(this, "Error", e.what());
        return;
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
        return;
    }
}

void TestPR::on_genMake_clicked()
{
    try {
        _project.generateMakefile(this);
    }catch (const Errors::CompilingError &e) {
        QMessageBox::warning(this, "Error", e.what());
        return;
    } catch (const Errors::DirectoryError &e) {
        QMessageBox::warning(this, "Error", e.what());
        return;
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
        return;
    }
}
