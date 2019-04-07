#ifndef DATABASEWINDOW_H
#define DATABASEWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include "database.h"

namespace Ui {
class DatabaseWindow;
}

class DatabaseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DatabaseWindow(QWidget *parent = nullptr);
    ~DatabaseWindow();

signals:
    void connEstablished(bool isit);

private slots:
    void on_connectDbBtn_clicked();
    void on_closeDbBtn_clicked();
    void on_refreshBtn_clicked();
    void on_importBtn_clicked();

private:
    Ui::DatabaseWindow *ui;
    Database dbase;
    QString host;
    QString dbname;
    QString uname;
    int port;
    QString pw;
};

#endif // DATABASEWINDOW_H
