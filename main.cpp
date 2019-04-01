#include <QApplication>
#include "starter.h"
#include "transmitterdialog.h"
#include "databasedialog.h"
#include "userdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    Starter sysStart;
    //    sysStart.show();
    TransmitterDialog transmitterdialog;
    DatabaseDialog databasedialog;
    UserDialog userdialog;
    databasedialog.show();
    transmitterdialog.show();
    userdialog.show();
    return a.exec();
}
