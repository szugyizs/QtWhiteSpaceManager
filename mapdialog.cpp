#include "mapdialog.h"
#include "ui_mapdialog.h"

MapDialog::MapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapDialog)
{
    setWindowTitle("Map");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
}

MapDialog::~MapDialog()
{
    delete ui;
}

void MapDialog::on_pushButton_clicked()
{

}

void MapDialog::on_pushButton_2_clicked()
{

}
