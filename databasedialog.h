#ifndef DATABASEDIALOG_H
#define DATABASEDIALOG_H

#include <QDialog>
#include "database.h"

namespace Ui {
class DatabaseDialog;
}

class DatabaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseDialog(QWidget *parent = nullptr);
    ~DatabaseDialog();
    Database dbase;

private slots:
    void on_createDbBtn_clicked();

    void on_dropDbBtn_clicked();

private:
    Ui::DatabaseDialog *ui;
};

#endif // DATABASEDIALOG_H
