/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 19/02/2019
 * Last modify date: 07/03/2019
 *      Description: Command Panel dialog of MeasurementUI application.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   6XX - View control functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#ifndef C203_COMMAND_PANEL_H
#define C203_COMMAND_PANEL_H

#define COMMNAD_PANEL_DISCHARGE_TYPE_SQUARE_WAVE      0
#define COMMNAD_PANEL_DISCHARGE_TYPE_CONSTANT_CURRENT 1

#define COMMAND_PANEL_DISCHARGE_TYPE_INDEX        0

#define COMMAND_PANEL_SW_MIN_CURRENT_INDEX 1
#define COMMAND_PANEL_SW_MAX_CURRENT_INDEX 2
#define COMMAND_PANEL_SW_PERIOD_INDEX      3

#define COMMAND_PANEL_CC_CURRENT_INDEX 1

#define COMMAND_PANEL_TERMINATION_TYPE_COULOMB_COUNTING 0
#define COMMAND_PANEL_TERMINATION_TYPE_OCV              1

#define COMMAND_PANEL_TERMINATION_TYPE_INDEX    0

#define COMMAND_PANEL_TCC_COULOMB_INDEX 1

#define COMMAND_PANEL_TVOC_VOLTAGE_INDEX 1

#include <QDialog>

#include "h000_global_parameters.h"

namespace Ui {
class Command_Panel;
}

class Command_Panel : public QDialog
{
    Q_OBJECT

public:
    /** Function 000: Construction function. */
    explicit Command_Panel(QWidget *parent = nullptr);
    /** Function 001: Destruction function. */
    ~Command_Panel();

    /** Function 300: Show window and record its postion. */
    void showDialog();

    /** Function 800: Get discharge type and information. */
    QList<double> getDischarge_information();
    /** Function 801: Get termination type and information. */
    QList<double> getTermination_information();
    /** Function 802: Get battery type and information. */
    double getBattery_information();

private:
    Ui::Command_Panel *ui;
};

#endif // C203_COMMAND_PANEL_H
