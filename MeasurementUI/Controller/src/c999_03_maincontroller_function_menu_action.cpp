/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 19/02/2019
 * Last modify date: 20/02/2019
 *      Description: Main window controller.
 *                   - Functions related to function menu actions.
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: handleSettings
 *      Function ID: 238
 *      Create date: 19/02/2019
 * Last modify date: 20/02/2019
 *      Description: Function for handle operations related to Settings.
 ******************************************************************************/
void MainController::handleSettings()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleSettings";
#endif
    if(_main_window->getSettings_action_checked()){
        _settings_dialog->show();
        /** Let system remember dialog current position. */
        _settings_dialog->move(_settings_dialog->pos().x(), _settings_dialog->pos().y());
    } else {
        _settings_dialog->hide();
    }
}

/******************************************************************************
 *             Name: handleCommand_Panel
 *      Function ID: 239
 *      Create date: 19/02/2019
 * Last modify date: 20/02/2019
 *      Description: Function for handle operations related to Command Panel.
 ******************************************************************************/
void MainController::handleCommand_Panel()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleCommand_Panel";
#endif
    if(_main_window->getCommand_panel_action_checked()){
        _command_panel->show();
        /** Let system remember dialog current position. */
        _command_panel->move(_command_panel->pos().x(), _command_panel->pos().y());
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
    qDebug() << "+ MainController: handleOutput_Panel";
#endif
    if(_main_window->getOutput_panel_action_checked()){
        _output_panel->show();
        /** Let system remember dialog current position. */
        _output_panel->move(_output_panel->pos().x(), _output_panel->pos().y());
    } else {
        _output_panel->hide();
    }
}
