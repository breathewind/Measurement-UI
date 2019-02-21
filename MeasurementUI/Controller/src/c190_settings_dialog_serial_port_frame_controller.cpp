/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Settings dialog serial port frame controller.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#include "Controller/inc/c190_settings_dialog_serial_port_frame_controller.h"

/******************************************************************************
 *             Name: Settings_Dialog_Serial_Port_Frame_Controller
 *      Function ID: 000
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Construction function.
 ******************************************************************************/
Settings_Dialog_Serial_Port_Frame_Controller::Settings_Dialog_Serial_Port_Frame_Controller(Settings_DIalog_Serial_Port_Frame *serial_port_frame) :
    _serial_port_frame(serial_port_frame)
{
    initDMM_group();
    initBC_group();

    setCombobox_default();

    connect(_serial_port_frame, &Settings_DIalog_Serial_Port_Frame::signal_rescan, this, &Settings_Dialog_Serial_Port_Frame_Controller::slot_rescan);
}

/******************************************************************************
 *             Name: initDMM_group
 *      Function ID: 002
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Initialize DMM group.
 ******************************************************************************/
void Settings_Dialog_Serial_Port_Frame_Controller::initDMM_group()
{
    QStringList data[6] = { Serial_definitions::getSerial_port_name(),
                            __serial_definitions.getBaudrate_list(),
                            __serial_definitions.getDataBits_list(),
                            __serial_definitions.getStopBits_list(),
                            __serial_definitions.getParity_list(),
                            __serial_definitions.getFlowcontrol_list()};
    _serial_port_frame->initDMM_group(data);
}

/******************************************************************************
 *             Name: initBC_group
 *      Function ID: 003
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Initialize BC group.
 ******************************************************************************/
void Settings_Dialog_Serial_Port_Frame_Controller::initBC_group()
{
    QStringList data[6] = { Serial_definitions::getSerial_port_name(),
                            __serial_definitions.getBaudrate_list(),
                            __serial_definitions.getDataBits_list(),
                            __serial_definitions.getStopBits_list(),
                            __serial_definitions.getParity_list(),
                            __serial_definitions.getFlowcontrol_list()};
    _serial_port_frame->initBC_group(data);
}

/******************************************************************************
 *             Name: updateDMM
 *      Function ID: 300
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Update all DMM combo boxes.
 ******************************************************************************/
void Settings_Dialog_Serial_Port_Frame_Controller::updateDMM(QStringList data)
{
    _serial_port_frame->updateDMM_combobox(data);
}

/******************************************************************************
 *             Name: updateBC
 *      Function ID: 301
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Update all BC combo boxes.
 ******************************************************************************/
void Settings_Dialog_Serial_Port_Frame_Controller::updateBC(QStringList data)
{
    _serial_port_frame->updateBC_combobox(data);
}

/******************************************************************************
 *             Name: rescanSerial_port
 *      Function ID: 302
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Rescan serial ports.
 ******************************************************************************/
void Settings_Dialog_Serial_Port_Frame_Controller::rescanSerial_port()
{
    _serial_port_frame->updateSerial_port_combobox(Serial_definitions::getSerial_port_name());
}

/******************************************************************************
 *             Name: setCombobox_default
 *      Function ID: 303
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Set all combobox by default settings.
 ******************************************************************************/
void Settings_Dialog_Serial_Port_Frame_Controller::setCombobox_default()
{
    rescanSerial_port();

    QStringList DMM_data;
    QStringList BC_data;

    DMM_data.append(MEASUREMENTUI_DMM_BAUDRATE);
    DMM_data.append(MEASUREMENTUI_DMM_DATABITS);
    DMM_data.append(MEASUREMENTUI_DMM_STOPBITS);
    DMM_data.append(MEASUREMENTUI_DMM_PARITY);
    DMM_data.append(MEASUREMENTUI_DMM_FLOWCONTROL);

    BC_data.append(MEASUREMENTUI_BC_BAUDRATE);
    BC_data.append(MEASUREMENTUI_BC_DATABITS);
    BC_data.append(MEASUREMENTUI_BC_STOPBITS);
    BC_data.append(MEASUREMENTUI_BC_PARITY);
    BC_data.append(MEASUREMENTUI_BC_FLOWCONTROL);

    _serial_port_frame->updateDMM_combobox(DMM_data);
    _serial_port_frame->updateBC_combobox(BC_data);
}

/******************************************************************************
 *             Name: slot_rescan
 *      Function ID: 700
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Slot for a rescan operation is acquired.
 ******************************************************************************/
void Settings_Dialog_Serial_Port_Frame_Controller::slot_rescan()
{
    rescanSerial_port();
}
