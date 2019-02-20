/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 19/02/2019
 * Last modify date: 20/02/2019
 *      Description: Output Panel dialog of MeasurementUI application.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   6XX - View control functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#ifndef C204_OUTPUT_PANEL_H
#define C204_OUTPUT_PANEL_H

#include <QDialog>

#include "h000_global_parameters.h"

namespace Ui {
class Output_Panel;
}

class Output_Panel : public QDialog
{
    Q_OBJECT

public:
    /** Function 000: Construction function. */
    explicit Output_Panel(QWidget *parent = nullptr);
    /** Function 001: Destruction function. */
    ~Output_Panel();

    /** Function 300: Show window and record its postion. */
    void showDialog();

private:
    Ui::Output_Panel *ui;
};

#endif // C204_OUTPUT_PANEL_H
