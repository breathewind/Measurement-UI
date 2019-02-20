/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 14/02/2019
 * Last modify date: 20/02/2019
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
 * Last modify date: 18/02/2019
 *      Description: Construction function.
 ******************************************************************************/
MainController::MainController()
{
    initMainwindow();
    initProject_operaiton();
    initRun_operaiton();
    initFunction_operaiton();

    synchronizeCurrent_path(QDir::homePath());
}

/******************************************************************************
 *             Name: MainController
 *      Function ID: 002
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Clear all project information.
 ******************************************************************************/
void MainController::clearProject_information()
{
    _project_name.clear();
    _project_file.clear();
    _project_path.clear();
    _project_file_full_path.clear();
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
 * Last modify date: 19/02/2019
 *      Description: Update project information according to project name and
 *                   project path.
 ******************************************************************************/
void MainController::updateProject_information(QString project_name, QString project_path)
{
    _project_name = project_name;
    _project_file = _project_name + MEASUREMENTUI_DAFAULT_PROJECT_SUFFIX;
    _project_path = project_path + MEASUREMENTUI_DIR_SYMBOL + _project_name;
    _project_file_full_path = _project_path + MEASUREMENTUI_DIR_SYMBOL +
                              _project_name + MEASUREMENTUI_DAFAULT_PROJECT_SUFFIX;
    synchronizeCurrent_path(project_path);
}

/******************************************************************************
 *             Name: updateProject_information
 *      Function ID: 005
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Update project information according to project file full
 *                   path.
 ******************************************************************************/
void MainController::updateProject_information(QString project_file_full_path)
{
    _project_name = Global_Functions::extractFile_name(project_file_full_path);
    _project_file = Global_Functions::extractFile_full_name(project_file_full_path);
    _project_path = Global_Functions::extractFile_path(project_file_full_path);
    _project_file_full_path = project_file_full_path;
    synchronizeCurrent_path(_project_path);
}

/******************************************************************************
 *             Name: initMain_Window
 *      Function ID: 200
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Initilize functions related to Main Window..
 ******************************************************************************/
void MainController::initMainwindow()
{
    _main_window = new MainWindow();
    connect(this, &MainController::signal_synchronizeCurrent_Path, _main_window, &MainWindow::slot_update_current_path);
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
 * Last modify date: 20/02/2019
 *      Description: Initilize functions related to Settings operations.
 ******************************************************************************/
void MainController::initSettings()
{
    _settings_dialog = new Settings_Dialog(_main_window);
    /** Connect signals and slots related to click Settings menu action button in main window. */
    connect(_main_window, &MainWindow::signal_settings_menu_action_triggered, this, &MainController::slot_settings);
    /** Connect signals and slots related to close Settings dialog. */
    connect(_settings_dialog, &Settings_Dialog::accepted, _main_window, &MainWindow::slot_close_settings_dialog);
    connect(_settings_dialog, &Settings_Dialog::rejected, _main_window, &MainWindow::slot_close_settings_dialog);
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
 *      Function ID: 300
 *      Create date: 16/02/2019
 * Last modify date: 16/02/2019
 *      Description: Show main window.
 ******************************************************************************/
void MainController::showMainwindow()
{
    _main_window->show();
}

/******************************************************************************
 *             Name: slot_create_new_project
 *      Function ID: 700
 *      Create date: 16/02/2019
 * Last modify date: 19/02/2019
 *      Description: Slot for new project created.
 ******************************************************************************/
void MainController::slot_create_new_project(QString project_name, QString project_path)
{
    updateProject_information(project_name, project_path);

    handleNew_Project();

    _main_window->changeDisplay_status(MAINWINDOW_PROJECT_ACTIVATE);

#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: New Project";
    printProject_information();
#endif
}

/******************************************************************************
 *             Name: slot_open_project
 *      Function ID: 701
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Slot for open a project.
 ******************************************************************************/
void MainController::slot_open_project(QString project_file_full_path)
{
    if(project_file_full_path.length() > 0){
        updateProject_information(project_file_full_path);

        _main_window->changeDisplay_status(MAINWINDOW_PROJECT_ACTIVATE);

        handleOpen_Project();
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
 * Last modify date: 18/02/2019
 *      Description: Slot for saving project as another project.
 ******************************************************************************/
void MainController::slot_save_project_as(QString project_file_full_path)
{
    if(project_file_full_path.length() > 0){
        updateProject_information(project_file_full_path);

        handleSave_Project_As();
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
 * Last modify date: 19/02/2019
 *      Description: Slot for current project closed.
 ******************************************************************************/
void MainController::slot_close_project()
{
    clearProject_information();

    handleClose_Project();

    _main_window->resetAll_menu_actions();
    _command_panel->hide();
    _settings_dialog->hide();

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
    qDebug() << "= Project name: " << _project_name;
    qDebug() << "= Project file: " << _project_file;
    qDebug() << "= Project path: " << _project_path;
    qDebug() << "= Project file full path: " <<  _project_file_full_path;
    qDebug() << "= Current path: " <<  _current_path;
    qDebug() << "------------------------------------------------------";
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
#endif
