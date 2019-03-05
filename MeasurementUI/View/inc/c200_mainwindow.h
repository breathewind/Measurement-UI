/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 30/01/2019
 * Last modify date: 05/03/2019
 *      Description: Main window of MeasurementUI application.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   6XX - View control functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#ifndef C200_MAINWINDOW_H
#define C200_MAINWINDOW_H

#define MAINWINDOW_PROJECT_ACTIVATE   true
#define MAINWINDOW_PROJECT_DEACTIVATE false

#define MAINWINDOW_PROJECT_RUNNING 0
#define MAINWINDOW_PROJECT_PASUE   1
#define MAINWINDOW_PROJECT_STOP    2

#include <QMainWindow>
#include <QMessageBox>
#include <QActionGroup>
#include <QFileDialog>
#include <QIcon>
#include <QCloseEvent>

#include "h000_global_parameters.h"
#include "Controller/inc/c110_chart_controller.h"
#include "Controller/inc/c111_pie_controller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /** Function 000: Construction function. */
    explicit MainWindow(QWidget *parent = nullptr);
    /** Function 001: Destruction function. */
    ~MainWindow();


    /** Function 300: Change display status depending on if there is any project activated. */
    void changeDisplay_status(bool display_flag);
    /** Function 301: Reset display status for all the menu actions. */
    void resetAll_menu_actions();

    /** Function 310: Add battery chart view to main window. */
    void addBettery_voltage_chart_view(QChartView *battery_volage_chart_view);
    /** Function 311: Remove battery chart view from main window. */
    void removeBettery_voltage_chart_view(QChartView *battery_volage_chart_view);
    /** Function 312: Add load current chart view to main window. */
    void addLoad_current_chart_view(QChartView *load_current_chart_view);
    /** Function 313: Remove load current chart view from main window. */
    void removeLoad_current_chart_view(QChartView *load_current_chart_view);
    /** Function 314: Add battery capacity chart view to main window. */
    void addBattery_capacity_chart_view(QChartView *battery_capacity_chart_view);
    /** Function 315: Remove battery capacity chart view from main window. */
    void removeBattery_capacity_chart_view(QChartView *battery_capacity_chart_view);



    /** Function 800: Set Settings menu action seleted. */
    void setSettings_action_checked(bool flag);
    /** Function 801: Get if Settings menu action seleted. */
    bool getSettings_action_checked();
    /** Function 802: Set Command panel menu action seleted. */
    void setCommand_panel_action_checked(bool flag);
    /** Function 803: Get if Command panel menu action seleted. */
    bool getCommand_panel_action_checked();
    /** Function 804: Set Output panel menu action seleted. */
    void setOutput_panel_action_checked(bool flag);
    /** Function 805: Get if Output panel menu action seleted. */
    bool getOutput_panel_action_checked();

public slots:
    /** Function 750: Slot for updating current path. */
    void slot_update_current_path(QString current_path);
    /** Function 751: Slot for quit application confirmed. */
    void slot_confirm_quit_application();

    /** Function 752: Slot for closing Settings dialog. */
    void slot_close_settings_dialog();
    /** Function 753: Slot for closing Command panel. */
    void slot_close_command_panel();
    /** Function 754: Slot for closing Output panel. */
    void slot_close_output_panel();

    /** Function 755: Slot for displaying warning message box. */
    void slot_display_warning_message_box(QString text);
private:
    /** Function 002: Run time action group initialization. */
    void initializeRun_time_group();
    /** Function 003: File action group initialization. */
    void initializeFile_group();
    /** Function 004: Setting action group initialization. */
    void initializeSetting_group();
    /** Function 005: Full file action group initialization. */
    void initializeCreate_file_group();

    /** Function 010: Set display status for the Run operation menu actions depending project running information. */
    void setRun_menu_action_enable(bool flag);

    /** Function 090: Overwrite close event. */
    void closeEvent (QCloseEvent *event);

    /** Function 200: Function for New Project menu action triggered. */
    void handleNew_Project_triggered();
    /** Function 201: Function for Open Project menu action triggered. */
    QString handleOpen_Project_triggered();
    /** Function 202: Function for Save Project menu action triggered. */
    void handleSave_Project_triggered();
    /** Function 203: Function for Save Project As menu action triggered. */
    QString handleSave_Project_As_triggered();
    /** Function 204: Function for Close Project menu action triggered. */
    void handleClose_Project_triggered();

    /** Function 205: Function for Start menu action triggered. */
    void handleStart_triggered();
    /** Function 206: Function for Stop menu action triggered. */
    void handleStop_triggered();

    /** Function 207: Function for Settings menu action triggered. */
    void handleSettings_triggered();
    /** Function 208: Function for Command Panel menu action triggered. */
    void handleCommand_Panel_triggered();
    /** Function 209: Function for Output Panel menu action triggered. */
    void handleOutput_Panel_triggered();

    Ui::MainWindow *ui;

    QActionGroup *_run_time_group;
    QActionGroup *_file_group;
    QActionGroup *_create_file_group;
    QActionGroup *_setting_group;

    bool _project_activated;
    char _project_running;

    QString _current_path;

private slots:
    /** Function 700: Slot for New Project menu action triggered. */
    void on_actionNew_Project_triggered();
    /** Function 701: Slot for Open Project menu action triggered. */
    void on_actionOpen_Project_triggered();
    /** Function 702: Slot for Save Project menu action triggered. */
    void on_actionSave_project_triggered();
    /** Function 703: Slot for Save Project As menu action triggered. */
    void on_actionSave_project_as_triggered();
    /** Function 704: Slot for Close Project menu action triggered. */
    void on_actionClose_project_triggered();

    /** Function 705: Slot for Start menu action triggered. */
    void on_actionStart_triggered();
    /** Function 706: Slot for Stop menu action triggered. */
    void on_actionStop_triggered();

    /** Function 707: Slot for Settings menu action triggered. */
    void on_actionSettings_triggered();
    /** Function 708: Slot for Command Panel menu action triggered. */
    void on_actionCommand_Panel_triggered();
    /** Function 709: Slot for Output Panel menu action triggered. */
    void on_actionOutput_Panel_triggered();

    /** Function 710: Slot for Information menu action triggered. */
    void on_actionInformation_triggered();
    /** Function 711: Slot for Quit menu action triggered. */
    void on_actionQuit_triggered();

signals:
    /** Signal 001: Signal emitted when New Project menu action triggered. */
    void signal_new_project_menu_action_triggered();
    /** Signal 002: Signal emitted when Open Project menu action triggered. */
    void signal_open_project_menu_action_triggered(QString project_file_full_path);
    /** Signal 003: Signal emitted when Save Project menu action triggered. */
    void signal_save_project_menu_action_triggered();
    /** Signal 004: Signal emitted when Save Project As menu action triggered. */
    void signal_save_project_as_menu_action_triggered(QString project_file_full_path);
    /** Signal 005: Signal emitted when Close Project menu action triggered. */
    void signal_close_project_menu_action_triggered();

    /** Signal 006: Signal emitted when Start menu action triggered. */
    void signal_start_menu_action_triggered();
    /** Signal 007: Signal emitted when Stop menu action triggered. */
    void signal_stop_menu_action_triggered();

    /** Signal 008: Signal emitted when Settings menu action triggered. */
    void signal_settings_menu_action_triggered();
    /** Signal 009: Signal emitted when Command panel menu action triggered. */
    void signal_command_panel_menu_action_triggered();
    /** Signal 010: Signal emitted when Output panel menu action triggered. */
    void signal_output_panel_menu_action_triggered();

    /** Signal 012: Signal emitted when Quit menu action triggered. */
    void signal_quit_menu_action_triggered();
};

#endif // C200_MAINWINDOW_H
