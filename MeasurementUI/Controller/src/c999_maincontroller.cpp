/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 14/02/2019
 * Last modify date: 15/03/2019
 *      Description: Main window controller.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: MainController
 *      Function ID: 000
 *      Create date: 14/02/2019
 * Last modify date: 07/03/2019
 *      Description: Construction function.
 ******************************************************************************/
MainController::MainController()
{
    _sense_resistance = MAINCONTTROLLER_RESISTANCE;
    _control_resistance_max = 0;
    _start_exe_OCV = MAINCONTTROLLER_DEFAULT_START_EXECUTION_OCV;

    _output_file_name = MEASUREMENTUI_DEFAUTL_OUTPUT_FILE_NAME;
    _raw_output_file_name = MEASUREMENTUI_DEFAUTL_RAW_OUTPUT_FILE_NAME;

    _max_mAh = 0;

    initMainwindow();

    initProject_operaiton();
    initRun_operaiton();
    initFunction_operaiton();

    initSerial_operaiton();

    initChart_operaiton();

    synchronizeCurrent_path(QDir::homePath());


//    Wave_Block test(1000);
//    test.setFirst_point(100, 4.1);
//    test.setSecond_point(900, 4.0);
//    test.calculate();
//    qDebug() << "slope: " << test.slope();
//    qDebug() << "intercept: " << test.intercept();
//    qDebug() << "y_start: " << test.y_start();
//    qDebug() << "y_end: " << test.y_end();
//    qDebug() << "power: " << test.power();
}

/******************************************************************************
 *             Name: MainController
 *      Function ID: 002
 *      Create date: 18/02/2019
 * Last modify date: 04/03/2019
 *      Description: Clear all project information.
 ******************************************************************************/
void MainController::clearProject_information()
{
    _project_name.clear();
    _project_file.clear();
    _project_path.clear();
    _project_file_full_path.clear();
    _project_output_path.clear();
}

/******************************************************************************
 *             Name: signal_synchronizeCurrent_Path
 *      Function ID: 003
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Synchronize project path.
 ******************************************************************************/
void MainController::synchronizeCurrent_path(QString current_path)
{
    _current_path = current_path;
    emit signal_synchronizeCurrent_Path(current_path);
}

/******************************************************************************
 *             Name: updateProject_information
 *      Function ID: 004
 *      Create date: 18/02/2019
 * Last modify date: 15/03/2019
 *      Description: Update project information according to project name and
 *                   project path.
 ******************************************************************************/
int MainController::updateProject_information(QString project_name, QString project_path)
{
    QString previous_project_name = _project_name;
    QString previous_project_path = _project_path;

    _project_name = project_name;
    _project_path = project_path + MEASUREMENTUI_DIR_SYMBOL + _project_name;
    /** Create directory. */
    QDir dir(_project_path);
    if(dir.exists()){
        int ret = QMessageBox::warning(_main_window, tr("Directory already exists."),
                                       QString("%1 already exists, do you want to rewrite it?\n"
                                               "If you are not sure, please contact System Administrator").arg(_project_path),
                                       QMessageBox::Yes | QMessageBox::Cancel,
                                       QMessageBox::Yes);

        switch(ret){
        case QMessageBox::Yes:
            // Yes was clicked
            dir.removeRecursively();
            break;
        case QMessageBox::Cancel:
            // Cancel was clicked
            _project_name = previous_project_name;
            _project_path = previous_project_path;
            return MAINCONTROLLER_DIR_CREATE_FAIL;
        default:
            // should never be reached
            break;
        }
    }

    _project_file = _project_name + MEASUREMENTUI_DAFAULT_PROJECT_SUFFIX;
    _project_file_full_path = _project_path + MEASUREMENTUI_DIR_SYMBOL +
                              _project_name + MEASUREMENTUI_DAFAULT_PROJECT_SUFFIX;
    _project_output_path = _project_path + MEASUREMENTUI_DIR_SYMBOL + MEASUREMENTUI_DEFAUTL_OUTPUT_PAHT;
    synchronizeCurrent_path(project_path);

    QDir().mkdir(_project_path);
    QDir().mkdir(_project_output_path);

    return MAINCONTROLLER_DIR_CREATE_SUCCEED;
}

/******************************************************************************
 *             Name: updateProject_information
 *      Function ID: 005
 *      Create date: 18/02/2019
 * Last modify date: 15/03/2019
 *      Description: Update project information according to project file full
 *                   path.
 ******************************************************************************/
void MainController::updateProject_information(QString project_file_full_path)
{
    _project_name = Global_Functions::extractFile_name(project_file_full_path);
    _project_file = Global_Functions::extractFile_full_name(project_file_full_path);
    _project_path = Global_Functions::extractFile_path(project_file_full_path);
    _project_file_full_path = project_file_full_path;
    _project_output_path = _project_path + MEASUREMENTUI_DIR_SYMBOL + MEASUREMENTUI_DEFAUTL_OUTPUT_PAHT;
    synchronizeCurrent_path(_project_path);
}

/******************************************************************************
 *             Name: createWave_block
 *      Function ID: 006
 *      Create date: 28/02/2019
 * Last modify date: 05/03/2019
 *      Description: Create a new wave block by current measurement and
 *                   update it to chart.
 ******************************************************************************/
void MainController::createWave_block(int current_time)
{
    if(_half_counter == MAINCONTROLLER_FIRST_HALF){
        int relax_time = _execution_period/2 - current_time;
        if(relax_time > 0){
            _execution_capture_timer->start(relax_time);
            _half_counter = MAINCONTROLLER_SECOND_HALF;
            _first_x = current_time;
            _first_y = _data_read_buffer_current;
#ifdef MAINCONTROLLER_DEBUG
        qDebug() << "+ MainController: " << __FUNCTION__ << " The measurement operation took: " << current_time << " milliseconds";
#endif
        }
    }else {
//        _half_counter = MAINCONTROLLER_FIRST_HALF;
        qint64 second_x = current_time;
        double second_y = _data_read_buffer_current;

        Wave_Block new_block(_execution_period);
        new_block.setFirst_point(_first_x, _first_y);
        new_block.setSecond_point(second_x, second_y);
        new_block.calculate();

        qint64 time_before_this_block = _load_current_chart_view_controller->current_time();
        _load_current_chart_view_controller->addOne_new_point(1, new_block.y_start());
        _load_current_chart_view_controller->addOne_new_point(_execution_period-1, new_block.y_end());

        saveWave_data(_project_output_path + MEASUREMENTUI_DIR_SYMBOL + _output_file_name,
                      time_before_this_block+1, new_block.y_start(),
                      time_before_this_block+2000, new_block.y_end(),
                      new_block.power());

        saveWave_data(_project_output_path + MEASUREMENTUI_DIR_SYMBOL + _raw_output_file_name,
                      time_before_this_block+_first_x, _first_y,
                      time_before_this_block+second_x, second_y,
                      new_block.power());

        _total_mAh += new_block.power();
        _battery_capacity_pie_controller->setUsed_capacity(_total_mAh);
        _target_capacity_pie_controller->setUsed_capacity(_total_mAh);

#ifdef MAINCONTROLLER_DEBUG
        qDebug() << "+ MainController: " << __FUNCTION__ << " The first point: (" << _first_x << ", " << _first_y << ")";
        qDebug() << "+ MainController: " << __FUNCTION__ << " The second point: (" << second_x << ", " << second_y << ")";
        qDebug() << "+ MainController: " << __FUNCTION__ << " Power: " << new_block.power();
        qDebug() << "+ MainController: " << __FUNCTION__ << " Total power: " << _total_mAh;
        qDebug() << "+ MainController: " << __FUNCTION__ << " The measurement operation took: " << current_time -_execution_period/2 << " milliseconds";
#endif
    }
}

/******************************************************************************
 *             Name: saveWave_data
 *      Function ID: 007
 *      Create date: 04/03/2019
 * Last modify date: 05/03/2019
 *      Description: Save wave data to file with specific file path.
 ******************************************************************************/
int MainController::saveWave_data(QString file_path, qint64 time1, double value1, qint64 time2, double value2, double power_consumption)
{
    QFile output_file(file_path);
    if (output_file.open(QFile::WriteOnly | QFile::Text | QFile::Append)) {
            QTextStream out_stream(&output_file);
            out_stream << time1 << " " << value1 << MEASUREMENTUI_DAFAULT_NEW_LINE;
            out_stream << time2 << " " << value2 << " " << power_consumption  << " " << _realtime_battery_voltage << MEASUREMENTUI_DAFAULT_NEW_LINE;
            out_stream.flush();
            output_file.close();
    } else {
#ifdef MAINCONTROLLER_DEBUG
            qDebug() << "+ MainController: " << __FUNCTION__ << " Fail to open file: " << file_path;
#endif
            return 1;
    }
    return 0;
}

/******************************************************************************
 *             Name: writeOCV
 *      Function ID: 008
 *      Create date: 05/03/2019
 * Last modify date: 05/03/2019
 *      Description: Write OCV to file with specific file path.
 ******************************************************************************/
int MainController::writeOCV(QString file_path, double value)
{
    QFile output_file(file_path);
    if (output_file.open(QFile::WriteOnly | QFile::Text | QFile::Append)) {
            QTextStream out_stream(&output_file);
            out_stream << "OCV: " << " " << value << MEASUREMENTUI_DAFAULT_NEW_LINE;
            out_stream.flush();
            output_file.close();
    } else {
#ifdef MAINCONTROLLER_DEBUG
            qDebug() << "+ MainController: " << __FUNCTION__ << " Fail to open file: " << file_path;
#endif
            return 1;
    }
    return 0;
}

/******************************************************************************
 *             Name: retrieveCommand_panel_data
 *      Function ID: 009
 *      Create date: 07/03/2019
 * Last modify date: 07/03/2019
 *      Description: Retrieve all information about battery and discharging
 *                   from command panel.
 ******************************************************************************/
void MainController::retrieveCommand_panel_data()
{
    QList<double> info = _command_panel->getDischarge_information();
    _discharge_type = static_cast<int>(info.at(COMMAND_PANEL_DISCHARGE_TYPE_INDEX));
    if(_discharge_type == COMMNAD_PANEL_DISCHARGE_TYPE_SQUARE_WAVE){
        _SW_min_current = info.at(COMMAND_PANEL_SW_MIN_CURRENT_INDEX);
        _SW_max_current = info.at(COMMAND_PANEL_SW_MAX_CURRENT_INDEX);
        _SW_period = static_cast<int>(info.at(COMMAND_PANEL_SW_PERIOD_INDEX));
        _execution_period = _SW_period/2;

        _load_current_chart_view_controller->setY_range(_SW_min_current-0.5>0?_SW_min_current-0.5:0, _SW_max_current+0.5);

        _target_current_max = _SW_max_current;
        _target_current_min = _SW_min_current;
    }else {
        _CC_current = info.at(COMMAND_PANEL_CC_CURRENT_INDEX);

        _execution_period = MAINCONTTROLLER_DEFAULT_EXECUTION_TIMER_TIMEOUT;

        _load_current_chart_view_controller->setY_range(0, _CC_current+0.5);

        _target_current_max = _CC_current;
    }

    info = _command_panel->getTermination_information();
    _termination_type = static_cast<int>(info.at(COMMAND_PANEL_TERMINATION_TYPE_INDEX));
    if(_termination_type == COMMAND_PANEL_TERMINATION_TYPE_COULOMB_COUNTING){
        _TCC_coulomb = info.at(COMMAND_PANEL_TCC_COULOMB_INDEX);
        _target_capacity_pie_controller->setCapacity(_TCC_coulomb);
        _max_mAh = _TCC_coulomb;
    } else {
        _TVOC_voltage = info.at(COMMAND_PANEL_TVOC_VOLTAGE_INDEX);
    }

    _battery_capacity = _command_panel->getBattery_information();
    _battery_capacity_pie_controller->setCapacity(_battery_capacity);
}

/******************************************************************************
 *             Name: initMain_Window
 *      Function ID: 200
 *      Create date: 18/02/2019
 * Last modify date: 20/02/2019
 *      Description: Initilize functions related to Main Window..
 ******************************************************************************/
void MainController::initMainwindow()
{
    _main_window = new MainWindow();
    connect(this, &MainController::signal_synchronizeCurrent_Path, _main_window, &MainWindow::slot_update_current_path);
    connect(this, &MainController::signal_warning_occurs, _main_window, &MainWindow::slot_display_warning_message_box);
}

/******************************************************************************
 *             Name: initProject_operaiton
 *      Function ID: 201
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Initilize functions related to Project operations.
 ******************************************************************************/
void MainController::initProject_operaiton()
{
    initNew_Project();
    initOpen_Project();
    initSave_Project();
    initSave_Project_As();
    initClose_Project();
}

/******************************************************************************
 *             Name: initRun_operaiton
 *      Function ID: 202
 *      Create date: 18/02/2019
 * Last modify date: 19/02/2019
 *      Description: Initilize functions related to Run operations.
 ******************************************************************************/
void MainController::initRun_operaiton()
{
    initStart();
    initStop();
}

/******************************************************************************
 *             Name: initFunction_operaiton
 *      Function ID: 203
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Initilize functions related to Function operations.
 ******************************************************************************/
void MainController::initFunction_operaiton()
{
    initSettings();
    initCommand_Panel();
    initOutput_Panel();
    initQuit();
}

/******************************************************************************
 *             Name: initSerial_operaiton
 *      Function ID: 204
 *      Create date: 21/02/2019
 * Last modify date: 05/03/2019
 *      Description: Initilize functions related to Serial operations.
 ******************************************************************************/
void MainController::initSerial_operaiton()
{
    _execution_command = MAINCONTROLLER_EXE_COMMAND_STOP;
    _sampling_command = MAINCONTROLLER_VOLT_COMMAND_STOP;
//    _sampling_command_current = MAINCONTROLLER_CURR_COMMAND_STOP;
    /** Battery control serial settings */
    _BC_controller = new Serial_Controller(SERIAL_CONTROLLER_TYPE_BC);
    connect(_BC_controller, &Serial_Controller::signal_pure_data_received, this, &MainController::slot_battery_voltage_received);

    _execution_timer = new QTimer();
    connect(_execution_timer, &QTimer::timeout, this, &MainController::slot_change_load_current);
    _execution_capture_timer = new QTimer();
    connect(_execution_capture_timer, &QTimer::timeout, this, &MainController::slot_start_second_half_meausurement);
    _execution_elapsed_timer = new QElapsedTimer();
    _execution_calibrate_timer = new QTimer();

    /** Battery voltage measurement serial settings */
    _DMM_controller = new Serial_Controller(SERIAL_CONTROLLER_TYPE_DMM);
    connect(_DMM_controller, &Serial_Controller::data_received, this, &MainController::slot_retrieveDMM_data);

    _capture_timer = new QTimer();
    _capture_timer_timeout = MAINCONTTROLLER_DEFAULT_CAPTURE_TIMER_TIMEOUT;
    connect(_capture_timer, &QTimer::timeout, this, &MainController::slot_read_serial_buffer);

    /** Load current measurement serial settings */
    _DMM_controller_current = new Serial_Controller(SERIAL_CONTROLLER_TYPE_DMM);
    connect(_DMM_controller_current, &Serial_Controller::data_received, this, &MainController::slot_retrieveDMM_data_for_current);
//    connect(_DMM_controller_current, &Serial_Controller::signal_pure_data_received, this, &MainController::slot_battery_voltage_received);

//    _capture_timer_current = new QTimer();
//    _capture_timer_timeout_current = MAINCONTTROLLER_DEFAULT_CAPTURE_TIMER_TIMEOUT;
//    connect(_capture_timer_current, &QTimer::timeout, this, &MainController::slot_read_serial_buffer_for_current);
    _voltage_capture_timer = new QTimer();
     connect(_voltage_capture_timer, &QTimer::timeout, this, &MainController::slot_read_battery_voltage);

     _OCV_timer = new QTimer();
     connect(_OCV_timer, &QTimer::timeout, this, &MainController::slot_save_OCV);
}

/******************************************************************************
 *             Name: initChart_operaiton
 *      Function ID: 205
 *      Create date: 21/02/2019
 * Last modify date: 07/03/2019
 *      Description: Initilize functions related to Chart operations.
 ******************************************************************************/
void MainController::initChart_operaiton(){
    _battery_voltage_chart_view_controller = new Chart_Controller(tr("Battery Voltage"), CHART_CONTROLLER_DEFAULT_TIME_RANGE, tr("V"));
    _main_window->addBettery_voltage_chart_view(_battery_voltage_chart_view_controller->getChart_view());
    _load_current_chart_view_controller = new Chart_Controller(tr("Load Current"), CHART_CONTROLLER_DEFAULT_TIME_RANGE, tr("A"));
    _main_window->addLoad_current_chart_view(_load_current_chart_view_controller->getChart_view());
    _battery_capacity_pie_controller = new Pie_Controller("Battery Capatity");
    _main_window->addBattery_capacity_chart_view(_battery_capacity_pie_controller->getChart_view());
    _target_capacity_pie_controller  = new Pie_Controller(QString("Target Capatity"));
    _main_window->addTarget_capacity_chart_view(_target_capacity_pie_controller->getChart_view());
}

/******************************************************************************
 *             Name: initNew_Project
 *      Function ID: 211
 *      Create date: 16/02/2019
 * Last modify date: 18/02/2019
 *      Description: Initilize functions related to New Project operations.
 ******************************************************************************/
void MainController::initNew_Project()
{
    _new_project_dialog = new New_Project_Dialog(_main_window);
    /** Connect signals and slots related to click New Project menu action button in main window. */
    connect(_main_window, &MainWindow::signal_new_project_menu_action_triggered, _new_project_dialog, &New_Project_Dialog::slot_trigger_new_project_dialog);
    connect(_new_project_dialog, &New_Project_Dialog::signal_new_project_comfirmed, this, &MainController::slot_create_new_project);
    connect(this, &MainController::signal_synchronizeCurrent_Path, _new_project_dialog, &New_Project_Dialog::slot_update_current_path);
}

/******************************************************************************
 *             Name: initOpen_Project
 *      Function ID: 212
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Initilize functions related to Open Project operations.
 ******************************************************************************/
void MainController::initOpen_Project()
{
    /** Connect signals and slots related to click Open menu action button in main window. */
    connect(_main_window, &MainWindow::signal_open_project_menu_action_triggered, this, &MainController::slot_open_project);
}

/******************************************************************************
 *             Name: initSave_Project
 *      Function ID: 213
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Initilize functions related to Save Project operations.
 ******************************************************************************/
void MainController::initSave_Project()
{
    /** Connect signals and slots related to click Save Project menu action button in main window. */
    connect(_main_window, &MainWindow::signal_save_project_menu_action_triggered, this, &MainController::slot_save_project);
}

/******************************************************************************
 *             Name: initSave_Project_As
 *      Function ID: 214
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Initilize functions related to Save Project As operations.
 ******************************************************************************/
void MainController::initSave_Project_As()
{
    /** Connect signals and slots related to click Save Project As menu action button in main window. */
    connect(_main_window, &MainWindow::signal_save_project_as_menu_action_triggered, this, &MainController::slot_save_project_as);
}

/******************************************************************************
 *             Name: initClose_Project
 *      Function ID: 215
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Initilize functions related to Close project operations.
 ******************************************************************************/
void MainController::initClose_Project()
{
    /** Connect signals and slots related to click Close Project menu action button in main window. */
    connect(_main_window, &MainWindow::signal_close_project_menu_action_triggered, this, &MainController::slot_close_project);
}

/******************************************************************************
 *             Name: initStart
 *      Function ID: 216
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Initilize functions related to Start operations.
 ******************************************************************************/
void MainController::initStart()
{
    /** Connect signals and slots related to click Start menu action button in main window. */
    connect(_main_window, &MainWindow::signal_start_menu_action_triggered, this, &MainController::slot_Start);
}

/******************************************************************************
 *             Name: initStop
 *      Function ID: 217
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Initilize functions related to Stop operations.
 ******************************************************************************/
void MainController::initStop()
{
    /** Connect signals and slots related to click Stop menu action button in main window. */
    connect(_main_window, &MainWindow::signal_stop_menu_action_triggered, this, &MainController::slot_Stop);
}

/******************************************************************************
 *             Name: initSettings
 *      Function ID: 218
 *      Create date: 19/02/2019
 * Last modify date: 24/02/2019
 *      Description: Initilize functions related to Settings operations.
 ******************************************************************************/
void MainController::initSettings()
{
    _settings_dialog = new Settings_Dialog(_main_window);
    _setting_dialog_controller = new Settings_Dialog_Controller(_settings_dialog);
    /** Connect signals and slots related to click Settings menu action button in main window. */
    connect(_main_window, &MainWindow::signal_settings_menu_action_triggered, this, &MainController::slot_settings);
    /** Connect signals and slots related to close Settings dialog. */
    connect(_settings_dialog, &Settings_Dialog::accepted, _main_window, &MainWindow::slot_close_settings_dialog);
    connect(_settings_dialog, &Settings_Dialog::rejected, _main_window, &MainWindow::slot_close_settings_dialog);
    /** Connect signals and slots related to clicl Apply button in Settings Dialog. */
    connect(_setting_dialog_controller, &Settings_Dialog_Controller::signal_modification_confirmed, this, &MainController::slot_update_data_from_settings);
}

/******************************************************************************
 *             Name: initCommand_Panel
 *      Function ID: 219
 *      Create date: 19/02/2019
 * Last modify date: 20/02/2019
 *      Description: Initilize functions related to Command Panel operations.
 ******************************************************************************/
void MainController::initCommand_Panel()
{
    _command_panel = new Command_Panel(_main_window);
    /** Connect signals and slots related to click Command panel menu action button in main window. */
    connect(_main_window, &MainWindow::signal_command_panel_menu_action_triggered, this, &MainController::slot_command_panel);
    /** Connect signals and slots related to close Command panel. */
    connect(_command_panel, &Command_Panel::rejected, _main_window, &MainWindow::slot_close_command_panel);
}

/******************************************************************************
 *             Name: initOutput_Panel
 *      Function ID: 220
 *      Create date: 19/02/2019
 * Last modify date: 20/02/2019
 *      Description: Initilize functions related to Output Panel operations.
 ******************************************************************************/
void MainController::initOutput_Panel()
{
    _output_panel = new Output_Panel(_main_window);
    /** Connect signals and slots related to click Output menu action button in main window. */
    connect(_main_window, &MainWindow::signal_output_panel_menu_action_triggered, this, &MainController::slot_output_panel);
    /** Connect signals and slots related to close Output panel. */
    connect(_output_panel, &Output_Panel::rejected, _main_window, &MainWindow::slot_close_output_panel);
}

/******************************************************************************
 *             Name: initQuit
 *      Function ID: 222
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Initilize functions related to Quit operations.
 ******************************************************************************/
void MainController::initQuit()
{
    /** Connect signals and slots related to click Quit menu action button in main window. */
    connect(_main_window, &MainWindow::signal_quit_menu_action_triggered, this, &MainController::slot_Quit);
    connect(this, &MainController::signal_confirm_quit_application, _main_window, &MainWindow::slot_confirm_quit_application);
}

/******************************************************************************
 *             Name: showMain_Window
 *      Function ID: 299
 *      Create date: 16/02/2019
 * Last modify date: 16/02/2019
 *      Description: Show main window.
 ******************************************************************************/
void MainController::showMainwindow()
{
    _main_window->show();
}


/******************************************************************************
 *             Name: UpdateSettings
 *      Function ID: 300
 *      Create date: 21/02/2019
 * Last modify date: 15/03/2019
 *      Description: Update all settings opertions.
 ******************************************************************************/
void MainController::updateSettings()
{
    QList<QStringList> data_list;
    QStringList data_list_dmm;
    QStringList data_list_bc;

    data_list_dmm.append(_dmm_baudrate);
    data_list_dmm.append(_dmm_databits);
    data_list_dmm.append(_dmm_stopbits);
    data_list_dmm.append(_dmm_parity);
    data_list_dmm.append(_dmm_flowcontrol);
    data_list_dmm.append(_dmm_port);

    data_list_bc.append(_bc_baudrate);
    data_list_bc.append(_bc_databits);
    data_list_bc.append(_bc_stopbits);
    data_list_bc.append(_bc_parity);
    data_list_bc.append(_bc_flowcontrol);
    data_list_bc.append(_bc_port);

    data_list.append(data_list_dmm);
    data_list.append(data_list_bc);

    _setting_dialog_controller->updataeAll_frames(data_list);
}

/******************************************************************************
 *             Name: captureOne_measurement
 *      Function ID: 301
 *      Create date: 25/02/2019
 * Last modify date: 26/02/2019
 *      Description: Capture one measurement.
 ******************************************************************************/
void MainController::captureOne_measurement()
{
    _sampling_command = MAINCONTROLLER_VOLT_COMMAND_RUN;

    _DMM_controller->writeDMM_command(":SYST:REM", false);
    _DMM_controller->writeDMM_command(MEASUREMENTUI_VOLTAGE_COMMAND);
#ifdef MAINCONTROLLER_DEBUG
    _elapsed_timer.start();
#endif
    _capture_timer->start(_capture_timer_timeout);
}

/******************************************************************************
 *             Name: startExecution
 *      Function ID: 302
 *      Create date: 27/02/2019
 * Last modify date: 01/03/2019
 *      Description: Start exeuction of meausuremnt.
 ******************************************************************************/
void MainController::startExecution(uint8_t resistance)
{
    _execution_timer->start(_execution_period);
    _execution_elapsed_timer->start();
    _execution_command = MAINCONTROLLER_EXE_COMMAND_RUN;
    _half_counter = MAINCONTROLLER_FIRST_HALF;

#ifdef MAINCONTROLLER_DEBUG
//    int value_to_be_set;
//    if(test_counter == 4) {
//        test_counter = 0;
//    }
//    value_to_be_set = test_counter*80;
//    test_counter++;
//    _BC_controller->sendMCU_Value(static_cast<char>(value_to_be_set));
#endif

    _BC_controller->sendMCU_Value(static_cast<char>(resistance));

    _execution_capture_timer->start(0);
//    _DMM_controller_current->writeDMM_command(":SYST:REM", false);
//    _DMM_controller_current->writeDMM_command(MEASUREMENTUI_VOLTAGE_COMMAND);

#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__ << "- set Value: " << resistance;
#endif
}

/******************************************************************************
 *             Name: startCalibration_max
 *      Function ID: 303
 *      Create date: 28/02/2019
 * Last modify date: 07/03/2019
 *      Description: Start calibration of max current.
 ******************************************************************************/
void MainController::startCalibration_max()
{
    _execution_command = MAINCONTROLLER_EXE_COMMAND_CALIBRATION_MAX;
    _control_resistance_max = 255;
    _calibration_factor = 0;

    _BC_controller->sendMCU_Value(static_cast<char>(_control_resistance_max));

    _DMM_controller_current->writeDMM_command(":SYST:REM", false);
    _DMM_controller_current->writeDMM_command(MEASUREMENTUI_VOLTAGE_COMMAND);
}

/******************************************************************************
 *             Name: startCalibration_min
 *      Function ID: 304
 *      Create date: 07/03/2019
 * Last modify date: 07/03/2019
 *      Description: Start calibration of min current.
 ******************************************************************************/
void MainController::startCalibration_min()
{
    _execution_command = MAINCONTROLLER_EXE_COMMAND_CALIBRATION_MIN;
    _control_resistance_min = 255;
    _calibration_factor = 0;

    _BC_controller->sendMCU_Value(static_cast<char>(_control_resistance_min));

    _execution_capture_timer->start(0);
//    _DMM_controller_current->writeDMM_command(":SYST:REM", false);
//    _DMM_controller_current->writeDMM_command(MEASUREMENTUI_VOLTAGE_COMMAND);
}

/******************************************************************************
 *             Name: startMeasurement
 *      Function ID: 305
 *      Create date: 05/03/2019
 * Last modify date: 15/03/2019
 *      Description: Start meausuremnt from capturing OCV.
 ******************************************************************************/
void MainController::startMeasurement()
{
    _execution_elapsed_timer->start();
    _execution_command = MAINCONTROLLER_EXE_COMMAND_PREPARATION;
    retrieveCommand_panel_data();
    _toggle_flag = MAINCONTROLLER_TOGGLE_FLAG_ON;
    _total_mAh = 0;
    _start_record = false;

    _battery_voltage_chart_view_controller->setY_range(2.0, 4.5);

    _BC_controller->sendMCU_Value(0);
    _OCV_timer->start(500);
}

/******************************************************************************
 *             Name: printData_read_from_project_file
 *      Function ID: 600
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Print data read from project file.
 ******************************************************************************/
void MainController::printData_read_from_project_file(QString domain, QString content)
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << domain << " " << content;
#endif
}

/******************************************************************************
 *             Name: slot_create_new_project
 *      Function ID: 700
 *      Create date: 16/02/2019
 * Last modify date: 15/03/2019
 *      Description: Slot for new project created.
 ******************************************************************************/
void MainController::slot_create_new_project(QString project_name, QString project_path)
{
    if(!updateProject_information(project_name, project_path)){
        if(handleNew_Project()){
            _main_window->setWindowTitle(QString("%1 - %2").arg(APP_NAME).arg(_project_name));
            _main_window->changeDisplay_status(MAINWINDOW_PROJECT_ACTIVATE);
        }
    }

#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: New Project";
    printProject_information();
#endif
}

/******************************************************************************
 *             Name: slot_open_project
 *      Function ID: 701
 *      Create date: 18/02/2019
 * Last modify date: 20/02/2019
 *      Description: Slot for open a project.
 ******************************************************************************/
void MainController::slot_open_project(QString project_file_full_path)
{
    if(project_file_full_path.length() > 0){
        updateProject_information(project_file_full_path);

        if(handleOpen_Project()){
            _main_window->setWindowTitle(QString("%1 - %2").arg(APP_NAME).arg(_project_name));
            _main_window->changeDisplay_status(MAINWINDOW_PROJECT_ACTIVATE);
        }
    }

#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: Open Project";
    printProject_information();
#endif
}

/******************************************************************************
 *             Name: slot_save_project
 *      Function ID: 702
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Slot for saving current project.
 ******************************************************************************/
void MainController::slot_save_project()
{
    handleSave_Project();

#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: Save Project";
    printProject_information();
#endif
}

/******************************************************************************
 *             Name: slot_save_project_as
 *      Function ID: 703
 *      Create date: 18/02/2019
 * Last modify date: 15/03/2019
 *      Description: Slot for saving project as another project.
 ******************************************************************************/
void MainController::slot_save_project_as(QString project_file_full_path)
{
    if(project_file_full_path.length() > 0){
        if(!updateProject_information(Global_Functions::extractFile_name(project_file_full_path),
                                      Global_Functions::extractFile_path(project_file_full_path))){
            handleSave_Project_As();
            _main_window->setWindowTitle(QString("%1 - %2").arg(APP_NAME).arg(_project_name));
        }
    }
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: Save Project as";
    printProject_information();
#endif
}

/******************************************************************************
 *             Name: slot_close_project
 *      Function ID: 704
 *      Create date: 18/02/2019
 * Last modify date: 15/03/2019
 *      Description: Slot for current project closed.
 ******************************************************************************/
void MainController::slot_close_project()
{
    clearProject_information();

    handleClose_Project();

    _main_window->resetAll_menu_actions();
    _command_panel->hide();
    _settings_dialog->hide();
    _main_window->setWindowTitle(QString(APP_NAME));

    _battery_voltage_chart_view_controller->reset();
    _load_current_chart_view_controller->reset();
    _battery_capacity_pie_controller->reset();
    _target_capacity_pie_controller->reset();

#ifdef MAINCONTROLLER_DEBUG
    clearProject_information();
    qDebug() << "+ MainController: Close Project";
    printProject_information();
#endif
}

/******************************************************************************
 *             Name: slot_Start
 *      Function ID: 705
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Slot for starting new measrement.
 ******************************************************************************/
void MainController::slot_Start()
{
    handleStart();
}

/******************************************************************************
 *             Name: slot_Stop
 *      Function ID: 706
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Slot for stoping current measurement.
 ******************************************************************************/
void MainController::slot_Stop()
{
    handleStop();
}

/******************************************************************************
 *             Name: slot_settings
 *      Function ID: 707
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Slot for displaying Settings panel.
 ******************************************************************************/
void MainController::slot_settings()
{
    handleSettings();
}

/******************************************************************************
 *             Name: slot_command_panel
 *      Function ID: 708
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Slot for displaying Command panel.
 ******************************************************************************/
void MainController::slot_command_panel()
{
    handleCommand_Panel();
}

/******************************************************************************
 *             Name: slot_output_panel
 *      Function ID: 709
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Slot for displaying Output panel.
 ******************************************************************************/
void MainController::slot_output_panel()
{
    handleOutput_Panel();
}

/******************************************************************************
 *             Name: slot_Stop
 *      Function ID: 711
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Slot for quiting application.
 ******************************************************************************/
void MainController::slot_Quit()
{
    emit signal_confirm_quit_application();
}

#ifdef MAINCONTROLLER_DEBUG
/******************************************************************************
 *             Name: printProject_Information -Debug function
 *      Function ID: 900
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Print project information.
 ******************************************************************************/
void MainController::printProject_information()
{
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "Project name: " << _project_name;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "Project file: " << _project_file;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "Project path: " << _project_path;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "Project file full path: " <<  _project_file_full_path;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "Current path: " <<  _current_path;
    qDebug() << DEBUG_SPLIT_LINE;
}

/******************************************************************************
 *             Name: debug_slot_printDebug_info1 -Debug function
 *      Function ID: 901
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Print debug information.
 ******************************************************************************/
void MainController::debug_slot_printDebug_info1()
{
    qDebug() << "printDebug_info1";
}

/******************************************************************************
 *             Name: debug_slot_printDebug_info2 -Debug function
 *      Function ID: 902
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Print debug information.
 ******************************************************************************/
void MainController::debug_slot_printDebug_info2()
{
    qDebug() << "printDebug_info2";
}

/******************************************************************************
 *             Name: debug_printSerial_inforation -Debug function
 *      Function ID: 903
 *      Create date: 24/02/2019
 * Last modify date: 24/02/2019
 *      Description: Print serial information.
 ******************************************************************************/
void MainController::debug_printSerial_information()
{
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "DMM Current Port"            << _dmm_port;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_SERIAL_DMM_BAUDRATE_TEXT << _dmm_baudrate;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_SERIAL_DMM_DATABITS_TEXT << _dmm_databits;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_SERIAL_DMM_BAUDRATE_TEXT << _dmm_stopbits;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_SERIAL_DMM_PARITY_TEXT   <<  _dmm_parity;;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_SERIAL_DMM_FLOWCONTROL_TEXT << _dmm_flowcontrol;

    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "BC Current Port"            << _bc_port;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_SERIAL_BC_BAUDRATE_TEXT << _bc_baudrate;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_SERIAL_BC_DATABITS_TEXT << _bc_databits;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_SERIAL_BC_BAUDRATE_TEXT << _bc_stopbits;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_SERIAL_BC_PARITY_TEXT   <<  _bc_parity;;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_SERIAL_BC_FLOWCONTROL_TEXT << _bc_flowcontrol;
}
#endif
