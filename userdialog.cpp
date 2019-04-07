#include "userdialog.h"
#include "ui_userdialog.h"
#include <iostream>
using namespace std;

UserDialog::UserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDialog)
{
    ui->setupUi(this);
    setWindowTitle("User Admin");
    //setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint);
    cout << "User dialog object created." << endl;
}

UserDialog::~UserDialog()
{
    delete ui;
    cout << "User Dialog object removed." << endl;
}
