#ifndef USERADMIN_H
#define USERADMIN_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "User.h"
#include "databasewindow.h"

namespace Ui {
class UserAdmin;
}

class UserAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit UserAdmin(QWidget *parent = nullptr);
    ~UserAdmin();

private slots:
    void on_addBtnManual_2_clicked();

    void on_clearBtnCreate_2_clicked();

    void on_browseFile_2_clicked();

    void on_addAllBtn_2_clicked();

    void on_toolBox_2_currentChanged(int index);

    void on_clearFileBtn_2_clicked();

    void on_ModifyBtn_2_clicked();

    void on_tabWidget_2_currentChanged(int index);

    void on_userDropDown_currentIndexChanged(const QString &arg1);

private:
    Ui::UserAdmin *ui;
    QString ID_;
    int radius_;
    double power_;
    int x_;
    int y_;
};

class CreateTab_2 : public QWidget{
    Q_OBJECT
public:
    explicit CreateTab_2(QWidget *parent = nullptr);
};

class ModifyTab_2 : public QWidget{
    Q_OBJECT
public:
    explicit ModifyTab_2(QWidget *parent = nullptr);
};

class ListTab_2 : public QWidget{
    Q_OBJECT
public:
    explicit ListTab_2(QWidget *parent = nullptr);
};

#endif // USERADMIN_H
