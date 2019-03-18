/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 14/02/2019
 * Last modify date: 18/03/2019
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

#define MAINCONTTROLLER_SETTINGS_DISPLAY_TEXT       "settings_display"
#define MAINCONTTROLLER_COMMAND_PANEL_DISPLAY_TEXT  "command_panel_display"
#define MAINCONTTROLLER_OUTPUT_PANEL_DISPLAY_TEXT   "output_panel_display"

#define MAINCONTTROLLER_SERIAL_DMM_BAUDRATE_TEXT    "dmm_baudrate"
#define MAINCONTTROLLER_SERIAL_DMM_DATABITS_TEXT    "dmm_databits"
#define MAINCONTTROLLER_SERIAL_DMM_STOPBITS_TEXT    "dmm_stopbits"
#define MAINCONTTROLLER_SERIAL_DMM_PARITY_TEXT      "dmm_parity"
#define MAINCONTTROLLER_SERIAL_DMM_FLOWCONTROL_TEXT "dmm_flowcontrol"

#define MAINCONTTROLLER_SERIAL_BC_BAUDRATE_TEXT     "bc_baudrate"
#define MAINCONTTROLLER_SERIAL_BC_DATABITS_TEXT     "bc_databits"
#define MAINCONTTROLLER_SERIAL_BC_STOPBITS_TEXT     "bc_stopbits"
#define MAINCONTTROLLER_SERIAL_BC_PARITY_TEXT       "bc_parity"
#define MAINCONTTROLLER_SERIAL_BC_FLOWCONTROL_TEXT  "bc_flowcontrol"

#define MAINCONTTROLLER_DEFAULT_CAPTURE_TIMER_TIMEOUT   1000
#define MAINCONTTROLLER_DEFAULT_EXECUTION_TIMER_TIMEOUT 2000

#define MAINCONTTROLLER_DEFAULT_PREDISCHARGE_VALUE 100

#define MAINCONTTROLLER_DEFAULT_START_EXECUTION_OCV 4.10

//#define MAINCONTTROLLER_TARGET_MAH 500
//#define MAINCONTTROLLER_PWM false

#define MAINCONTTROLLER_RESISTANCE 0.53

#define MAINCONTROLLER_VOLT_COMMAND_RUN   0
#define MAINCONTROLLER_VOLT_COMMAND_STOP  1
#define MAINCONTROLLER_VOLT_COMMAND_PAUSE 2

#define MAINCONTROLLER_CURR_COMMAND_RUN   0
#define MAINCONTROLLER_CURR_COMMAND_STOP  1
#define MAINCONTROLLER_CURR_COMMAND_PAUSE 2

#define MAINCONTROLLER_EXE_COMMAND_RUN   0
#define MAINCONTROLLER_EXE_COMMAND_STOP  1
#define MAINCONTROLLER_EXE_COMMAND_PAUSE 2
#define MAINCONTROLLER_EXE_COMMAND_CALIBRATION_MAX 3
#define MAINCONTROLLER_EXE_COMMAND_CALIBRATION_MIN 4
#define MAINCONTROLLER_EXE_COMMAND_PREPARATION 5

#define MAINCONTROLLER_DIR_CREATE_SUCCEED 0
#define MAINCONTROLLER_DIR_CREATE_FAIL    1

#define MAINCONTROLLER_FIRST_HALF true
#define MAINCONTROLLER_SECOND_HALF false

#define MAINCONTROLLER_TOGGLE_FLAG_ON true
#define MAINCONTROLLER_TOGGLE_FLAG_OFF false

#include <QObject>
#include <QDir>
#include <QFile>

#include "h000_global_parameters.h"

#include "Controller/inc/c100_serial_controller.h"
#include "Controller/inc/c102_settings_dialog_controller.h"

#include "Entities/inc/c950_global_functions.h"

#include "View/inc/c200_mainwindow.h"
#include "View/inc/c201_new_project_dialog.h"
#include "View/inc/c202_settings_dialog.h"
#include "View/inc/c203_command_panel.h"
#include "View/inc/c204_output_panel.h"

#include "Model/inc/c001_wave_block.h"

#ifdef MAINCONTROLLER_DEBUG
#include <QElapsedTimer>
#endif

class MainController : public QObject
{
    Q_OBJECT
public:
    /** Function 000: Construction function. */
    MainController();

    /** Function 299: Show main window. */
    void showMainwindow();

private:
    /** Function 002: Clear all project information. */
    void clearProject_information();
    /** Function 003: Synchronize project path. */
    void synchronizeCurrent_path(QString current_path);
    /** Function 004: Update project information according to project name and project path. */
    int updateProject_information(QString project_name, QString project_path, QString output_file);
    /** Function 005: Update project information according to project file full path. */
    void updateProject_information(QString project_file_full_path);
    /** Function 006: Create a new wave block by current measurement and update it to chart. */
    void createWave_block(int current_time);
    /** Function 007: Save wave data to file with specific file path. */
    int saveWave_data(QString file_path, qint64 time1, double value1, qint64 time2, double value2, double power_consumption);
    /** Function 008: Write OCV to file with specific file path. */
    int writeOCV(QString file_path, double value);
    /** Function 009: Retrieve all information about battery and discharging from command panel. */
    void retrieveCommand_panel_data();

    /** Function 200: Initilize functions related to Main Window. */
    void initMainwindow();
    /** Function 201: Initilize functions related to Project operations. */
    void initProject_operaiton();
    /** Function 202: Initilize functions related to Run operations. */
    void initRun_operaiton();
    /** Function 203: Initilize functions related to Function operations. */
    void initFunction_operaiton();
    /** Function 204: Initilize functions related to Serial operations. */
    void initSerial_operaiton();
    /** Function 205: Initilize functions related to Chart operations. */
    void initChart_operaiton();


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
    bool handleNew_Project();
    /** Function 232: Function for handle operations related to Open Project. */
    bool handleOpen_Project();
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

    /** Function 300: Update all settings opertions. */
    void updateSettings();
    /** Function 301: Capture one measurement. */
    void captureOne_measurement();
    /** Function 302: Start exeuction of meausuremnt.. */
    void startExecution(uint8_t resistance);
    /** Function 303: Start calibration of max current. */
    void startCalibration_max();
    /** Function 304: Start calibration of min current. */
    void startCalibration_min();
    /** Function 305: Start meausuremnt from capturing OCV. */
    void startMeasurement();

    /** Function 600: Print data read from project file. */
    void printData_read_from_project_file(QString domain, QString content);

#ifdef MAINCONTROLLER_DEBUG
    /** Function 900: Print project information. -Debug function */
    void printProject_information();
    /** Function 903: Print serial information. -Debug function */
    void debug_printSerial_information();
#endif

    MainWindow* _main_window;

    New_Project_Dialog* _new_project_dialog;
    Settings_Dialog* _settings_dialog;
    Command_Panel* _command_panel;
    Output_Panel* _output_panel;

    Settings_Dialog_Controller* _setting_dialog_controller;

    QString _project_name;
    QString _project_file;
    QString _project_path;
    QString _project_file_full_path;
    QString _current_path;

    QString _project_output_path;
    QString _output_file_name;
    QString _raw_output_file_name;

    QString _dmm_port;
    QString _dmm_baudrate;
    QString _dmm_databits;
    QString _dmm_stopbits;
    QString _dmm_parity;
    QString _dmm_flowcontrol;

    QString _bc_port;
    QString _bc_baudrate;
    QString _bc_databits;
    QString _bc_stopbits;
    QString _bc_parity;
    QString _bc_flowcontrol;

    Serial_Controller *_DMM_controller;
    Serial_Controller *_DMM_controller_current;
    Serial_Controller *_BC_controller;

    int _sampling_command;
    QTimer *_capture_timer;
    int _capture_timer_timeout;
    QString _data_read_buffer;

    QTimer *_voltage_capture_timer;
    int _voltage_timer_timeout;

//    int _sampling_command_current;
//    QTimer *_capture_timer_current;
//    int _capture_timer_timeout_current;
    double _data_read_buffer_current;

    double _total_mAh;

    int _execution_period;
    QTimer *_execution_timer;
    QTimer *_execution_capture_timer;
    QTimer *_execution_calibrate_timer;
    int _execution_command;
    bool _half_counter;
    bool _toggle_flag;

    QTimer *_OCV_timer;

    QElapsedTimer *_execution_elapsed_timer;

    QElapsedTimer _main_elapsed_timer;
    qint64 _thistime_recorder;
    qint64 _lastime_recorder;

    qint64 _first_x;
    double _first_y;

    double _max_mAh;
    double _realtime_battery_voltage;
    double _start_exe_OCV;

    Chart_Controller* _battery_voltage_chart_view_controller;
    Chart_Controller* _load_current_chart_view_controller;
    Pie_Controller* _battery_capacity_pie_controller;
    Pie_Controller* _target_capacity_pie_controller;

    double _sense_resistance;
    uint8_t _control_resistance_max;
    uint8_t _control_resistance_min;
    double _target_current_max;
    double _target_current_min;
    int _calibration_factor;
    double _min_step_current_max;
    double _min_step_current_min;
    double _last_step_current_max;
    double _last_step_current_min;
//    double _last_last_step_current;
    bool _resistance_change_flag;
    char _different_factor;

    qint64 _last_elapsed_time;

    int _discharge_type;
    double _SW_min_current;
    double _SW_max_current;
    int _SW_period;
    double _CC_current;

    int _termination_type;
    double _TCC_coulomb;
    double _TVOC_voltage;

    double _battery_capacity;

    bool _start_record;

#ifdef MAINCONTROLLER_DEBUG
    QElapsedTimer _elapsed_timer;

    uint8_t test_counter;
#endif

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

    /** Function 750: Slot for updating data from settings dialog to main controller. */
    void slot_update_data_from_settings(QList<QStringList> data_set);

    /** Function 751: Slot for retrieving data from DMM when one data to read is ready. */
    void slot_retrieveDMM_data(QString received_data);
    /** Function 752: Slot for reading data from data read buffer when capture timer timeout is reached. */
    void slot_read_serial_buffer();
    /** Function 753: Slot for retrieving data from DMM during current measurement when one data to read is ready. */
    void slot_retrieveDMM_data_for_current(QString received_data);
    /** Function 754: Slot for reading data from data read buffer during current measurement when capture timer timeout is reached. */
//    void slot_read_serial_buffer_for_current();
    /** Function 755: Slot for changing load current when execution timer timeout is reached. */
    void slot_change_load_current();
    /** Function 756: Slot for starting second half load current meausurement when execution capture timer timeout is reached. */
    void slot_start_second_half_meausurement();
    /** Function 757: Slot for voltage current received from battery monitor. */
    void slot_battery_voltage_received(QString voltage_value);

    /** Function 758: Slot for sending read voltage comand to MCU when voltage capture timer timeout is reached. */
    void slot_read_battery_voltage();

    /** Function 759: Slot for writing OCV to file when OCV capture timer timeout is reached. */
    void slot_save_OCV();


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
    /** Signal 003: Signal emitted when a warning event occurs. */
    void signal_warning_occurs(QString text);
};

#endif // C999_MAINCONTROLLER_H
