/**
 * @package QTWhiteSpaceManager
 * @module DatabaseWindow.h
 * Header file of DatabaseWindow class.
 * ----------------------------
 * Updates
 * @date: 18/04/2019
 * @abstract: Added comments, indented code
 * @author:
 */

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
    void connEstablished(bool value);

private slots:
    void on_connectDbBtn_clicked();
    void on_closeDbBtn_clicked();
    void on_refreshBtn_clicked();
    void on_helpBtn_clicked();

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
