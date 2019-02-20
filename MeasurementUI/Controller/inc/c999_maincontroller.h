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
#ifndef C999_MAINCONTROLLER_H
#define C999_MAINCONTROLLER_H

#include <QObject>

#include "h000_global_parameters.h"
#include "Entities/inc/c950_global_functions.h"
#include "View/inc/c200_mainwindow.h"
#include "View/inc/c201_new_project_dialog.h"
#include "View/inc/c202_settings_dialog.h"
#include "View/inc/c203_command_panel.h"
#include "View/inc/c204_output_panel.h"

class MainController : public QObject
{
    Q_OBJECT
public:
    /** Function 000: Construction function. */
    MainController();

    /** Function 300: Show main window. */
    void showMainwindow();

private:
    /** Function 002: Clear all project information. */
    void clearProject_information();
    /** Function 003: Synchronize project path. */
    void synchronizeCurrent_path(QString current_path);
    /** Function 004: Update project information according to project name and project path. */
    void updateProject_information(QString project_name, QString project_path);
    /** Function 005: Update project information according to project file full path. */
    void updateProject_information(QString project_file_full_path);

    /** Function 200: Initilize functions related to Main Window. */
    void initMainwindow();
    /** Function 201: Initilize functions related to Project operations. */
    void initProject_operaiton();
    /** Function 202: Initilize functions related to Run operations. */
    void initRun_operaiton();
    /** Function 202: Initilize functions related to Function operations. */
    void initFunction_operaiton();


    /** Function 211: Initilize functions related to New Project operations. */
    void initNew_Project();
    /** Function 212: Initilize functions related to Open Project operations. */
    void initOpen_Project();
    /** Function 213: Initilize functions related to Save Project operations. */
    void initSave_Project();
    /** Function 214: Initilize functions related to Save Project As operations. */
    void initSave_Project_As();
    /** Function 215: Initilize functions related to Close Project operations. */
    void initClose_Project();

    /** Function 216: Initilize functions related to Start operations. */
    void initStart();
    /** Function 217: Initilize functions related to Stop operations. */
    void initStop();

    /** Function 218: Initilize functions related to Settings operations. */
    void initSettings();
    /** Function 219: Initilize functions related to Command Panel operations. */
    void initCommand_Panel();
    /** Function 220: Initilize functions related to Output Panel operations. */
    void initOutput_Panel();

    /** Function 222: Initilize functions related to Quit operations. */
    void initQuit();

    /** Function 231: Function for handle operations related to New Project. */
    void handleNew_Project();
    /** Function 232: Function for handle operations related to Open Project. */
    void handleOpen_Project();
    /** Function 233: Function for handle operations related to Save Project. */
    void handleSave_Project();
    /** Function 234: Function for handle operations related to Save Project as. */
    void handleSave_Project_As();
    /** Function 235: Function for handle operations related to Close Project. */
    void handleClose_Project();

    /** Function 236: Function for handle operations related to Start. */
    void handleStart();
    /** Function 237: Function for handle operations related to Stop. */
    void handleStop();

    /** Function 238: Function for handle operations related to Settings. */
    void handleSettings();
    /** Function 239: Function for handle operations related to Command Panel. */
    void handleCommand_Panel();
    /** Function 240: Function for handle operations related to Output Panel. */
    void handleOutput_Panel();

#ifdef MAINCONTROLLER_DEBUG
    /** Function 900: Print project information. -Debug function*/
    void printProject_information();
#endif

    MainWindow* _main_window;

    New_Project_Dialog* _new_project_dialog;
    Settings_Dialog* _settings_dialog;
    Command_Panel* _command_panel;
    Output_Panel* _output_panel;

    QString _project_name;
    QString _project_file;
    QString _project_path;
    QString _project_file_full_path;
    QString _current_path;

private slots:
    /** Function 700: Slot for new project created. */
    void slot_create_new_project(QString project_name, QString project_path);
    /** Function 701: Slot for open a project. */
    void slot_open_project(QString project_file_full_path);
    /** Function 702: Slot for saving current project. */
    void slot_save_project();
    /** Function 703: Slot for saving project as another project. */
    void slot_save_project_as(QString project_file_full_path);
    /** Function 704: Slot for current project closed. */
    void slot_close_project();

    /** Function 705: Slot for starting new measrement. */
    void slot_Start();
    /** Function 706: Slot for stoping current measurement. */
    void slot_Stop();

    /** Function 707: Slot for displaying Settings panel. */
    void slot_settings();
    /** Function 708: Slot for displaying Command panel. */
    void slot_command_panel();
    /** Function 709: Slot for displaying Output panel. */
    void slot_output_panel();

    /** Function 711: Slot for quiting application. */
    void slot_Quit();


#ifdef MAINCONTROLLER_DEBUG
    /** Function 901: Print debug information. -Debug function*/
    void debug_slot_printDebug_info1();
    /** Function 902: Print debug information. -Debug function*/
    void debug_slot_printDebug_info2();
#endif

signals:
    /** Signal 001: Signal for synchronizing project path. */
    void signal_synchronizeCurrent_Path(QString project_path);
    /** Signal 002: Signal for comfirming quit appliaciton. */
    void signal_confirm_quit_application();
};

#endif // C999_MAINCONTROLLER_H
