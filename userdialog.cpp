#include "userdialog.h"
#include "ui_userdialog.h"

UserDialog::UserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDialog)
{
    ui->setupUi(this);
    setWindowTitle("User Admin");
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint);
}

UserDialog::~UserDialog()
{
    delete ui;
}
