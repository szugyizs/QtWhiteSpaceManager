/**
 * @package QTWhiteSpaceManager
 * @module HelpDialog.cpp
 * The source file of the class detemining the operations of the help dialog GUI.
 * ----------------------------
 * Updates
 * @date: 18/04/2019
 * @abstract: Added comments, indented code
 * @author:
 */

#include "helpdialog.h"
#include "ui_helpdialog.h"

/**
  * Constructor for a HelpDialog object.
  * @param parent: the parent of the HelpDialog
  */
HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
}

/**
  * Destructor for the HelpDialog object.
  */
HelpDialog::~HelpDialog()
{
    delete ui;
}

/**
  * Setting the text of the Dialog body.
  * @param helpTxt: the text of the Dialog body
  */
void HelpDialog::setHelpText(QString helpTxt){
    ui->helpTxtLbl->setText(helpTxt);
}
