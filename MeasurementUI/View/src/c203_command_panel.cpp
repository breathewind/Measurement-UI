/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 19/02/2019
 * Last modify date: 18/03/2019
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
 * Last modify date: 18/03/2019
 *      Description: Construction function.
 ******************************************************************************/
Command_Panel::Command_Panel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Command_Panel)
{
    ui->setupUi(this);

    setWindowTitle("Command Panel");

    setFixedSize(480,540);
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
 *             Name: setLogic_type
 *      Function ID: 002
 *      Create date: 18/03/2019
 * Last modify date: 18/03/2019
 *      Description: Set display logic for discharge type.
 ******************************************************************************/
void Command_Panel::setLogic_type(int type)
{
    if(type == COMMNAD_PANEL_DISCHARGE_TYPE_SQUARE_WAVE){
        ui->groupBox_SW->setEnabled(true);
        ui->groupBox_CC->setEnabled(false);
    } else {
        ui->groupBox_SW->setEnabled(false);
        ui->groupBox_CC->setEnabled(true);
    }
}

/******************************************************************************
 *             Name: setLogic_option
 *      Function ID: 003
 *      Create date: 18/03/2019
 * Last modify date: 18/03/2019
 *      Description: Set display logic for stop discharging options.
 ******************************************************************************/
void Command_Panel::setLogic_option(int option)
{
    if(option == COMMAND_PANEL_TERMINATION_TYPE_COULOMB_COUNTING){
        ui->groupBox_TCC->setEnabled(true);
        ui->groupBox_TOCV->setEnabled(false);
    } else {
        ui->groupBox_TCC->setEnabled(false);
        ui->groupBox_TOCV->setEnabled(true);
    }
}

/******************************************************************************
 *             Name: setLogic_save_file
 *      Function ID: 004
 *      Create date: 18/03/2019
 * Last modify date: 18/03/2019
 *      Description: Set display logic for save file.
 ******************************************************************************/
void Command_Panel::setLogic_save_file(int save_file_flag)
{
    if(save_file_flag == COMMAND_PANEL_SAVE_FILE_CHECKED){
        ui->groupBox_save_file->setEnabled(true);
    } else {
        ui->groupBox_save_file->setEnabled(false);
    }
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
 *             Name: hideDialog
 *      Function ID: 301
 *      Create date: 15/03/2019
 * Last modify date: 15/03/2019
 *      Description: Hide window.
 ******************************************************************************/
void Command_Panel::hideDialog()
{
    hide();
}

/******************************************************************************
 *             Name: setDefault
 *      Function ID: 302
 *      Create date: 18/03/2019
 * Last modify date: 18/03/2019
 *      Description: Set all options in command window as default value.
 ******************************************************************************/
void Command_Panel::setDefault(QString output_file)
{
    /** Initialize discharge type */
    ui->lineEdit_SW_min_current->setText(QString::number(COMMAND_PANEL_DEFAULT_SW_MIN_I));
    ui->lineEdit_SW_max_current->setText(QString::number(COMMAND_PANEL_DEFAULT_SW_MAX_I));
    ui->lineEdit_SW_period->setText(QString::number(COMMAND_PANEL_DEFAULT_SW_PERIOD));
    ui->lineEdit_CC_discharge_current->setText(QString::number(COMMAND_PANEL_DEFAULT_CC_CURRENT));

    ui->radioButton_SW->setChecked(true);
    ui->radioButton_CC->setChecked(false);
    setLogic_type(COMMNAD_PANEL_DISCHARGE_TYPE_SQUARE_WAVE);

    /** Initialize stop discharging options */
    ui->lineEdit_TCC_target_coulomb->setText(QString::number(COMMAND_PANEL_DEFAULT_TCC_COULOMB));
    ui->lineEdit_TOCV_target_OCV->setText(QString::number(COMMAND_PANEL_DEFAULT_TOCV_OCV));

    ui->radioButton_TCC->setChecked(true);
    ui->radioButton_TOCV->setChecked(false);
    setLogic_option(COMMAND_PANEL_TERMINATION_TYPE_COULOMB_COUNTING);

    /** Initialize battery information */
    ui->lineEdit_rated_capacity->setText(QString::number(COMMAND_PANEL_DEFAULT_RATE_CAPACITY));

    /** Initialize save file */
    ui->lineEdit_file_path->setText(output_file);

    ui->checkBox_save_file->setChecked(true);
    setLogic_save_file(COMMAND_PANEL_SAVE_FILE_CHECKED);
}

/******************************************************************************
 *             Name: updateInformation
 *      Function ID: 303
 *      Create date: 18/03/2019
 * Last modify date: 18/03/2019
 *      Description: Update all options in command window.
 ******************************************************************************/
void Command_Panel::updateInformation(int type, double min_i, double max_i, double period, double current,
                                      int options, int coulomb, double ocv,
                                      int capacity,
                                      int save_file_checked, QString output_file)
{
    /** Update discharge type information */
    ui->lineEdit_SW_min_current->setText(QString::number(min_i));
    ui->lineEdit_SW_max_current->setText(QString::number(max_i));
    ui->lineEdit_SW_period->setText(QString::number(period));
    ui->lineEdit_CC_discharge_current->setText(QString::number(current));

    ui->radioButton_SW->setChecked(true);
    ui->radioButton_CC->setChecked(false);
    setLogic_type(type);

    /** Update stop discharging options information */
    ui->lineEdit_TCC_target_coulomb->setText(QString::number(coulomb));
    ui->lineEdit_TOCV_target_OCV->setText(QString::number(ocv));

    ui->radioButton_TCC->setChecked(true);
    ui->radioButton_TOCV->setChecked(false);
    setLogic_option(options);

    /** Update battery information information */
    ui->lineEdit_rated_capacity->setText(QString::number(capacity));

    /** Update save file information */
    ui->lineEdit_file_path->setText(output_file);

    ui->checkBox_save_file->setChecked(true);
    setLogic_save_file(save_file_checked);

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
