/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 18/02/2019
 * Last modify date: 24/02/2019
 *      Description: Main window controller.
 *                   - Functions related to file menu actions.
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: handleNew_Project
 *      Function ID: 231
 *      Create date: 18/02/2019
 * Last modify date: 22/02/2019
 *      Description: Function for handle operations related to New Project.
 ******************************************************************************/
bool MainController::handleNew_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__;
#endif

    QStringList available_ports = Serial_definitions::getSerial_port_name();
    if(available_ports.size() > 0){
        _dmm_port = available_ports.at(0);
        _dmm_port = available_ports.at(0);
    } else {
        _dmm_port = QString();
        _bc_port = QString();
    }
    _dmm_baudrate    = MEASUREMENTUI_DMM_BAUDRATE;
    _dmm_databits    = MEASUREMENTUI_DMM_DATABITS;
    _dmm_stopbits    = MEASUREMENTUI_DMM_STOPBITS;
    _dmm_parity      = MEASUREMENTUI_DMM_PARITY;
    _dmm_flowcontrol = MEASUREMENTUI_DMM_FLOWCONTROL;

    _bc_baudrate    = MEASUREMENTUI_BC_BAUDRATE;
    _bc_databits    = MEASUREMENTUI_BC_DATABITS;
    _bc_stopbits    = MEASUREMENTUI_BC_STOPBITS;
    _bc_parity      = MEASUREMENTUI_BC_PARITY;
    _bc_flowcontrol = MEASUREMENTUI_BC_FLOWCONTROL;


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

    out_stream << MAINCONTTROLLER_SETTINGS_DISPLAY_TEXT      << " 0" << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_COMMAND_PANEL_DISPLAY_TEXT << " 0" << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_OUTPUT_PANEL_DISPLAY_TEXT  << " 0" << MEASUREMENTUI_DAFAULT_NEW_LINE;

    out_stream << MAINCONTTROLLER_SERIAL_DMM_BAUDRATE_TEXT    << " " << __serial_definitions.getBaudrate(_dmm_baudrate)    << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_DATABITS_TEXT    << " " << __serial_definitions.getDataBits(_dmm_databits)    << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_STOPBITS_TEXT    << " " << __serial_definitions.getStopBits(_dmm_stopbits)    << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_PARITY_TEXT      << " " << __serial_definitions.getParity(_dmm_parity)        << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_FLOWCONTROL_TEXT << " " << __serial_definitions.getFlowcontrol(_dmm_flowcontrol) << MEASUREMENTUI_DAFAULT_NEW_LINE;

    out_stream << MAINCONTTROLLER_SERIAL_BC_BAUDRATE_TEXT    << " " << __serial_definitions.getBaudrate(_bc_baudrate)    << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_BC_DATABITS_TEXT    << " " << __serial_definitions.getDataBits(_bc_databits)    << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_BC_STOPBITS_TEXT    << " " << __serial_definitions.getStopBits(_bc_stopbits)    << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_BC_PARITY_TEXT      << " " << __serial_definitions.getParity(_bc_parity)        << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_BC_FLOWCONTROL_TEXT << " " << __serial_definitions.getFlowcontrol(_bc_flowcontrol) << MEASUREMENTUI_DAFAULT_NEW_LINE;

    file.flush();
    file.close();

    _setting_dialog_controller->resetAll_frames();

    return true;
}

/******************************************************************************
 *             Name: handleOpen_Project
 *      Function ID: 232
 *      Create date: 18/02/2019
 * Last modify date: 24/02/2019
 *      Description: Function for handle operations related to Open Project.
 ******************************************************************************/
bool MainController::handleOpen_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__;
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
        if(fields.at(0) == MAINCONTTROLLER_SETTINGS_DISPLAY_TEXT) {
            /************************* SETTINGS_DISPLAY *************************/
            printData_read_from_project_file(MAINCONTTROLLER_SETTINGS_DISPLAY_TEXT, fields.at(1));
            if(fields.at(1).toInt()){
                _main_window->setSettings_action_checked(true);
                _settings_dialog->showDialog();
            } else {
                _main_window->setSettings_action_checked(false);
                _settings_dialog->hide();
            }
        } else if (fields.at(0) == MAINCONTTROLLER_COMMAND_PANEL_DISPLAY_TEXT) {
            /************************* COMMAND_PANEL_DISPLAY *************************/
            printData_read_from_project_file(MAINCONTTROLLER_COMMAND_PANEL_DISPLAY_TEXT, fields.at(1));
            if(fields.at(1).toInt()){
                _main_window->setCommand_panel_action_checked(true);
                _command_panel->showDialog();
            } else {
                _main_window->setCommand_panel_action_checked(false);
                _command_panel->hide();
            }
        } else if (fields.at(0) == MAINCONTTROLLER_OUTPUT_PANEL_DISPLAY_TEXT) {
            /************************* OUTPUT_PANEL_DISPLAY *************************/
            printData_read_from_project_file(MAINCONTTROLLER_OUTPUT_PANEL_DISPLAY_TEXT, fields.at(1));
            if(fields.at(1).toInt()){
                _main_window->setOutput_panel_action_checked(true);
                _output_panel->showDialog();
            } else {
                _main_window->setOutput_panel_action_checked(false);
                _output_panel->hide();
            }
        } else if (fields.at(0) == MAINCONTTROLLER_SERIAL_DMM_BAUDRATE_TEXT) {
            /************************* DMM_BAUDRATE *************************/
            _dmm_baudrate = __serial_definitions.getBaudrate_string(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_SERIAL_DMM_BAUDRATE_TEXT, _dmm_baudrate);
        } else if (fields.at(0) == MAINCONTTROLLER_SERIAL_DMM_DATABITS_TEXT) {
            /************************* DMM_DATABITS *************************/
            _dmm_databits = __serial_definitions.getDataBits_string(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_SERIAL_DMM_DATABITS_TEXT, _dmm_databits);
        } else if (fields.at(0) == MAINCONTTROLLER_SERIAL_DMM_STOPBITS_TEXT) {
            /************************* DMM_STOPBITS *************************/
            _dmm_stopbits = __serial_definitions.getStopBits_string(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_SERIAL_DMM_STOPBITS_TEXT, _dmm_stopbits);
        } else if (fields.at(0) == MAINCONTTROLLER_SERIAL_DMM_PARITY_TEXT) {
            /************************* DMM_PARITY *************************/
            _dmm_parity = __serial_definitions.getParity_string(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_SERIAL_DMM_PARITY_TEXT, _dmm_parity);
        } else if (fields.at(0) == MAINCONTTROLLER_SERIAL_DMM_FLOWCONTROL_TEXT) {
            /************************* DMM_FLOWCONTROL *************************/
            _dmm_flowcontrol = __serial_definitions.getFlowcontrol_string(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_SERIAL_DMM_FLOWCONTROL_TEXT, _dmm_flowcontrol);
        } else if (fields.at(0) == MAINCONTTROLLER_SERIAL_BC_BAUDRATE_TEXT) {
            /************************* BC_BAUDRATE *************************/
            _bc_baudrate = __serial_definitions.getBaudrate_string(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_SERIAL_BC_BAUDRATE_TEXT, _bc_baudrate);
        } else if (fields.at(0) == MAINCONTTROLLER_SERIAL_BC_DATABITS_TEXT) {
            /************************* BC_DATABITS *************************/
            _bc_databits = __serial_definitions.getDataBits_string(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_SERIAL_BC_DATABITS_TEXT, _bc_databits);
        } else if (fields.at(0) == MAINCONTTROLLER_SERIAL_BC_STOPBITS_TEXT) {
            /************************* BC_STOPBITS *************************/
            _bc_stopbits = __serial_definitions.getStopBits_string(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_SERIAL_BC_STOPBITS_TEXT, _bc_stopbits);
       } else if (fields.at(0) == MAINCONTTROLLER_SERIAL_BC_PARITY_TEXT) {
            /************************* BC_PARITY *************************/
            _bc_parity = __serial_definitions.getParity_string(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_SERIAL_BC_PARITY_TEXT, _bc_parity);
        } else if (fields.at(0) == MAINCONTTROLLER_SERIAL_BC_FLOWCONTROL_TEXT) {
            /************************* BC_FLOWCONTROL *************************/
            _bc_flowcontrol = __serial_definitions.getFlowcontrol_string(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_SERIAL_BC_FLOWCONTROL_TEXT, _bc_flowcontrol);
        } else {
            file.close();
            emit signal_warning_occurs(QString("Unknow parameter: %1").arg(fields.at(0)));
            return false;
        }
    }
    file.close();

    UpdateSettings();
    QStringList available_ports = Serial_definitions::getSerial_port_name();
    if(available_ports.size() > 0){
        _dmm_port = available_ports.at(0);
        _dmm_port = available_ports.at(0);
    } else {
        _dmm_port = QString();
        _bc_port = QString();
    }

    return true;
}

/******************************************************************************
 *             Name: handleSave_Project
 *      Function ID: 233
 *      Create date: 18/02/2019
 * Last modify date: 24/02/2019
 *      Description: Function for handle operations related to Save Project.
 ******************************************************************************/
void MainController::handleSave_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__;
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

    out_stream << MAINCONTTROLLER_SERIAL_DMM_BAUDRATE_TEXT    << " " << __serial_definitions.getBaudrate(_dmm_baudrate)    << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_DATABITS_TEXT    << " " << __serial_definitions.getDataBits(_dmm_databits)    << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_STOPBITS_TEXT    << " " << __serial_definitions.getStopBits(_dmm_stopbits)    << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_PARITY_TEXT      << " " << __serial_definitions.getParity(_dmm_parity)        << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_FLOWCONTROL_TEXT << " " << __serial_definitions.getFlowcontrol(_dmm_flowcontrol) << MEASUREMENTUI_DAFAULT_NEW_LINE;

    out_stream << MAINCONTTROLLER_SERIAL_BC_BAUDRATE_TEXT    << " " << __serial_definitions.getBaudrate(_bc_baudrate)    << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_BC_DATABITS_TEXT    << " " << __serial_definitions.getDataBits(_bc_databits)    << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_BC_STOPBITS_TEXT    << " " << __serial_definitions.getStopBits(_bc_stopbits)    << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_BC_PARITY_TEXT      << " " << __serial_definitions.getParity(_bc_parity)        << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_BC_FLOWCONTROL_TEXT << " " << __serial_definitions.getFlowcontrol(_bc_flowcontrol) << MEASUREMENTUI_DAFAULT_NEW_LINE;
    file.flush();
    file.close();
}

/******************************************************************************
 *             Name: handleSave_Project_As
 *      Function ID: 234
 *      Create date: 18/02/2019
 * Last modify date: 21/02/2019
 *      Description: Function for handle operations related to Save Project As.
 ******************************************************************************/
void MainController::handleSave_Project_As()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__;
#endif
    handleSave_Project();
}

/******************************************************************************
 *             Name: handle_CloseProject
 *      Function ID: 235
 *      Create date: 18/02/2019
 * Last modify date: 20/02/2019
 *      Description: Function for handle operations related to Close Project.
 ******************************************************************************/
void MainController::handleClose_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__;
#endif
    _main_window->setWindowTitle(QString(APP_NAME));
}
