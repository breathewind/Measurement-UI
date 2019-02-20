/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 18/02/2019
 * Last modify date: 20/02/2019
 *      Description: Main window controller.
 *                   - Functions related to file menu actions.
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: handleNew_Project
 *      Function ID: 231
 *      Create date: 18/02/2019
 * Last modify date: 20/02/2019
 *      Description: Function for handle operations related to New Project.
 ******************************************************************************/
bool MainController::handleNew_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleNew_Project";
#endif
    /** Create directory. */
    QDir dir(_project_path);
    if(dir.exists()){
        dir.removeRecursively();
    }
    QDir().mkdir(_project_path);
    /** Create project file. */
    QFile file(_project_file_full_path);
    if (!file.open(QFile::WriteOnly | QFile::Text )) {
        emit signal_warning_occurs(QString("Fail to create file: %1").arg(_project_file_full_path));
        return false;
    }
    QTextStream out_stream(&file);
    out_stream << MAINCONTTROLLER_SETTINGS_DISPLAY_TEXT << " 0" << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_COMMAND_PANEL_DISPLAY_TEXT << " 0" << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_OUTPUT_PANEL_DISPLAY_TEXT << " 0" << MEASUREMENTUI_DAFAULT_NEW_LINE;
    file.flush();
    file.close();

    return true;
}

/******************************************************************************
 *             Name: handleOpen_Project
 *      Function ID: 232
 *      Create date: 18/02/2019
 * Last modify date: 20/02/2019
 *      Description: Function for handle operations related to Open Project.
 ******************************************************************************/
bool MainController::handleOpen_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleOpen_Project";
#endif
    QFile file(_project_file_full_path);
    if (!file.open(QFile::ReadOnly | QFile::Text )) {
        emit signal_warning_occurs(QString("Fail to create file: %1").arg(_project_file_full_path));
        return false;
    }
    QTextStream in_stream(&file);
    while(!in_stream.atEnd()) {
        QString line = in_stream.readLine();
        QStringList fields = line.split(" ");
        /*************************
         * SETTINGS_DISPLAY
         *************************/
        if(fields.at(0) == MAINCONTTROLLER_SETTINGS_DISPLAY_TEXT) {
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_SETTINGS_DISPLAY_TEXT << " " << fields.at(1).toInt();
#endif
            if(fields.at(1).toInt()){
                _main_window->setSettings_action_checked(true);
                _settings_dialog->showDialog();
            } else {
                _main_window->setSettings_action_checked(false);
                _settings_dialog->hide();
            }
        } else
        /*************************
         * COMMAND_PANEL_DISPLAY
         *************************/
        if (fields.at(0) == MAINCONTTROLLER_COMMAND_PANEL_DISPLAY_TEXT) {
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_COMMAND_PANEL_DISPLAY_TEXT << " " << fields.at(1).toInt();
#endif
            if(fields.at(1).toInt()){
                _main_window->setCommand_panel_action_checked(true);
                _command_panel->showDialog();
            } else {
                _main_window->setCommand_panel_action_checked(false);
                _command_panel->hide();
            }
        } else
        /*************************
         * OUTPUT_PANEL_DISPLAY
         *************************/
        if (fields.at(0) == MAINCONTTROLLER_OUTPUT_PANEL_DISPLAY_TEXT) {
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_OUTPUT_PANEL_DISPLAY_TEXT << " " << fields.at(1).toInt();
#endif
            if(fields.at(1).toInt()){
                _main_window->setOutput_panel_action_checked(true);
                _output_panel->showDialog();
            } else {
                _main_window->setOutput_panel_action_checked(false);
                _output_panel->hide();
            }
        } else {
            file.close();
            emit signal_warning_occurs(QString("Unknow parameter: %1").arg(fields.at(0)));
            return false;
        }
        file.close();
    }
    return true;
}

/******************************************************************************
 *             Name: handleSave_Project
 *      Function ID: 233
 *      Create date: 18/02/2019
 * Last modify date: 20/02/2019
 *      Description: Function for handle operations related to Save Project.
 ******************************************************************************/
void MainController::handleSave_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleSave_Project";
#endif
    /** Save project file. */
    QFile file(_project_file_full_path);
    if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate)) {
        emit signal_warning_occurs(QString("Fail to open file: %1").arg(_project_file_full_path));
        return;
    }
    QTextStream out_stream(&file);
    out_stream << MAINCONTTROLLER_SETTINGS_DISPLAY_TEXT << " " << _main_window->getSettings_action_checked() << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_COMMAND_PANEL_DISPLAY_TEXT << " " << _main_window->getCommand_panel_action_checked() << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_OUTPUT_PANEL_DISPLAY_TEXT << " " << _main_window->getOutput_panel_action_checked()<< MEASUREMENTUI_DAFAULT_NEW_LINE;
    file.flush();
    file.close();
}

/******************************************************************************
 *             Name: handleSave_Project_As
 *      Function ID: 234
 *      Create date: 18/02/2019
 * Last modify date: 20/02/2019
 *      Description: Function for handle operations related to Save Project As.
 ******************************************************************************/
void MainController::handleSave_Project_As()
{
    handleSave_Project();
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleSave_Project_As";
#endif
}

/******************************************************************************
 *             Name: handle_CloseProject
 *      Function ID: 235
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Function for handle operations related to Close Project.
 ******************************************************************************/
void MainController::handleClose_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handle_CloseProject";
#endif
    _main_window->setWindowTitle(QString(APP_NAME));
}
