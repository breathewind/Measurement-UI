/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 19/02/2019
 * Last modify date: 20/02/2019
 *      Description: Main window of MeasurementUI application.
 *                   - Functions related to function menu actions.
 ******************************************************************************/
#include "View/inc/c200_mainwindow.h"
#include "ui_c200_mainwindow.h"

/******************************************************************************
 *             Name: handleSettings_triggered
 *      Function ID: 207
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Function for Settings menu action triggered.
 ******************************************************************************/
void MainWindow::handleSettings_triggered()
{
#ifdef MAINWINDOW_DEBUG
    qDebug() << "+ MainWindow: " << __FUNCTION__;
#endif
}

/******************************************************************************
 *             Name: handleCommand_Panel_triggered
 *      Function ID: 208
 *      Create date: 19/02/2019
 * Last modify date: 20/02/2019
 *      Description: Function for Command Panel menu action triggered.
 ******************************************************************************/
void MainWindow::handleCommand_Panel_triggered()
{
#ifdef MAINWINDOW_DEBUG
    qDebug() << "+ MainWindow: " << __FUNCTION__;
#endif
}

/******************************************************************************
 *             Name: handleOutput_Panel_triggered
 *      Function ID: 209
 *      Create date: 19/02/2019
 * Last modify date: 20/02/2019
 *      Description: Function for Output Panel menu action triggered.
 ******************************************************************************/
void MainWindow::handleOutput_Panel_triggered()
{
#ifdef MAINWINDOW_DEBUG
    qDebug() << "+ MainWindow: " << __FUNCTION__;
#endif
}
