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
#ifndef C190_SETTINGS_DIALOG_SERIAL_PORT_FRAME_CONTROLLER_H
#define C190_SETTINGS_DIALOG_SERIAL_PORT_FRAME_CONTROLLER_H

#include <QObject>

#include "View/inc/c290_settings_dialog_serial_port_frame.h"

class Settings_Dialog_Serial_Port_Frame_Controller : public QObject
{
    Q_OBJECT
public:
    /** Function 000: Construction function. */
    Settings_Dialog_Serial_Port_Frame_Controller(Settings_DIalog_Serial_Port_Frame *serial_port_frame);

    /** Function 300: Update all DMM combo boxes. */
    void updateDMM(QStringList data);
    /** Function 301: 4. */
    void updateBC(QStringList data);
    /** Function 302: Rescan serial ports. */
    void rescanSerial_port();
    /** Function 303: Set all combobox by default settings. */
    void setCombobox_default();

private:
    /** Function 002: Initialize DMM group. */
    void initDMM_group();
    /** Function 003: Initialize BC group. */
    void initBC_group();

    Settings_DIalog_Serial_Port_Frame *_serial_port_frame;

private slots:
    /** Function 700: Slot for a rescan operation is acquired. */
    void slot_rescan();
};

#endif // C190_SETTINGS_DIALOG_SERIAL_PORT_FRAME_CONTROLLER_H
