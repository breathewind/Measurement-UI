/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Output Panel dialog of MeasurementUI application.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   6XX - View control functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#include "View/inc/c204_output_panel.h"
#include "ui_c204_output_panel.h"

/******************************************************************************
 *             Name: Output_Panel
 *      Function ID: 000
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Construction function.
 ******************************************************************************/
Output_Panel::Output_Panel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Output_Panel)
{
    ui->setupUi(this);
}

/******************************************************************************
 *             Name: ~Output_Panel
 *      Function ID: 001
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Destruction function.
 ******************************************************************************/
Output_Panel::~Output_Panel()
{
    delete ui;
}
