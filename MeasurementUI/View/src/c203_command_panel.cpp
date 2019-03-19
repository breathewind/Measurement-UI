/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 19/02/2019
 * Last modify date: 19/03/2019
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
 *             Name: setChecked_type
 *      Function ID: 002
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set check boxes for discharge type.
 ******************************************************************************/
void Command_Panel::setChecked_type(int type)
{
    if(type == COMMNAD_PANEL_DISCHARGE_TYPE_SQUARE_WAVE){
        ui->radioButton_SW->setChecked(true);
        ui->radioButton_CC->setChecked(false);
    } else {
        ui->radioButton_SW->setChecked(false);
        ui->radioButton_CC->setChecked(true);
    }
}

/******************************************************************************
 *             Name: setLogic_type
 *      Function ID: 003
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
 *             Name: setChecked_type
 *      Function ID: 004
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set check boxes for stop discharging options (termination
 *                   type).
 ******************************************************************************/
void Command_Panel::setChecked_option(int option)
{
    if(option == COMMAND_PANEL_TERMINATION_TYPE_COULOMB_COUNTING){
        ui->radioButton_TCC->setChecked(true);
        ui->radioButton_TOCV->setChecked(false);
    } else {
        ui->radioButton_TCC->setChecked(false);
        ui->radioButton_TOCV->setChecked(true);
    }
}

/******************************************************************************
 *             Name: setLogic_option
 *      Function ID: 005
 *      Create date: 18/03/2019
 * Last modify date: 18/03/2019
 *      Description: Set display logic for stop discharging options.
 *                   (termination type)
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
 *      Function ID: 006
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
 * Last modify date: 19/03/2019
 *      Description: Set all options in command window as default value.
 ******************************************************************************/
void Command_Panel::setDefault(QString output_file)
{
    /** Initialize discharge type */
    ui->lineEdit_SW_min_current->setText(QString::number(COMMAND_PANEL_DEFAULT_SW_MIN_I));
    ui->lineEdit_SW_max_current->setText(QString::number(COMMAND_PANEL_DEFAULT_SW_MAX_I));
    ui->lineEdit_SW_period->setText(QString::number(COMMAND_PANEL_DEFAULT_SW_PERIOD));
    ui->lineEdit_CC_discharge_current->setText(QString::number(COMMAND_PANEL_DEFAULT_CC_CURRENT));

    setChecked_type(COMMNAD_PANEL_DISCHARGE_TYPE_SQUARE_WAVE);
    setLogic_type(COMMNAD_PANEL_DISCHARGE_TYPE_SQUARE_WAVE);

    /** Initialize stop discharging options */
    ui->lineEdit_TCC_target_coulomb->setText(QString::number(COMMAND_PANEL_DEFAULT_TCC_COULOMB));
    ui->lineEdit_TOCV_target_OCV->setText(QString::number(COMMAND_PANEL_DEFAULT_TOCV_OCV));

    setChecked_option(COMMAND_PANEL_TERMINATION_TYPE_COULOMB_COUNTING);
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
 * Last modify date: 19/03/2019
 *      Description: Update all options in command window.
 ******************************************************************************/
void Command_Panel::updateInformation(int type, double min_i, double max_i, double period, double current,
                                      int options, int coulomb, double ocv,
                                      int capacity,
                                      int save_flag, QString save_path)
{
    /** Update discharge type information */
    ui->lineEdit_SW_min_current->setText(QString::number(min_i));
    ui->lineEdit_SW_max_current->setText(QString::number(max_i));
    ui->lineEdit_SW_period->setText(QString::number(period));
    ui->lineEdit_CC_discharge_current->setText(QString::number(current));

    setChecked_type(type);
    setLogic_type(type);

    /** Update stop discharging options information */
    ui->lineEdit_TCC_target_coulomb->setText(QString::number(coulomb));
    ui->lineEdit_TOCV_target_OCV->setText(QString::number(ocv));

    setChecked_option(options);
    setLogic_option(options);

    /** Update battery information information */
    ui->lineEdit_rated_capacity->setText(QString::number(capacity));

    /** Update save file information */
    ui->lineEdit_file_path->setText(save_path);

    ui->checkBox_save_file->setChecked(static_cast<bool>(save_flag));
    setLogic_save_file(save_flag);

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

/******************************************************************************
 *             Name: getAllInformation
 *      Function ID: 803
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Get all information from command panel.
 ******************************************************************************/
QStringList Command_Panel::getAllInformation()
{
    QStringList data_list;
    /** Retrieve data about discharge type. */
    if(ui->radioButton_SW->isChecked()){
        data_list.append(QString::number(COMMNAD_PANEL_DISCHARGE_TYPE_SQUARE_WAVE));
    } else {
        data_list.append(QString::number(COMMNAD_PANEL_DISCHARGE_TYPE_CONSTANT_CURRENT));
    }
    data_list.append(ui->lineEdit_SW_min_current->text());
    data_list.append(ui->lineEdit_SW_max_current->text());
    data_list.append(ui->lineEdit_SW_period->text());
    data_list.append(ui->lineEdit_CC_discharge_current->text());

    /** Retrieve data about stop discharging options. */
    if(ui->radioButton_TCC->isChecked()){
        data_list.append(QString::number(COMMAND_PANEL_TERMINATION_TYPE_COULOMB_COUNTING));
    } else {
        data_list.append(QString::number(COMMAND_PANEL_TERMINATION_TYPE_OCV));
    }
    data_list.append(ui->lineEdit_TCC_target_coulomb->text());
    data_list.append(ui->lineEdit_TOCV_target_OCV->text());

    /** Retrieve data about battery information. */
    data_list.append(ui->lineEdit_rated_capacity->text());

    /** Retrieve data about save file path. */
    if(ui->checkBox_save_file->isChecked()){
        data_list.append(QString::number(COMMAND_PANEL_SAVE_FILE_CHECKED));
    } else {
        data_list.append(QString::number(COMMAND_PANEL_SAVE_FILE_UNCHECKED));
    }
    data_list.append(ui->lineEdit_file_path->text());

    return data_list;
}

/******************************************************************************
 *             Name: setDischargeType
 *      Function ID: 810
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set discharge type.
 ******************************************************************************/
void Command_Panel::setDischargeType(int type)
{
    setChecked_type(type);
    setLogic_type(type);
}

/******************************************************************************
 *             Name: setMinDischargeCurrentt
 *      Function ID: 811
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set minimum discharge current.
 ******************************************************************************/
void Command_Panel::setMinDischargeCurrent(QString min_discharge_current)
{
    ui->lineEdit_SW_min_current->setText(min_discharge_current);
}

/******************************************************************************
 *             Name: setMaxDischargeCurrent
 *      Function ID: 812
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set maximum discharge current.
 ******************************************************************************/
void Command_Panel::setMaxDischargeCurrent(QString max_discharge_current)
{
    ui->lineEdit_SW_max_current->setText(max_discharge_current);
}

/******************************************************************************
 *             Name: setSquareWavePeriod
 *      Function ID: 813
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set square wave period.
 ******************************************************************************/
void Command_Panel::setSquareWavePeriod(QString period)
{
    ui->lineEdit_SW_period->setText(period);
}

/******************************************************************************
 *             Name: setConstantDischargeCurrent
 *      Function ID: 814
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set constant discharge current.
 ******************************************************************************/
void Command_Panel::setConstantDischargeCurrent(QString constant_discharge_current)
{
    ui->lineEdit_CC_discharge_current->setText(constant_discharge_current);
}

/******************************************************************************
 *             Name: setTerminationType
 *      Function ID: 815
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set termination type.
 ******************************************************************************/
void Command_Panel::setTerminationType(int type)
{
    setChecked_option(type);
    setLogic_option(type);
}

/******************************************************************************
 *             Name: setTargetCoulomb
 *      Function ID: 816
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set target coulomb.
 ******************************************************************************/
void Command_Panel::setTargetCoulomb(QString target_TCC)
{
    ui->lineEdit_TCC_target_coulomb->setText(target_TCC);
}

/******************************************************************************
 *             Name: setTargetOCV
 *      Function ID: 817
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set target OCV.
 ******************************************************************************/
void Command_Panel::setTargetOCV(QString target_TOCV)
{
    ui->lineEdit_TOCV_target_OCV->setText(target_TOCV);
}

/******************************************************************************
 *             Name: setRateCapacity
 *      Function ID: 818
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set rate capacity.
 ******************************************************************************/
void Command_Panel::setRateCapacity(QString rate_capacity)
{
    ui->lineEdit_rated_capacity->setText(rate_capacity);
}

/******************************************************************************
 *             Name: setSaveFlag
 *      Function ID: 819
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set save flag.
 ******************************************************************************/
void Command_Panel::setSaveFlag(int flag)
{
    ui->checkBox_save_file->setChecked(static_cast<bool>(flag));
    setLogic_save_file(flag);
}

/******************************************************************************
 *             Name: setSavePath
 *      Function ID: 820
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set save path.
 ******************************************************************************/
void Command_Panel::setSavePath(QString path)
{
    ui->lineEdit_file_path->setText(path);
}


