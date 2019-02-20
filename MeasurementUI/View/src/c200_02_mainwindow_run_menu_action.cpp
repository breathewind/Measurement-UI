/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 18/02/2019
 * Last modify date: 19/02/2019
 *      Description: Main window of MeasurementUI application.
 *                   - Functions related to run menu actions.
 ******************************************************************************/
#include "View/inc/c200_mainwindow.h"
#include "ui_c200_mainwindow.h"

/******************************************************************************
 *             Name: handleStart_triggered
 *      Function ID: 205
 *      Create date: 18/02/2019
 * Last modify date: 19/02/2019
 *      Description: Function for Start menu action triggered.
 ******************************************************************************/
void MainWindow::handleStart_triggered()
{
#ifdef MAINWINDOW_DEBUG
    qDebug() << "+ MainWindow: handleStart_triggered";
#endif


    switch(_project_running){
    case MAINWINDOW_PROJECT_STOP:
        _project_running = MAINWINDOW_PROJECT_RUNNING;
        setRun_menu_action_enable(MAINWINDOW_PROJECT_RUNNING);
        break;
    case MAINWINDOW_PROJECT_RUNNING:
        _project_running = MAINWINDOW_PROJECT_PASUE;
        ui->actionStop->setEnabled(false);
        ui->actionStart->setIcon(QIcon(":/icons/Resource/icons/start2.png"));
        break;
    case MAINWINDOW_PROJECT_PASUE:
        _project_running = MAINWINDOW_PROJECT_RUNNING;
        ui->actionStop->setEnabled(true);
        ui->actionStart->setIcon(QIcon(":/icons/Resource/icons/pause1.png"));
        break;
    default:
#ifdef MAINWINDOW_DEBUG
    qDebug() << "+ MainWindow: handleStart_triggered: Not acceptable _project_running value: " << _project_running;
#endif
        break;
    }
}

/******************************************************************************
 *             Name: handleStop_triggered
 *      Function ID: 206
 *      Create date: 18/02/2019
 * Last modify date: 19/02/2019
 *      Description: Function for Stop menu action triggered.
 ******************************************************************************/
void MainWindow::handleStop_triggered()
{
    _project_running = MAINWINDOW_PROJECT_STOP;
    setRun_menu_action_enable(!MAINWINDOW_PROJECT_RUNNING);

#ifdef MAINWINDOW_DEBUG
    qDebug() << "+ MainWindow: handleStop_triggered";
#endif
}

