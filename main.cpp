#include "databasewindow.h"
#include "transmitteradmin.h"
#include "useradmin.h"
#include "tvwsmodel.h"
#include "tvwspoint.h"

#include <QQuickWidget>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    qmlRegisterType<NavaidsModel>("NavModel", 1, 0, "NavModel");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    DatabaseWindow dw;
    TransmitterAdmin ta;
    UserAdmin ua;

    dw.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignTop, dw.size(), app.desktop()->availableGeometry()));
    ta.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignBottom, ta.size(), app.desktop()->availableGeometry()));
    ua.setGeometry(QStyle::alignedRect(Qt::RightToLeft, Qt::AlignBottom, ua.size(), app.desktop()->availableGeometry()));

    dw.show();
    ta.show();
    ua.show();

//    NavaidsModel model;
//    model.readFromCSV("C:\\Users\\Zsuzsi\\Desktop\\cctv1.csv");
//    model.addNavaidsPoint(NavaidsPoint("glasgow", 55.86,-4.251, "NG"));//from file

    //QQmlApplicationEngine engine;
    // //engine.rootContext()->setContextProperty("navaidsModel", &model);
    //engine.load(QUrl(QLatin1String("qrc:/mapdata.qml")));
    //if (engine.rootObjects().isEmpty())
    //    return -1;

    return app.exec();
}
