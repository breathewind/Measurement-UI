/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 25/02/2019
 * Last modify date: 26/02/2019
 *      Description: Main window of MeasurementUI application.
 *                   - Functions related to charts.
 ******************************************************************************/
#include "View/inc/c200_mainwindow.h"
#include "ui_c200_mainwindow.h"

/******************************************************************************
 *             Name: addBettery_voltage_chart_view
 *      Function ID: 310
 *      Create date: 25/02/2019
 * Last modify date: 25/02/2019
 *      Description: Add battery chart view to main window.
 ******************************************************************************/
void MainWindow::addBettery_voltage_chart_view(QChartView *battery_volage_chart_view){

    ui->verticalLayout_battery_voltage->addWidget(battery_volage_chart_view);
}

/******************************************************************************
 *             Name: removeBettery_voltage_chart_view
 *      Function ID: 311
 *      Create date: 26/02/2019
 * Last modify date: 26/02/2019
 *      Description: Remove battery chart view from main window.
 ******************************************************************************/
void MainWindow::removeBettery_voltage_chart_view(QChartView *battery_volage_chart_view){

    ui->verticalLayout_battery_voltage->removeWidget(battery_volage_chart_view);
}
