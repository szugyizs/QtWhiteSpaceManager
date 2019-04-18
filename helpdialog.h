/**
 * @package QTWhiteSpaceManager
 * @module HelpDialog.h
 * Header file for HelpDialog class.
 * ----------------------------
 * Updates
 * @date: 18/04/2019
 * @abstract: Added comments, indented code
 * @author:
 */

#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>

namespace Ui {
class HelpDialog;
}

class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDialog(QWidget *parent = nullptr);
    ~HelpDialog();
    void setHelpText(QString helpText);

private:
    Ui::HelpDialog *ui;
};

#endif // HELPDIALOG_H
