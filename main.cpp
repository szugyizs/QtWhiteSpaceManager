//#include "tvwsmodel.h"
//#include "tvwspoint.h"
#include "databasewindow.h"
#include "transmitteradmin.h"
#include "useradmin.h"
#include "mapdialog.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

//    NavaidsModel model;
//    //model.readFromCSV("C:\\Users\\Zsuzsi\\Desktop\\cctv1.csv");
//    model.addNavaidsPoint(NavaidsPoint("glasgow", 55.86,-4.251, "NG"));//from file
//    QQmlApplicationEngine engine;
//    engine.rootContext()->setContextProperty("navaidsModel", &model);
//    engine.load(QUrl(QLatin1String("qrc:/mapdata.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

    //qmlRegisterType<NavaidsModel>("NavModel", 1, 0, "NavaidsModel");

    DatabaseWindow dw;
    TransmitterAdmin ta;
    UserAdmin ua;
    MapDialog md;

    dw.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignTop, dw.size(), app.desktop()->availableGeometry()));
    ta.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignBottom, ta.size(), app.desktop()->availableGeometry()));
    ua.setGeometry(QStyle::alignedRect(Qt::RightToLeft, Qt::AlignBottom, ua.size(), app.desktop()->availableGeometry()));
    md.setGeometry(QStyle::alignedRect(Qt::RightToLeft, Qt::AlignTop, md.size(), app.desktop()->availableGeometry()));

    dw.show();
    ta.show();
    ua.show();
    md.show();

    return app.exec();
}
