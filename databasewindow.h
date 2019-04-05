#ifndef DATABASEWINDOW_H
#define DATABASEWINDOW_H

#include <QMainWindow>

namespace Ui {
class DatabaseWindow;
}

class DatabaseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DatabaseWindow(QWidget *parent = nullptr);
    ~DatabaseWindow();

private:
    Ui::DatabaseWindow *ui;
};

#endif // DATABASEWINDOW_H
