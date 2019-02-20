/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Command Panel dialog of MeasurementUI application.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   6XX - View control functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#include "View/inc/c203_command_panel.h"
#include "ui_c203_command_panel.h"

/******************************************************************************
 *             Name: Command_Panel
 *      Function ID: 000
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Construction function.
 ******************************************************************************/
Command_Panel::Command_Panel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Command_Panel)
{
    ui->setupUi(this);
}

/******************************************************************************
 *             Name: ~Command_Panel
 *      Function ID: 001
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Destruction function.
 ******************************************************************************/
Command_Panel::~Command_Panel()
{
    delete ui;
}
