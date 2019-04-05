#include "databasewindow.h"
#include "ui_databasewindow.h"

DatabaseWindow::DatabaseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DatabaseWindow)
{
    ui->setupUi(this);
}

DatabaseWindow::~DatabaseWindow()
{
    delete ui;
}
