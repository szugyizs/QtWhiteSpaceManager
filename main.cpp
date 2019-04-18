/**
 * @package QTWhiteSpaceManager
 * @module main.cpp
 * The source file containing the main function of the application.
 * ----------------------------
 * Updates
 * @date: 18/04/2019
 * @abstract: Added comments, indented code
 * @author:
 */

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

    /*Positioning the GUIs so that they do not overlap*/
    dw.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignTop, dw.size(), app.desktop()->availableGeometry()));
    ta.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignBottom, ta.size(), app.desktop()->availableGeometry()));
    ua.setGeometry(QStyle::alignedRect(Qt::RightToLeft, Qt::AlignBottom, ua.size(), app.desktop()->availableGeometry()));

    dw.show();
    ta.show();
    ua.show();

    TVModel model1;
    TVModel model2;

    /*initialise Map and System power button*/
    QQmlApplicationEngine engine, engine1;
    engine.rootContext()->setContextProperty("TVModel1", &model1);
    engine.rootContext()->setContextProperty("TVModel2", &model2);
    engine.load(QUrl(QLatin1String("qrc:/mapdata.qml")));
    engine1.load(QUrl(QLatin1String("qrc:/sysmgr.qml")));

    return app.exec();
}
