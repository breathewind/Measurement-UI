/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 25/02/2019
 * Last modify date: 05/03/2019
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

/******************************************************************************
 *             Name: addLoad_current_chart_view
 *      Function ID: 312
 *      Create date: 27/02/2019
 * Last modify date: 27/02/2019
 *      Description: Add load current chart view to main window.
 ******************************************************************************/
void MainWindow::addLoad_current_chart_view(QChartView *load_current_chart_view)
{
    ui->verticalLayout_load_current->addWidget(load_current_chart_view);
}

/******************************************************************************
 *             Name: removeLoad_current_chart_view
 *      Function ID: 313
 *      Create date: 27/02/2019
 * Last modify date: 27/02/2019
 *      Description: Remove load current chart view from main window.
 ******************************************************************************/
void MainWindow::removeLoad_current_chart_view(QChartView *load_current_chart_view)
{
    ui->verticalLayout_load_current->removeWidget(load_current_chart_view);
}

/******************************************************************************
 *             Name: addBattery_capacity_chart_view
 *      Function ID: 314
 *      Create date: 05/03/2019
 * Last modify date: 05/03/2019
 *      Description: Add battery capacity chart view to main window.
 ******************************************************************************/
void MainWindow::addBattery_capacity_chart_view(QChartView *battery_capacity_chart_view)
{
    ui->verticalLayout_battery_capacity->addWidget(battery_capacity_chart_view);
}

/******************************************************************************
 *             Name: removeBattery_capacity_chart_view
 *      Function ID: 315
 *      Create date: 05/03/2019
 * Last modify date: 05/03/2019
 *      Description: Remove battery capacity chart view from main window.
 ******************************************************************************/
void MainWindow::removeBattery_capacity_chart_view(QChartView *battery_capacity_chart_view)
{
    ui->verticalLayout_battery_capacity->removeWidget(battery_capacity_chart_view);
}

/******************************************************************************
 *             Name: addTarget_capacity_chart_view
 *      Function ID: 316
 *      Create date: 05/03/2019
 * Last modify date: 05/03/2019
 *      Description: Add battery capacity chart view to main window.
 ******************************************************************************/
void MainWindow::addTarget_capacity_chart_view(QChartView *target_capacity_chart_view)
{
    ui->verticalLayout_target_capacity->addWidget(target_capacity_chart_view);
}

/******************************************************************************
 *             Name: removeTarget_capacity_chart_view
 *      Function ID: 317
 *      Create date: 05/03/2019
 * Last modify date: 05/03/2019
 *      Description: Remove battery capacity chart view from main window.
 ******************************************************************************/
void MainWindow::removeTarget_capacity_chart_view(QChartView *target_capacity_chart_view)
{
    ui->verticalLayout_target_capacity->removeWidget(target_capacity_chart_view);
}
