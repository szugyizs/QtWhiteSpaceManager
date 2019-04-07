#include <QApplication>
#include "transmitteradmin.h"
#include "databasewindow.h"
#include "userdialog.h"
#include "QDesktopWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseWindow dw;
    TransmitterAdmin ta;
//    UserAdmin ua;
//    MapWindow mw;

    dw.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignTop, dw.size(), a.desktop()->availableGeometry()));
    ta.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignBottom, ta.size(), a.desktop()->availableGeometry()));
//    ua->setGeometry(QStyle::alignedRect(Qt::RightToLeft, Qt::AlignTop, ua.size(), a->desktop()->availableGeometry()));
//    mw->setGeometry(QStyle::alignedRect(Qt::RightToLeft, Qt::AlignBottom, dialog.size(), a->desktop()->availableGeometry()));

    dw.show();
    ta.show();
    return a.exec();
}


