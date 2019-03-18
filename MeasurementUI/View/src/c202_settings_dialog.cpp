/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 19/02/2019
 * Last modify date: 18/03/2019
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
 * Last modify date: 15/03/2019
 *      Description: Construction function.
 ******************************************************************************/
Settings_Dialog::Settings_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings_Dialog)
{
    ui->setupUi(this);

    setWindowTitle("Settings");
    setFixedSize(480, 556);
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
 *             Name: setCurrent_frame
 *      Function ID: 002
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Set current frame.
 ******************************************************************************/
void Settings_Dialog::setCurrent_frame(QWidget *frame_to_be_set)
{
    ui->verticalLayout_settings->addWidget(frame_to_be_set);
}

/******************************************************************************
 *             Name: showDialog
 *      Function ID: 300
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Show window and record its postion.
 ******************************************************************************/
void Settings_Dialog::showDialog()
{
    show();
    /** Let system remember dialog current position. */
    move(pos().x(), pos().y());
}

/******************************************************************************
 *             Name: on_pushButton_Apply_clicked
 *      Function ID: 700
 *      Create date: 20/02/2019
 * Last modify date: 18/03/2019
 *      Description: Slot for Apply pushbutton clicked.
 ******************************************************************************/
void Settings_Dialog::on_pushButton_Apply_clicked()
{
    emit signal_accept_button_clicked();
}
