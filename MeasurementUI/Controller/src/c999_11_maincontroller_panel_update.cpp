/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 22/02/2019
 * Last modify date: 22/02/2019
 *      Description: Main window controller.
 *                   - Functions related to update data from panels and
 *                     dialogs.
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
