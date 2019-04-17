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


    TVModel model1;
    TVModel model2;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("TVModel1", &model1);
    engine.rootContext()->setContextProperty("TVModel2", &model2);
    engine.load(QUrl(QLatin1String("qrc:/mapdata.qml")));

    return app.exec();
}
