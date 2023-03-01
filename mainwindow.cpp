#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    this->setCentralWidget(this->ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete this->ui;
}


void MainWindow::on_actionNew_triggered()
{
    this->currentFilePath.clear();
    this->ui->textEdit->setText(QString());

}


void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(filePath);
    this->currentFilePath = filePath;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"notepad", "cannot open file '" + filePath +  "'.Error'" + file.errorString() + "'.");
        return;
    }

     this->currentFilePath = filePath;

    this->setWindowTitle(filePath);
    QTextStream in(&file);
    QString content = in.readAll();
    this->ui->textEdit->setText(content);
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this,"save as");
    QFile file(filePath);

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"notepad", "cannot save file '" + filePath +  "'.Error'" + file.errorString() + "'.");
        return;
    }
     this->currentFilePath = filePath;
    this->setWindowTitle(filePath);
    QTextStream out(&file);
    QString content = this->ui->textEdit->toPlainText();//in.readAll();
        out << content ;
        file.close();
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionCut_triggered()
{
    this->ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    this->ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    this->ui->textEdit->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    this->ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    this->ui->textEdit->redo();
}

