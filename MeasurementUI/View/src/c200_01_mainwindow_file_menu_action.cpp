/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Main window of MeasurementUI application.
 *                   - Functions related to file menu actions.
 ******************************************************************************/
#include "View/inc/c200_mainwindow.h"
#include "ui_c200_mainwindow.h"

/******************************************************************************
 *             Name: handleNew_Project_triggered
 *      Function ID: 200
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Function for New Project menu action triggered.
 ******************************************************************************/
void MainWindow::handleNew_Project_triggered()
{
#ifdef MAINWINDOW_DEBUG
    qDebug() << "+ MainWindow: handleNew_Project_triggered";
#endif
}

/******************************************************************************
 *             Name: handleOpen_Project_triggered
 *      Function ID: 201
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Function for Open Project menu action triggered.
 ******************************************************************************/
QString MainWindow::handleOpen_Project_triggered()
{
#ifdef MAINWINDOW_DEBUG
    qDebug() << "+ MainWindow: handleOpen_Project_triggered";
#endif
    QString project_file_full_path = QFileDialog::getOpenFileName(this, tr("Open project"), _current_path, MEASUREMENTUI_DAFAULT_PROJECT_FILE_TYPE);
    return project_file_full_path;
}

/******************************************************************************
 *             Name: handleSave_Project_triggered
 *      Function ID: 202
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Function for Save Project menu action triggered.
 ******************************************************************************/
void MainWindow::handleSave_Project_triggered()
{
#ifdef MAINWINDOW_DEBUG
    qDebug() << "+ MainWindow: handleSave_Project_triggered";
#endif


}

/******************************************************************************
 *             Name: handleSave_Project_As_triggered
 *      Function ID: 203
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Function for Save Project As menu action triggered.
 ******************************************************************************/
QString MainWindow::handleSave_Project_As_triggered()
{
#ifdef MAINWINDOW_DEBUG
    qDebug() << "+ MainWindow: handleSave_Project_As_triggered";
#endif
    QString project_file_full_path = QFileDialog::getSaveFileName(this, tr("Save project as"), _current_path, MEASUREMENTUI_DAFAULT_PROJECT_FILE_TYPE);
    return project_file_full_path;
}

/******************************************************************************
 *             Name: handleClose_Project_triggered
 *      Function ID: 204
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Function for Close Project menu action triggered.
 ******************************************************************************/
void MainWindow::handleClose_Project_triggered()
{
#ifdef MAINWINDOW_DEBUG
    qDebug() << "+ MainWindow: handleClose_Project_triggered";
#endif
}


