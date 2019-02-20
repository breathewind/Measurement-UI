/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 18/02/2019
 * Last modify date: 19/02/2019
 *      Description: Main window controller.
 *                   - Functions related to file menu actions.
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: handleNew_Project
 *      Function ID: 231
 *      Create date: 18/02/2019
 * Last modify date: 19/02/2019
 *      Description: Function for handle operations related to New Project.
 ******************************************************************************/
void MainController::handleNew_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleNew_Project";
#endif
    _main_window->setWindowTitle(QString("%1 - %2").arg(APP_NAME).arg(_project_name));

}

/******************************************************************************
 *             Name: handleOpen_Project
 *      Function ID: 232
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Function for handle operations related to Open Project.
 ******************************************************************************/
void MainController::handleOpen_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleOpen_Project";
#endif
    _main_window->setWindowTitle(QString("%1 - %2").arg(APP_NAME).arg(_project_name));
}

/******************************************************************************
 *             Name: handleSave_Project
 *      Function ID: 233
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Function for handle operations related to Save Project.
 ******************************************************************************/
void MainController::handleSave_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleSave_Project";
#endif
}

/******************************************************************************
 *             Name: handleSave_Project_As
 *      Function ID: 234
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Function for handle operations related to Save Project As.
 ******************************************************************************/
void MainController::handleSave_Project_As()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleSave_Project_As";
#endif
}

/******************************************************************************
 *             Name: handle_CloseProject
 *      Function ID: 235
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Function for handle operations related to Close Project.
 ******************************************************************************/
void MainController::handleClose_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handle_CloseProject";
#endif
    _main_window->setWindowTitle(QString(APP_NAME));
}
