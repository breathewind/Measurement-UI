/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 19/02/2019
 * Last modify date: 07/03/2019
 *      Description: Command Panel dialog of MeasurementUI application.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   6XX - View control functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#include "View/inc/c203_command_panel.h"
#include "ui_c203_command_panel.h"

/******************************************************************************
 *             Name: Command_Panel
 *      Function ID: 000
 *      Create date: 19/02/2019
 * Last modify date: 07/03/2019
 *      Description: Construction function.
 ******************************************************************************/
Command_Panel::Command_Panel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Command_Panel)
{
    ui->setupUi(this);

    setWindowTitle("Command Panel");

    ui->radioButton_SW->setChecked(true);
    ui->radioButton_CC->setChecked(false);

    ui->radioButton_TCC->setChecked(true);
    ui->radioButton_TOCV->setChecked(false);

    setFixedSize(480,465);
}

/******************************************************************************
 *             Name: ~Command_Panel
 *      Function ID: 001
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Destruction function.
 ******************************************************************************/
Command_Panel::~Command_Panel()
{
    delete ui;
}

/******************************************************************************
 *             Name: showDialog
 *      Function ID: 300
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Show window and record its postion.
 ******************************************************************************/
void Command_Panel::showDialog()
{
    show();
    /** Let system remember dialog current position. */
    move(pos().x(), pos().y());
}

/******************************************************************************
 *             Name: getDischarge_information
 *      Function ID: 800
 *      Create date: 06/03/2019
 * Last modify date: 06/03/2019
 *      Description: Get discharge type and information.
 ******************************************************************************/
QList<double> Command_Panel::getDischarge_information()
{
    QList<double> information;
    if(ui->radioButton_SW->isChecked()){
        information.append(COMMNAD_PANEL_DISCHARGE_TYPE_SQUARE_WAVE);
        information.append(ui->lineEdit_SW_min_current->text().toDouble());
        information.append(ui->lineEdit_SW_max_current->text().toDouble());
        information.append(ui->lineEdit_SW_period->text().toDouble()*1000);
    } else {
        information.append(COMMNAD_PANEL_DISCHARGE_TYPE_CONSTANT_CURRENT);
        information.append(ui->lineEdit_CC_discharge_current->text().toDouble());
    }
    return information;
}

/******************************************************************************
 *             Name: getTermination_information
 *      Function ID: 801
 *      Create date: 06/03/2019
 * Last modify date: 06/03/2019
 *      Description: Get termination type and information.
 ******************************************************************************/
QList<double> Command_Panel::getTermination_information()
{
    QList<double> information;
    if(ui->radioButton_TCC->isChecked()){
        information.append(COMMAND_PANEL_TERMINATION_TYPE_COULOMB_COUNTING);
        information.append(ui->lineEdit_TCC_target_coulomb->text().toDouble());
    } else {
        information.append(COMMAND_PANEL_TERMINATION_TYPE_OCV);
        information.append(ui->lineEdit_TOCV_target_OCV->text().toDouble());
    }
    return information;
}

/******************************************************************************
 *             Name: getBattery_information
 *      Function ID: 802
 *      Create date: 06/03/2019
 * Last modify date: 06/03/2019
 *      Description: Get battery type and information.
 ******************************************************************************/
double Command_Panel::getBattery_information()
{
    return ui->lineEdit_rated_capacity->text().toDouble();
}
