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
#include "View/inc/c202_settings_dialog.h"
#include "ui_c202_settings_dialog.h"

/******************************************************************************
 *             Name: Settings_Dialog
 *      Function ID: 000
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Construction function.
 ******************************************************************************/
Settings_Dialog::Settings_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings_Dialog)
{
    ui->setupUi(this);

//    _current_pos.setX(0);
//    _current_pos.setY(0);
//    _first_time_show = true;
}

/******************************************************************************
 *             Name: ~Settings_Dialog
 *      Function ID: 001
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Destruction function.
 ******************************************************************************/
Settings_Dialog::~Settings_Dialog()
{
    delete ui;
}

/******************************************************************************
 *             Name: on_pushButton_Apply_clicked
 *      Function ID: 700
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Slot for Apply pushbutton clicked.
 ******************************************************************************/
void Settings_Dialog::on_pushButton_Apply_clicked()
{

}

/******************************************************************************
 *             Name: accept
 *      Function ID: 790
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Rewrite slot accect().
 ******************************************************************************/
void Settings_Dialog::accept()
{
#ifdef SETTINGS_DIALOG_DEBUG
    qDebug() << "+ Settings_Dialog: accept";
#endif
    emit accepted();
    hide();
}

/******************************************************************************
 *             Name: reject
 *      Function ID: 791
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Rewrite slot reject().
 ******************************************************************************/
void Settings_Dialog::reject()
{
#ifdef SETTINGS_DIALOG_DEBUG
    qDebug() << "+ Settings_Dialog: reject";
#endif
    emit rejected();
    hide();
}
