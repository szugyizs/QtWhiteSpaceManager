#ifndef STARTER_H
#define STARTER_H

#include <QWidget>

namespace Ui {
class Starter;
}

class Starter : public QWidget
{
    Q_OBJECT

public:
    explicit Starter(QWidget *parent = nullptr);
    ~Starter();

private slots:
    void on_startBtn_clicked();

private:
    Ui::Starter *ui;
};

#endif // STARTER_H
