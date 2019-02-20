/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 16/02/2019
 * Last modify date: 18/02/2019
 *      Description: Global parameters.
 ******************************************************************************/
#ifndef H000_GLOBAL_PARAMETERS_H
#define H000_GLOBAL_PARAMETERS_H

#define APP_NAME "MeasurementUI"

#define MEASUREMENTUI_DIR_SYMBOL "/"
#define MEASUREMENTUI_DAFAULT_PROJECT_NAME   "Measurement"
#define MEASUREMENTUI_DAFAULT_PROJECT_SUFFIX ".proj"
#define MEASUREMENTUI_DAFAULT_PROJECT_FILE_TYPE tr("Project File (*.proj)")
//#define MEASUREMENTUI_DAFAULT_PROJECT_FILE_TYPE tr("Project File (*.proj);;All Files (*.*)")

#define MEASUREMENTUI_DEBUG

#ifdef MEASUREMENTUI_DEBUG
#include <QDebug>
#define MAINCONTROLLER_DEBUG
#define MAINWINDOW_DEBUG
#define NEWPROJECT_DEBUG
#define SETTINGS_DIALOG_DEBUG
#endif


#endif // H000_GLOBAL_PARAMETERS_H
