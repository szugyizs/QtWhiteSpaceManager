#ifndef TRANSMITTERDIALOG_H
#define TRANSMITTERDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>

namespace Ui {
class TransmitterDialog;
}

class TransmitterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransmitterDialog(QWidget *parent = nullptr);
    ~TransmitterDialog();

private slots:
    void on_addBtnManual_clicked();

    void on_clearBtnCreate_clicked();

    void on_browseFile_clicked();

    void on_fileNameEdit_returnPressed();

    void on_addAllBtn_clicked();

    void on_toolBox_currentChanged(int index);

    void on_clearFileBtn_clicked();

    void on_ModifyBtn_clicked();

    void on_tmitDropDown_currentIndexChanged(int index);

private:
    Ui::TransmitterDialog *ui;
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

class ListTab : public QWidget{
    Q_OBJECT
public:
    explicit ListTab(QWidget *parent = nullptr);
};

#endif // TRANSMITTERDIALOG_H
