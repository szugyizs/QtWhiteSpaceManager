#ifndef TRANSMITTERADMIN_H
#define TRANSMITTERADMIN_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "transmitter.h"
#include "databasewindow.h"

namespace Ui {
class TransmitterAdmin;
}

class TransmitterAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit TransmitterAdmin(QWidget *parent = nullptr);
    ~TransmitterAdmin();

private slots:
    void on_addBtnManual_clicked();

    void on_clearBtnCreate_clicked();

    void on_browseFile_clicked();

    void on_addAllBtn_clicked();

    void on_toolBox_currentChanged(int index);

    void on_clearFileBtn_clicked();

    void on_ModifyBtn_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tmitDropDown_currentIndexChanged(const QString &arg1);

    void on_tExportBtn_clicked();

    void on_removeBtn_clicked();

    void on_clrSelectBtn_clicked();

    void on_helpBtn_clicked();

    int confirmPopUp(QString values);

private:
    Ui::TransmitterAdmin *ui;
    QString ID_;
    int radius_;
    double power_;
    int x_;
    int y_;
};

class CreateTab : public QWidget{
    Q_OBJECT
public:
    explicit CreateTab(QWidget *parent = nullptr);
};

class ModifyTab : public QWidget{
    Q_OBJECT
public:
    explicit ModifyTab(QWidget *parent = nullptr);
};

class RemoveTab : public QWidget{
    Q_OBJECT
public:
    explicit RemoveTab(QWidget *parent = nullptr);
};

class ListTab : public QWidget{
    Q_OBJECT
public:
    explicit ListTab(QWidget *parent = nullptr);
};

#endif // TRANSMITTERADMIN_H
