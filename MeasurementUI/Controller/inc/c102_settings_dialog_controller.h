/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 21/02/2019
 * Last modify date: 15/03/2019
 *      Description: Settings dialog controller.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#ifndef C102_SETTINGS_DIALOG_CONTROLLER_H
#define C102_SETTINGS_DIALOG_CONTROLLER_H

#define SETTINGS_DIALOG_CONTROLLER_SERIAL_PORT 0

#define SETTINGS_DIALOG_CONTROLLER_DATA_SIZE 2
#define SETTINGS_DIALOG_CONTROLLER_DATA_DMM  0
#define SETTINGS_DIALOG_CONTROLLER_DATA_BC   1

#include <QObject>

#include "View/inc/c202_settings_dialog.h"

#include "Controller/inc/c190_settings_dialog_serial_port_frame_controller.h"

class Settings_Dialog_Controller : public QObject
{
    Q_OBJECT
public:
    /** Function 000: Construction function. */
    Settings_Dialog_Controller(Settings_Dialog *setting_dialog);

    /** Function 300: Set all frames as default values. */
    void resetAll_frames();
    /** Function 301: Update all frames. */
    void updataeAll_frames(QList<QStringList> data);

private:
    /** Function 002: Initialize serial port frame and controller. */
    void initSerial_Port_Frame();

    Settings_Dialog *_setting_dialog;
    Settings_DIalog_Serial_Port_Frame *_serial_port_frame;
    Settings_Dialog_Serial_Port_Frame_Controller* _serial_port_frame_controller;

    int _current_widget;

private slots:
    /** Function 700: Slot for retrieving data when accepted signal received from Settings_Dialog. */
    void slot_modification_accepted();

signals:
    /** Signal 001: Signal emitted when the modification of Settings_Dialog is comfirmed. */
    void signal_modification_confirmed(QList<QStringList> data_set);
};

#endif // C102_SETTINGS_DIALOG_CONTROLLER_H
