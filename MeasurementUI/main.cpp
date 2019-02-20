/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 30/01/2019
 * Last modify date: 18/02/2019
 *      Description: Main file of MeasurementUI application.
 ******************************************************************************/
#include <QApplication>

#include "View/inc/c201_new_project_dialog.h"
#include "Controller/inc/c999_maincontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainController main_controller;

    main_controller.showMainwindow();
//    MainWindow w;
//    w.show();

    return a.exec();
}
