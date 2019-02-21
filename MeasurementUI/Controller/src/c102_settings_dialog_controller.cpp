/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Settings dialog controller.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#include "Controller/inc/c102_settings_dialog_controller.h"

/******************************************************************************
 *             Name: Settings_Dialog_Controller
 *      Function ID: 000
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Construction function.
 ******************************************************************************/
Settings_Dialog_Controller::Settings_Dialog_Controller(Settings_Dialog *setting_dialog) :
    _setting_dialog(setting_dialog)
{

    initSerial_Port_Frame();

    _current_widget = SETTINGS_DIALOG_CONTROLLER_SERIAL_PORT;
    _setting_dialog->setCurrent_frame(_serial_port_frame);
}

/******************************************************************************
 *             Name: initSerial_Port_Frame
 *      Function ID: 002
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Initialize serial port frame and controller.
 ******************************************************************************/
void Settings_Dialog_Controller::initSerial_Port_Frame()
{
    _serial_port_frame = new Settings_DIalog_Serial_Port_Frame(_setting_dialog);
    _serial_port_frame_controller = new Settings_Dialog_Serial_Port_Frame_Controller(_serial_port_frame);
}

/******************************************************************************
 *             Name: resetAll_frames
 *      Function ID: 300
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Set all frames as default values.
 ******************************************************************************/
void Settings_Dialog_Controller::resetAll_frames()
{
    _serial_port_frame_controller->setCombobox_default();
}

/******************************************************************************
 *             Name: updataeAll_frames
 *      Function ID: 301
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Update all frames..
 ******************************************************************************/
void Settings_Dialog_Controller::updataeAll_frames(QStringList* data)
{
    _serial_port_frame_controller->updateDMM(data[0]);
    _serial_port_frame_controller->updateBC(data[1]);
}
