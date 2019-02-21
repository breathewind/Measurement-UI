/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 20/02/2019
 * Last modify date: 21/02/2019
 *      Description: Serial Port frame of Settings dialog.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   6XX - View control functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#ifndef C290_SETTINGS_DIALOG_SERIAL_PORT_FRAME_H
#define C290_SETTINGS_DIALOG_SERIAL_PORT_FRAME_H

#include <QFrame>

#include "h001_serial_parameters.h"

namespace Ui {
class Settings_DIalog_Serial_Port_Frame;
}

class Settings_DIalog_Serial_Port_Frame : public QFrame
{
    Q_OBJECT

public:
    /** Function 000: Construction function. */
    explicit Settings_DIalog_Serial_Port_Frame(QWidget *parent = nullptr);
    /** Function 001: Destruction function. */
    ~Settings_DIalog_Serial_Port_Frame();


    /** Function 002: Initialize DMM group. */
    void initDMM_group(QStringList *data);
    /** Function 003: Initialize BC group. */
    void initBC_group(QStringList *data);
    /** Function 004: Update all DMM combo boxes. */
    void updateDMM_combobox(QStringList data);
    /** Function 005: Update all BC combo boxes. */
    void updateBC_combobox(QStringList data);

    /** Function 006: Update port combobbox. */
    void updateSerial_port_combobox(QStringList data);

    /** Function 007: Retrieve data from all DMM combobbox. */
    QStringList retrieveDMM_data();
    /** Function 008: Retrieve data from all BC combobbox. */
    QStringList retrieveBC_data();

private:
    Ui::Settings_DIalog_Serial_Port_Frame *ui;

private slots:
    /** Function 700: Slot for Rescan push button clicked. */
    void on_pushButton_Rescan_clicked();
signals:
    /** Signal 001: Signal emitted when a rescan operation is acquired. */
    void signal_rescan();
};

#endif // C290_SETTINGS_DIALOG_SERIAL_PORT_FRAME_H
