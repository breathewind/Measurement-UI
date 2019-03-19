/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 18/02/2019
 * Last modify date: 19/03/2019
 *      Description: Main window controller.
 *                   - Functions related to file menu actions.
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: handleNew_Project
 *      Function ID: 231
 *      Create date: 18/02/2019
 * Last modify date: 19/03/2019
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
        _bc_port = available_ports.at(0);
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

    /** Create project file. */
    QFile file(_project_file_full_path);
    if (!file.open(QFile::WriteOnly | QFile::Text )) {
        emit signal_warning_occurs(QString("Fail to create file: %1").arg(_project_file_full_path));
        return false;
    }
    QTextStream out_stream(&file);    
/************************* GENERAL SETTINGS *************************/
    out_stream << MAINCONTTROLLER_SETTINGS_DISPLAY_TEXT      << " 0" << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_COMMAND_PANEL_DISPLAY_TEXT << " 1" << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_OUTPUT_PANEL_DISPLAY_TEXT  << " 0" << MEASUREMENTUI_DAFAULT_NEW_LINE;
/************************* SERIAL SETTINGS FROM SETTINGS DIALOG *************************/
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
/************************* DISCHARGE SETTINGS FROM COMMAND PANEL *************************/
    out_stream << MAINCONTTROLLER_DISCHARGE_TYPE_TEXT             <<  " " << COMMNAD_PANEL_DISCHARGE_TYPE_SQUARE_WAVE        << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_MIN_DISCHARGE_CURRENT_TEXT      <<  " " << COMMAND_PANEL_DEFAULT_SW_MIN_I                  << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_MAX_DISCHARGE_CURRENT_TEXT      <<  " " << COMMAND_PANEL_DEFAULT_SW_MAX_I                  << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SQUARE_WAVE_PERIOD_TEXT         <<  " " << COMMAND_PANEL_DEFAULT_SW_PERIOD                 << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_CONSTANT_DISCHARGE_CURRENT_TEXT <<  " " << COMMAND_PANEL_DEFAULT_CC_CURRENT                << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_TERMINATION_TYPE_TEXT           <<  " " << COMMAND_PANEL_TERMINATION_TYPE_COULOMB_COUNTING << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_TARGET_TCC_TEXT                 <<  " " << COMMAND_PANEL_DEFAULT_TCC_COULOMB               << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_TARGET_TOCV_TEXT                <<  " " << COMMAND_PANEL_DEFAULT_TOCV_OCV                  << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_RATE_CAPACITY_TEXT              <<  " " << COMMAND_PANEL_DEFAULT_RATE_CAPACITY             << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SAVE_FLAG_TEXT                  <<  " " << COMMAND_PANEL_SAVE_FILE_CHECKED                 << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SAVE_PATH_TEXT                  <<  " " << _project_output_path + MEASUREMENTUI_DIR_SYMBOL + _output_file_name  << MEASUREMENTUI_DAFAULT_NEW_LINE;

    file.flush();
    file.close();
    /** Show command panel when a new project is created. */
    _command_panel->setDefault(_project_output_path + MEASUREMENTUI_DIR_SYMBOL + _output_file_name);

    _main_window->setCommand_panel_action_checked(true);
    _command_panel->showDialog();
    /** Hide settings dialog when a new project is created. */
    _main_window->setSettings_action_checked(false);
    _settings_dialog->hide();
    /** Hide output panel when a new project is created. */
    _main_window->setOutput_panel_action_checked(false);
    _output_panel->hide();

    /** Reset all dialogs */
    _setting_dialog_controller->resetAll_frames();
    _battery_voltage_chart_view_controller->reset();
    _load_current_chart_view_controller->reset();
    _battery_capacity_pie_controller->reset();
    _target_capacity_pie_controller->reset();

    return true;
}

/******************************************************************************
 *             Name: handleOpen_Project
 *      Function ID: 232
 *      Create date: 18/02/2019
 * Last modify date: 15/03/2019
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

 /************************* GENERAL SETTINGS *************************/
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
        } else
/************************* SERIAL SETTINGS FROM SETTINGS DIALOG *************************/
            if (fields.at(0) == MAINCONTTROLLER_SERIAL_DMM_BAUDRATE_TEXT) {
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
        } else
/************************* DISCHARGE SETTINGS FROM COMMAND PANEL *************************/
            if (fields.at(0) == MAINCONTTROLLER_DISCHARGE_TYPE_TEXT) {
            /************************* DISCHARGE_TYPE *************************/
            _command_panel->setDischargeType(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_DISCHARGE_TYPE_TEXT, fields.at(1));
        } else if (fields.at(0) == MAINCONTTROLLER_MIN_DISCHARGE_CURRENT_TEXT) {
            /************************* MIN_DISCHARGE_CURRENT *************************/
            _command_panel->setMinDischargeCurrent(fields.at(1));
            printData_read_from_project_file(MAINCONTTROLLER_MIN_DISCHARGE_CURRENT_TEXT, fields.at(1));
        } else if (fields.at(0) == MAINCONTTROLLER_MAX_DISCHARGE_CURRENT_TEXT) {
            /************************* MAX_DISCHARGE_CURRENT *************************/
            _command_panel->setMaxDischargeCurrent(fields.at(1));
            printData_read_from_project_file(MAINCONTTROLLER_MAX_DISCHARGE_CURRENT_TEXT, fields.at(1));
        } else if (fields.at(0) == MAINCONTTROLLER_SQUARE_WAVE_PERIOD_TEXT) {
            /************************* SQUARE_WAVE_PERIOD *************************/
            _command_panel->setSquareWavePeriod(fields.at(1));
            printData_read_from_project_file(MAINCONTTROLLER_SQUARE_WAVE_PERIOD_TEXT, fields.at(1));
        } else if (fields.at(0) == MAINCONTTROLLER_CONSTANT_DISCHARGE_CURRENT_TEXT) {
            /************************* CONSTANT_DISCHARGE_CURRENT *************************/
            _command_panel->setConstantDischargeCurrent(fields.at(1));
            printData_read_from_project_file(MAINCONTTROLLER_CONSTANT_DISCHARGE_CURRENT_TEXT, fields.at(1));
        } else if (fields.at(0) == MAINCONTTROLLER_TERMINATION_TYPE_TEXT) {
             /************************* TERMINATION_TYPE *************************/
             _command_panel->setTerminationType(fields.at(1).toInt());
             printData_read_from_project_file(MAINCONTTROLLER_TERMINATION_TYPE_TEXT, fields.at(1));
        } else if (fields.at(0) == MAINCONTTROLLER_TARGET_TCC_TEXT) {
             /************************* TARGET_TCC *************************/
             _command_panel->setTargetCoulomb(fields.at(1));
             printData_read_from_project_file(MAINCONTTROLLER_TARGET_TCC_TEXT, fields.at(1));
        } else if (fields.at(0) == MAINCONTTROLLER_TARGET_TOCV_TEXT) {
             /************************* TARGET_TOCV *************************/
             _command_panel->setTargetOCV(fields.at(1));
             printData_read_from_project_file(MAINCONTTROLLER_TARGET_TOCV_TEXT, fields.at(1));
        } else if (fields.at(0) == MAINCONTTROLLER_RATE_CAPACITY_TEXT) {
             /************************* RATE_CAPACITY *************************/
             _command_panel->setRateCapacity(fields.at(1));
             printData_read_from_project_file(MAINCONTTROLLER_RATE_CAPACITY_TEXT, fields.at(1));
        } else if (fields.at(0) == MAINCONTTROLLER_SAVE_FLAG_TEXT) {
             /************************* SAVE_FLAG *************************/
             _command_panel->setSaveFlag(fields.at(1).toInt());
             printData_read_from_project_file(MAINCONTTROLLER_SAVE_FLAG_TEXT, fields.at(1));
        } else if (fields.at(0) == MAINCONTTROLLER_SAVE_PATH_TEXT) {
             /************************* SAVE_PATH *************************/
             _command_panel->setSavePath(fields.at(1));
             printData_read_from_project_file(MAINCONTTROLLER_SAVE_PATH_TEXT, fields.at(1));
        } else {
            file.close();
            emit signal_warning_occurs(QString("Unknow parameter: %1").arg(fields.at(0)));
            return false;
        }
    }
    file.close();

    updateSettings();
    QStringList available_ports = Serial_definitions::getSerial_port_name();
    _dmm_port = available_ports.size() > 0? available_ports.at(0):QString();

    _battery_voltage_chart_view_controller->reset();
    _load_current_chart_view_controller->reset();
    _battery_capacity_pie_controller->reset();
    _target_capacity_pie_controller->reset();

    return true;
}

/******************************************************************************
 *             Name: handleSave_Project
 *      Function ID: 233
 *      Create date: 18/02/2019
 * Last modify date: 19/03/2019
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

    QStringList discharge_settings = _command_panel->getAllInformation();

    QTextStream out_stream(&file);
/************************* GENERAL SETTINGS *************************/
    out_stream << MAINCONTTROLLER_SETTINGS_DISPLAY_TEXT      << " " << _main_window->getSettings_action_checked()      << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_COMMAND_PANEL_DISPLAY_TEXT << " " << _main_window->getCommand_panel_action_checked() << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_OUTPUT_PANEL_DISPLAY_TEXT  << " " << _main_window->getOutput_panel_action_checked()  << MEASUREMENTUI_DAFAULT_NEW_LINE;
/************************* SERIAL SETTINGS FROM SETTINGS DIALOG *************************/
    out_stream << MAINCONTTROLLER_SERIAL_DMM_BAUDRATE_TEXT    << " " << __serial_definitions.getBaudrate(_dmm_baudrate)       << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_DATABITS_TEXT    << " " << __serial_definitions.getDataBits(_dmm_databits)       << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_STOPBITS_TEXT    << " " << __serial_definitions.getStopBits(_dmm_stopbits)       << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_PARITY_TEXT      << " " << __serial_definitions.getParity(_dmm_parity)           << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_FLOWCONTROL_TEXT << " " << __serial_definitions.getFlowcontrol(_dmm_flowcontrol) << MEASUREMENTUI_DAFAULT_NEW_LINE;

    out_stream << MAINCONTTROLLER_SERIAL_BC_BAUDRATE_TEXT    << " " << __serial_definitions.getBaudrate(_bc_baudrate)       << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_BC_DATABITS_TEXT    << " " << __serial_definitions.getDataBits(_bc_databits)       << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_BC_STOPBITS_TEXT    << " " << __serial_definitions.getStopBits(_bc_stopbits)       << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_BC_PARITY_TEXT      << " " << __serial_definitions.getParity(_bc_parity)           << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_BC_FLOWCONTROL_TEXT << " " << __serial_definitions.getFlowcontrol(_bc_flowcontrol) << MEASUREMENTUI_DAFAULT_NEW_LINE;
/************************* DISCHARGE SETTINGS FROM COMMAND PANEL *************************/
    out_stream << MAINCONTTROLLER_DISCHARGE_TYPE_TEXT             <<  " " << discharge_settings.at(COMMAND_PANEL_DISCHARGE_TYPE_ALL_INDEX)   << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_MIN_DISCHARGE_CURRENT_TEXT      <<  " " << discharge_settings.at(COMMAND_PANEL_SW_MIN_CURRENT_ALL_INDEX)   << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_MAX_DISCHARGE_CURRENT_TEXT      <<  " " << discharge_settings.at(COMMAND_PANEL_SW_MAX_CURRENT_ALL_INDEX)   << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SQUARE_WAVE_PERIOD_TEXT         <<  " " << discharge_settings.at(COMMAND_PANEL_SW_PERIOD_ALL_INDEX)        << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_CONSTANT_DISCHARGE_CURRENT_TEXT <<  " " << discharge_settings.at(COMMAND_PANEL_CC_CURRENT_ALL_INDEX)       << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_TERMINATION_TYPE_TEXT           <<  " " << discharge_settings.at(COMMAND_PANEL_TERMINATION_TYPE_ALL_INDEX) << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_TARGET_TCC_TEXT                 <<  " " << discharge_settings.at(COMMAND_PANEL_TCC_COULOMB_ALL_INDEX)      << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_TARGET_TOCV_TEXT                <<  " " << discharge_settings.at(COMMAND_PANEL_TVOC_VOLTAGE_ALL_INDEX)     << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_RATE_CAPACITY_TEXT              <<  " " << discharge_settings.at(COMMAND_PANEL_RATE_CAPACITY_ALL_INDEX)    << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SAVE_FLAG_TEXT                  <<  " " << discharge_settings.at(COMMAND_PANEL_SAVE_FLAG_ALL_INDEX)        << MEASUREMENTUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SAVE_PATH_TEXT                  <<  " " << discharge_settings.at(COMMAND_PANEL_SAVE_PATH_ALL_INDEX)        << MEASUREMENTUI_DAFAULT_NEW_LINE;

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
 * Last modify date: 15/03/2019
 *      Description: Function for handle operations related to Close Project.
 ******************************************************************************/
void MainController::handleClose_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__;
#endif
}
