/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 19/02/2019
 * Last modify date: 15/03/2019
 *      Description: Main window controller.
 *                   - Functions related to function menu actions.
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: handleSettings
 *      Function ID: 238
 *      Create date: 19/02/2019
 * Last modify date: 15/03/2019
 *      Description: Function for handle operations related to Settings.
 ******************************************************************************/
void MainController::handleSettings()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__;
#endif
    if(_main_window->getSettings_action_checked()){
        updateSettings();
        _settings_dialog->showDialog();
    } else {
        _settings_dialog->hide();
    }
}

/******************************************************************************
 *             Name: handleCommand_Panel
 *      Function ID: 239
 *      Create date: 19/02/2019
 * Last modify date: 26/02/2019
 *      Description: Function for handle operations related to Command Panel.
 ******************************************************************************/
void MainController::handleCommand_Panel()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__;
#endif
//    _battery_voltage_chart_view_controller->addOne_new_voltage(60000, 2.1);
    if(_main_window->getCommand_panel_action_checked()){
        _command_panel->showDialog();
    } else {
        _command_panel->hide();
    }
}

/******************************************************************************
 *             Name: handleOutput_Panel
 *      Function ID: 240
 *      Create date: 19/02/2019
 * Last modify date: 20/02/2019
 *      Description: Function for handle operations related to Output Panel.
 ******************************************************************************/
void MainController::handleOutput_Panel()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__;
#endif
    if(_main_window->getOutput_panel_action_checked()){
        _output_panel->showDialog();
    } else {
        _output_panel->hide();
    }
}
