/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 22/02/2019
 * Last modify date: 25/02/2019
 *      Description: Main window controller.
 *                   - Functional slots.
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: slot_update_data_from_settings
 *      Function ID: 750
 *      Create date: 22/02/2019
 * Last modify date: 22/02/2019
 *      Description: Slot for updating data from settings dialog to main
 *                   controller.
 ******************************************************************************/
void MainController::slot_update_data_from_settings(QList<QStringList> data_set)
{
    _dmm_baudrate = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_DMM).at(MEASUREMENTUI_INDEX_BAUDRATE);
    _dmm_databits = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_DMM).at(MEASUREMENTUI_INDEX_DATABITS);
    _dmm_stopbits = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_DMM).at(MEASUREMENTUI_INDEX_STOPBITS);
    _dmm_parity = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_DMM).at(MEASUREMENTUI_INDEX_PARITY);
    _dmm_flowcontrol = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_DMM).at(MEASUREMENTUI_INDEX_FLOWCONTROL);
    _dmm_port = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_DMM).at(MEASUREMENTUI_INDEX_PORT);

    _bc_baudrate = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_BC).at(MEASUREMENTUI_INDEX_BAUDRATE);
    _bc_databits = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_BC).at(MEASUREMENTUI_INDEX_DATABITS);
    _bc_stopbits = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_BC).at(MEASUREMENTUI_INDEX_STOPBITS);
    _bc_parity = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_BC).at(MEASUREMENTUI_INDEX_PARITY);
    _bc_flowcontrol = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_BC).at(MEASUREMENTUI_INDEX_FLOWCONTROL);
    _bc_port = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_BC).at(MEASUREMENTUI_INDEX_PORT);

    debug_printSerial_information();
}

/******************************************************************************
 *             Name: slot_retrieveDMM_data
 *      Function ID: 751
 *      Create date: 25/02/2019
 * Last modify date: 25/02/2019
 *      Description: Slot for retrieving data from DMM when capture timer
 *                   timeout is reached.
 ******************************************************************************/
void MainController::slot_retrieveDMM_data(QString received_data)
{
    _data_read_buffer = received_data;
#ifdef MAINCONTROLLER_DEBUG
    qint64 elapsed_time = _elapsed_timer.elapsed();
    qDebug() << "+ MainController: " << __FUNCTION__ << " The measurement operation took: " << elapsed_time << " milliseconds";
    qDebug() << "+ MainController: " << __FUNCTION__ << "- received_data: " << received_data;
#endif
}

/******************************************************************************
 *             Name: slot_read_serial_buffer
 *      Function ID: 752
 *      Create date: 25/02/2019
 * Last modify date: 25/02/2019
 *      Description: Slot for reading data from data read buffer when capture
 *                   timer timeout is reached.
 ******************************************************************************/
void MainController::slot_read_serial_buffer()
{
    _capture_timer->stop();

    switch(_sampling_command){
    case MAINCONTROLLER_COMMAND_RUN:
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__ << "- data: " << QString("%1 V").arg(_data_read_buffer.toDouble());
#endif
        captureOne_measurement();
        break;
    case MAINCONTROLLER_COMMAND_STOP:
        _DMM_controller->closeSerial();
        break;
    case MAINCONTROLLER_COMMAND_PAUSE:
        break;
    default:
        break;
    }
}
