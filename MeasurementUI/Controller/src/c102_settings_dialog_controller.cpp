/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 21/02/2019
 * Last modify date: 18/03/2019
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
 * Last modify date: 18/03/2019
 *      Description: Construction function.
 ******************************************************************************/
Settings_Dialog_Controller::Settings_Dialog_Controller(Settings_Dialog *setting_dialog) :
    _setting_dialog(setting_dialog)
{
    initSerial_Port_Frame();

    _current_widget = SETTINGS_DIALOG_CONTROLLER_SERIAL_PORT;
    _setting_dialog->setCurrent_frame(_serial_port_frame);

    connect(_setting_dialog, &Settings_Dialog::accepted, this, &Settings_Dialog_Controller::slot_modification_accepted);
    connect(_setting_dialog, &Settings_Dialog::signal_accept_button_clicked, this, &Settings_Dialog_Controller::slot_modification_accepted);
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
 * Last modify date: 15/03/2019
 *      Description: Update all frames..
 ******************************************************************************/
void Settings_Dialog_Controller::updataeAll_frames(QList<QStringList> data)
{
    _serial_port_frame_controller->updateDMM(data.at(SETTINGS_DIALOG_CONTROLLER_DATA_DMM));
    _serial_port_frame_controller->updateBC(data.at(SETTINGS_DIALOG_CONTROLLER_DATA_BC));

//    for (int i=0; i<SETTINGS_DIALOG_SERIAL_PORT_FRAME_CONTROLLER_DATA_SET_SIZE; i++) {
//        for (int j=0 ; j<5; j++) {
//            qDebug() << data[i].at(j);
//        }
//    }
}

/******************************************************************************
 *             Name: slot_modification_accepted
 *      Function ID: 700
 *      Create date: 22/02/2019
 * Last modify date: 22/02/2019
 *      Description: Slot for retrieving data when accepted signal received
 *                   from Settings_Dialog..
 ******************************************************************************/
void Settings_Dialog_Controller::slot_modification_accepted()
{
    QList<QStringList> data_set;

    data_set.append(_serial_port_frame_controller->retrieveData());

    emit signal_modification_confirmed(data_set);
}
