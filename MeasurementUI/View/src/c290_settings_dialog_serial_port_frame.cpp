/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 20/02/2019
 * Last modify date: 22/02/2019
 *      Description: Serial Port frame of Settings dialog.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   6XX - View control functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#include "View/inc/c290_settings_dialog_serial_port_frame.h"
#include "ui_c290_settings_dialog_serial_port_frame.h"

/******************************************************************************
 *             Name: Settings_DIalog_Serial_Port_Frame
 *      Function ID: 000
 *      Create date: 20/02/2019
 * Last modify date: 21/02/2019
 *      Description: Construction function.
 ******************************************************************************/
Settings_DIalog_Serial_Port_Frame::Settings_DIalog_Serial_Port_Frame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Settings_DIalog_Serial_Port_Frame)
{
    ui->setupUi(this);
}

/******************************************************************************
 *             Name: ~Settings_DIalog_Serial_Port_Frame
 *      Function ID: 001
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Destruction function.
 ******************************************************************************/
Settings_DIalog_Serial_Port_Frame::~Settings_DIalog_Serial_Port_Frame()
{
    delete ui;
}

/******************************************************************************
 *             Name: initDMM_group
 *      Function ID: 002
 *      Create date: 20/02/2019
 * Last modify date: 21/02/2019
 *      Description: Initialize DMM group.
 ******************************************************************************/
void Settings_DIalog_Serial_Port_Frame::initDMM_group(QStringList *data)
{
    ui->comboBox_DMM_baudrate->addItems(data[1]);
    ui->comboBox_DMM_databits->addItems(data[2]);
    ui->comboBox_DMM_stopbits->addItems(data[3]);
    ui->comboBox_DMM_parity->addItems(data[4]);
    ui->comboBox_DMM_flowcontrol->addItems(data[5]);
    ui->comboBox_DMM_port->addItems(data[0]);
}

/******************************************************************************
 *             Name: initBC_group
 *      Function ID: 003
 *      Create date: 20/02/2019
 * Last modify date: 21/02/2019
 *      Description: Initialize BC group.
 ******************************************************************************/
void Settings_DIalog_Serial_Port_Frame::initBC_group(QStringList *data)
{
    ui->comboBox_BC_baudrate->addItems(data[1]);
    ui->comboBox_BC_databits->addItems(data[2]);
    ui->comboBox_BC_stopbits->addItems(data[3]);
    ui->comboBox_BC_parity->addItems(data[4]);
    ui->comboBox_BC_flowcontrol->addItems(data[5]);
    ui->comboBox_BC_port->addItems(data[0]);
}

/******************************************************************************
 *             Name: updateDMM_Combobox
 *      Function ID: 004
 *      Create date: 21/02/2019
 * Last modify date: 22/02/2019
 *      Description: Update all DMM combo boxes.
 ******************************************************************************/
void Settings_DIalog_Serial_Port_Frame::updateDMM_combobox(QStringList data)
{
    ui->comboBox_DMM_baudrate->setCurrentText(data.at(MEASUREMENTUI_INDEX_BAUDRATE));
    ui->comboBox_DMM_databits->setCurrentText(data.at(MEASUREMENTUI_INDEX_DATABITS));
    ui->comboBox_DMM_stopbits->setCurrentText(data.at(MEASUREMENTUI_INDEX_STOPBITS));
    ui->comboBox_DMM_parity->setCurrentText(data.at(MEASUREMENTUI_INDEX_PARITY));
    ui->comboBox_DMM_flowcontrol->setCurrentText(data.at(MEASUREMENTUI_INDEX_FLOWCONTROL));
}

/******************************************************************************
 *             Name: updateBC_Combobox
 *      Function ID: 005
 *      Create date: 21/02/2019
 * Last modify date: 22/02/2019
 *      Description: Update all BC combo boxes.
 ******************************************************************************/
void Settings_DIalog_Serial_Port_Frame::updateBC_combobox(QStringList data)
{
    ui->comboBox_BC_baudrate->setCurrentText(data.at(MEASUREMENTUI_INDEX_BAUDRATE));
    ui->comboBox_BC_databits->setCurrentText(data.at(MEASUREMENTUI_INDEX_DATABITS));
    ui->comboBox_BC_stopbits->setCurrentText(data.at(MEASUREMENTUI_INDEX_STOPBITS));
    ui->comboBox_BC_parity->setCurrentText(data.at(MEASUREMENTUI_INDEX_PARITY));
    ui->comboBox_BC_flowcontrol->setCurrentText(data.at(MEASUREMENTUI_INDEX_FLOWCONTROL));
}

/******************************************************************************
 *             Name: updateSerial_port_combobox
 *      Function ID: 006
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Update port combobbox.
 ******************************************************************************/
void Settings_DIalog_Serial_Port_Frame::updateSerial_port_combobox(QStringList data)
{
    ui->comboBox_DMM_port->clear();
    ui->comboBox_BC_port->clear();

    ui->comboBox_DMM_port->addItems(data);
    ui->comboBox_BC_port->addItems(data);
}

/******************************************************************************
 *             Name: retrieveDMM_data
 *      Function ID: 007
 *      Create date: 21/02/2019
 * Last modify date: 22/02/2019
 *      Description: Retrieving data from all DMM combobbox.
 ******************************************************************************/
QStringList Settings_DIalog_Serial_Port_Frame::retrieveDMM_data()
{
    QStringList data;

    data.append(ui->comboBox_DMM_baudrate->currentText());
    data.append(ui->comboBox_DMM_databits->currentText());
    data.append(ui->comboBox_DMM_stopbits->currentText());
    data.append(ui->comboBox_DMM_parity->currentText());
    data.append(ui->comboBox_DMM_flowcontrol->currentText());
    data.append(ui->comboBox_DMM_port->currentText());

    return data;
}
/******************************************************************************
 *             Name: retrieveBC_data
 *      Function ID: 008
 *      Create date: 21/02/2019
 * Last modify date: 22/02/2019
 *      Description: Retrieving data from all BC combobbox.
 ******************************************************************************/
QStringList Settings_DIalog_Serial_Port_Frame::retrieveBC_data()
{
    QStringList data;

    data.append(ui->comboBox_BC_baudrate->currentText());
    data.append(ui->comboBox_BC_databits->currentText());
    data.append(ui->comboBox_BC_stopbits->currentText());
    data.append(ui->comboBox_BC_parity->currentText());
    data.append(ui->comboBox_BC_flowcontrol->currentText());
    data.append(ui->comboBox_BC_port->currentText());

    return data;
}


/******************************************************************************
 *             Name: on_pushButton_Rescan_clicked
 *      Function ID: 700
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Slot for Rescan push button clicked.
 ******************************************************************************/
void Settings_DIalog_Serial_Port_Frame::on_pushButton_Rescan_clicked()
{
    emit signal_rescan();
}
