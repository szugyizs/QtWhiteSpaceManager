#include "starter.h"
#include "ui_starter.h"
#include "transmitterdialog.h"
#include "databasedialog.h"
#include "userdialog.h"

Starter::Starter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Starter)
{
    ui->setupUi(this);
    //connect(startBtn,SIGNAL(clicked(),this,SLOT(on_Button_clicked())));
}

Starter::~Starter()
{
    delete ui;
}

bool clicked = false;

void Starter::on_startBtn_clicked()
{

    TransmitterDialog transmitterdialog;
    DatabaseDialog databasedialog;
    UserDialog userdialog;
    if (!clicked){
        databasedialog.show();
        transmitterdialog.show();
        userdialog.show();
    }
    else {
        transmitterdialog.~TransmitterDialog();
        databasedialog.~DatabaseDialog();
        userdialog.~UserDialog();
    }
    clicked=!clicked;
}
