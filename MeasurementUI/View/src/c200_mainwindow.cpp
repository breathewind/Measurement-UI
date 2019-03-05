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
#include "View/inc/c200_mainwindow.h"
#include "ui_c200_mainwindow.h"

/******************************************************************************
 *             Name: MainWindow
 *      Function ID: 000
 *      Create date: 30/01/2019
 * Last modify date: 19/02/2019
 *      Description: Construction function.
 ******************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("MeasurementUI");

    initializeRun_time_group();
    initializeFile_group();
    initializeSetting_group();
    initializeCreate_file_group();

    resetAll_menu_actions();
}

/******************************************************************************
 *             Name: ~MainWindow
 *      Function ID: 001
 *      Create date: 30/01/2019
 * Last modify date: 30/01/2019
 *      Description: Destruction function.
 ******************************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}

/******************************************************************************
 *             Name: initializeRun_Time_Group
 *      Function ID: 002
 *      Create date: 18/02/2019
 * Last modify date: 19/02/2019
 *      Description: Run time action group initialization.
 ******************************************************************************/
void MainWindow::initializeRun_time_group()
{
    _run_time_group = new QActionGroup(this);
    _run_time_group->addAction(ui->actionStart);
    _run_time_group->addAction(ui->actionStop);

    ui->actionStop->setEnabled(false);
}

/******************************************************************************
 *             Name: initializeFile_group
 *      Function ID: 003
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: File action group initialization.
 ******************************************************************************/
void MainWindow::initializeFile_group()
{
    _file_group = new QActionGroup(this);
    _file_group->addAction(ui->actionSave_project);
    _file_group->addAction(ui->actionSave_project_as);
    _file_group->addAction(ui->actionClose_project);
}

/******************************************************************************
 *             Name: initializeSetting_group
 *      Function ID: 004
 *      Create date: 18/02/2019
 * Last modify date: 19/02/2019
 *      Description: Setting action group initialization.
 ******************************************************************************/
void MainWindow::initializeSetting_group()
{
    _setting_group = new QActionGroup(this);
    _setting_group->addAction(ui->actionSettings);
    _setting_group->addAction(ui->actionCommand_Panel);
    _setting_group->setExclusive(false);
}

/******************************************************************************
 *             Name: initializeFull_file_group
 *      Function ID: 005
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Setting action group initialization.
 ******************************************************************************/
void MainWindow::initializeCreate_file_group()
{
    _create_file_group = new QActionGroup(this);
    _create_file_group->addAction(ui->actionNew_Project);
    _create_file_group->addAction(ui->actionOpen_Project);
}

/******************************************************************************
 *             Name: setRun_menu_action_enable
 *      Function ID: 010
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Set display status for the Run operation menu actions
 *                   depending project running information.
 *  @param flag: MAINWINDOW_PROJECT_RUNNING(0) - Measurement is running;
 *               !MAINWINDOW_PROJECT_RUNNING   - Measurement is not running.
 ******************************************************************************/
void MainWindow::setRun_menu_action_enable(bool flag)
{
    /** Enable Stop menu action when measurement is currently running. */
    ui->actionStop->setEnabled(!flag);
    /** Enable Quit menu action when measurement is not currently running. */
    ui->actionQuit->setEnabled(flag);
    /** Enable Create file action group when measurement is not currently running. */
    _create_file_group->setEnabled(flag);
    /** Enable File action group when measurement is not currently running. */
    _file_group->setEnabled(flag);
    if(flag){
        /** Set Start action icon to start.png when measurement is not current running. */
        ui->actionStart->setIcon(QIcon(":/icons/Resource/icons/start.png"));
    } else {
        /** Set Start action icon to pause1.png when measurement is current running. */
        ui->actionStart->setIcon(QIcon(":/icons/Resource/icons/pause1.png"));
    }
}

/******************************************************************************
 *             Name: closeEvent
 *      Function ID: 090
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Overwrite close event.
 ******************************************************************************/
void MainWindow::closeEvent (QCloseEvent *event)
{
    if(_project_running!= MAINWINDOW_PROJECT_STOP){
        QMessageBox::warning(this, tr("Warning"), tr("One project is currently runing, please stop it and try to quit again.\n"));
        event->ignore();
    }else {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, APP_NAME, tr("Are you sure to quit?\n"),
                                                                    QMessageBox::Cancel | QMessageBox::Yes,
                                                                    QMessageBox::Yes);
            if (resBtn != QMessageBox::Yes) {
                event->ignore();
            } else {
                event->accept();
                QApplication::quit();
            }
    }
}

/******************************************************************************
 *             Name: changeDisplay_status
 *      Function ID: 300
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Change display status depending on if there is any project
 *                   activated.
 ******************************************************************************/
void MainWindow::changeDisplay_status(bool display_flag)
{
    _project_activated = display_flag;

    _run_time_group->setEnabled(display_flag);
    _file_group->setEnabled(display_flag);
    _setting_group->setEnabled(display_flag);
}

/******************************************************************************
 *             Name: resetAll_menu_actions
 *      Function ID: 301
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Reset display status for all the menu actions.
 ******************************************************************************/
void MainWindow::resetAll_menu_actions()
{
    setSettings_action_checked(false);
    setCommand_panel_action_checked(false);

    setRun_menu_action_enable(!MAINWINDOW_PROJECT_RUNNING);
    changeDisplay_status(MAINWINDOW_PROJECT_DEACTIVATE);

    _project_running = MAINWINDOW_PROJECT_STOP;
}

/******************************************************************************
 *             Name: on_actionNew_Project_triggered
 *      Function ID: 700
 *      Create date: 16/02/2019
 * Last modify date: 16/02/2019
 *      Description: Slot for New Project menu action triggered.
 ******************************************************************************/
void MainWindow::on_actionNew_Project_triggered()
{
//    qDebug() << "on_actionNew_Project_triggered";
    handleNew_Project_triggered();
    emit signal_new_project_menu_action_triggered();
}

/******************************************************************************
 *             Name: on_actionOpen_Project_triggered
 *      Function ID: 701
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Slot for Open Project menu action triggered.
 ******************************************************************************/
void MainWindow::on_actionOpen_Project_triggered()
{
    emit signal_open_project_menu_action_triggered(handleOpen_Project_triggered());
}

/******************************************************************************
 *             Name: on_actionSave_project_triggered
 *      Function ID: 702
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Slot for Save Project menu action triggered.
 ******************************************************************************/
void MainWindow::on_actionSave_project_triggered()
{
    handleSave_Project_triggered();
    emit signal_save_project_menu_action_triggered();
}

/******************************************************************************
 *             Name: on_actionSave_project_as_triggered
 *      Function ID: 703
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Slot for Save Project As menu action triggered.
 ******************************************************************************/
void MainWindow::on_actionSave_project_as_triggered()
{
    emit signal_save_project_as_menu_action_triggered(handleSave_Project_As_triggered());
}

/******************************************************************************
 *             Name: on_actionClose_project_triggered
 *      Function ID: 704
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Slot for Close Project menu action triggered.
 ******************************************************************************/
void MainWindow::on_actionClose_project_triggered()
{
    handleClose_Project_triggered();
    emit signal_close_project_menu_action_triggered();
}

/******************************************************************************
 *             Name: on_actionStart_triggered
 *      Function ID: 705
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Slot for Start menu action triggered.
 ******************************************************************************/
void MainWindow::on_actionStart_triggered()
{
    handleStart_triggered();
    emit signal_start_menu_action_triggered();
}

/******************************************************************************
 *             Name: on_actionStop_triggered
 *      Function ID: 706
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Slot for Stop menu action triggered.
 ******************************************************************************/
void MainWindow::on_actionStop_triggered()
{
    handleStop_triggered();
    emit signal_stop_menu_action_triggered();
}

/******************************************************************************
 *             Name: on_actionSettings_triggered
 *      Function ID: 707
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Slot for Settings menu action triggered.
 ******************************************************************************/
void MainWindow::on_actionSettings_triggered()
{
    handleSettings_triggered();
    emit signal_settings_menu_action_triggered();
}

/******************************************************************************
 *             Name: on_actionCommand_Panel_triggered
 *      Function ID: 708
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Slot for Command Panel menu action triggered.
 ******************************************************************************/
void MainWindow::on_actionCommand_Panel_triggered()
{
    handleCommand_Panel_triggered();
    emit signal_command_panel_menu_action_triggered();
}

/******************************************************************************
 *             Name: on_actionOutput_Panel_triggered
 *      Function ID: 709
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Slot for Output Panel menu action triggered.
 ******************************************************************************/
void MainWindow::on_actionOutput_Panel_triggered()
{
    handleOutput_Panel_triggered();
    emit signal_output_panel_menu_action_triggered();
}

/******************************************************************************
 *             Name: on_actionInformation_triggered
 *      Function ID: 710
 *      Create date: 31/01/2019
 * Last modify date: 31/01/2019
 *      Description: Slot for Information menu action triggered.
 ******************************************************************************/
void MainWindow::on_actionInformation_triggered()
{
    QMessageBox::information(this, "Information", "Measurement UI\nCreator: Wenlong Wang\nVersion: 0.0.0");
}

/******************************************************************************
 *             Name: on_actionQuit_triggered
 *      Function ID: 711
 *      Create date: 31/01/2019
 * Last modify date: 19/02/2019
 *      Description: Slot for Quit menu action triggered.
 ******************************************************************************/
void MainWindow::on_actionQuit_triggered()
{
    emit signal_quit_menu_action_triggered();
}

/******************************************************************************
 *             Name: slot_update_current_path
 *      Function ID: 750
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Slot for updating current path.
 ******************************************************************************/
void MainWindow::slot_update_current_path(QString current_path)
{
    _current_path = current_path;

#ifdef MAINWINDOW_DEBUG
    qDebug() << "+ MainWindow: current path is updated to: " << _current_path ;
#endif
}

/******************************************************************************
 *             Name: slot_confirm_quit_application
 *      Function ID: 751
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Slot for quit application confirmed.
 ******************************************************************************/
void MainWindow::slot_confirm_quit_application()
{
    close();
}

/******************************************************************************
 *             Name: slot_close_settings_dialog
 *      Function ID: 752
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Slot for closing Settings dialog.
 ******************************************************************************/
void MainWindow::slot_close_settings_dialog()
{
    ui->actionSettings->setChecked(false);
}

/******************************************************************************
 *             Name: slot_close_command_panel
 *      Function ID: 753
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Slot for closing Command panel.
 ******************************************************************************/
void MainWindow::slot_close_command_panel()
{
    ui->actionCommand_Panel->setChecked(false);
}

/******************************************************************************
 *             Name: slot_close_output_panel
 *      Function ID: 754
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Slot for closing Output panel.
 ******************************************************************************/
void MainWindow::slot_close_output_panel()
{
    ui->actionOutput_Panel->setChecked(false);
}

/******************************************************************************
 *             Name: slot_display_warning_message_box
 *      Function ID: 755
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Slot for displaying warning message box.
 ******************************************************************************/
void MainWindow::slot_display_warning_message_box(QString text)
{
    QMessageBox::warning(this, "Warning", text);
}

/******************************************************************************
 *             Name: setSettings_action_seleted
 *      Function ID: 800
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Set Settings menu action seleted.
 ******************************************************************************/
void MainWindow::setSettings_action_checked(bool flag)
{
    ui->actionSettings->setChecked(flag);
}

/******************************************************************************
 *             Name: getSettings_action_checked
 *      Function ID: 801
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Get if Settings menu action is seleted.
 ******************************************************************************/
bool MainWindow::getSettings_action_checked()
{
    return ui->actionSettings->isChecked();
}

/******************************************************************************
 *             Name: setCommand_panel_action_checked
 *      Function ID: 802
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Set Command panel menu action seleted.
 ******************************************************************************/
void MainWindow::setCommand_panel_action_checked(bool flag)
{
    ui->actionCommand_Panel->setChecked(flag);
}

/******************************************************************************
 *             Name: getCommand_panel_action_checked
 *      Function ID: 803
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Get if Command panel menu action is seleted.
 ******************************************************************************/
bool MainWindow::getCommand_panel_action_checked()
{
    return ui->actionCommand_Panel->isChecked();
}

/******************************************************************************
 *             Name: setOutput_panel_action_checked
 *      Function ID: 804
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Set Output panel menu action seleted.
 ******************************************************************************/
void MainWindow::setOutput_panel_action_checked(bool flag)
{
    ui->actionOutput_Panel->setChecked(flag);
}

/******************************************************************************
 *             Name: getOutput_panel_action_checked
 *      Function ID: 805
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Get if Output panel menu action is seleted.
 ******************************************************************************/
bool MainWindow::getOutput_panel_action_checked()
{
    return ui->actionOutput_Panel->isChecked();
}


