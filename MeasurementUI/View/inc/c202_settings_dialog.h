/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 19/02/2019
 * Last modify date: 20/02/2019
 *      Description: Settings dialog of MeasurementUI application.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   6XX - View control functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#ifndef C202_SETTINGS_DIALOG_H
#define C202_SETTINGS_DIALOG_H

#include <QDialog>

#include "h000_global_parameters.h"

namespace Ui {
class Settings_Dialog;
}

class Settings_Dialog : public QDialog
{
    Q_OBJECT

public:
    /** Function 000: Construction function. */
    explicit Settings_Dialog(QWidget *parent = nullptr);
    /** Function 001: Destruction function. */
    ~Settings_Dialog();

    /** Function 300: Show window and record its postion. */
    void showDialog();

private slots:
    /** Function 700: Slot for Apply pushbutton clicked. */
    void on_pushButton_Apply_clicked();

    /** Function 790: Rewrite slot accect(). */
    void accept();
    /** Function 791: Rewrite slot reject(). */
    void reject();

private:
    Ui::Settings_Dialog *ui;

//signals:
//    void
};

#endif // C202_SETTINGS_DIALOG_H
