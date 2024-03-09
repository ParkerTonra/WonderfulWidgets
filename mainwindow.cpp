#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "converter.h"
#include <QApplication>
#include <QPalette>
#include <QStyle>





void MainWindow::openCalculator() {
    Converter *calc = new Converter();
    calc->show();

}

//void MainWindow::privateFunction2() {
////TODO
//}

//constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) //inherit from main window base
    , ui(new Ui::MainWindow) //attatch to the UI file
{
    ui->setupUi(this);
    connect(ui->openCalculatorButton, &QPushButton::clicked, this, &MainWindow::openCalculator); // connect dark mode to toggleDarkModeButton
}

MainWindow::~MainWindow()
{
    delete ui;
}
