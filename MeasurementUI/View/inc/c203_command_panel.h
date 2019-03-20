/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 19/02/2019
 * Last modify date: 20/03/2019
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

#define COMMAND_PANEL_SAVE_FILE_UNCHECKED 0
#define COMMAND_PANEL_SAVE_FILE_CHECKED   1

/**************** Default values ****************/
#define COMMAND_PANEL_DEFAULT_SW_MIN_I   1
#define COMMAND_PANEL_DEFAULT_SW_MAX_I   3
#define COMMAND_PANEL_DEFAULT_SW_PERIOD  4
#define COMMAND_PANEL_DEFAULT_CC_CURRENT 2

#define COMMAND_PANEL_DEFAULT_TCC_COULOMB 2000
#define COMMAND_PANEL_DEFAULT_TOCV_OCV    3.0

#define COMMAND_PANEL_DEFAULT_RATE_CAPACITY 3200

/**************** Parameters index (among all the parameters) ****************/
#define COMMAND_PANEL_DISCHARGE_TYPE_ALL_INDEX   0
#define COMMAND_PANEL_SW_MIN_CURRENT_ALL_INDEX   1
#define COMMAND_PANEL_SW_MAX_CURRENT_ALL_INDEX   2
#define COMMAND_PANEL_SW_PERIOD_ALL_INDEX        3
#define COMMAND_PANEL_CC_CURRENT_ALL_INDEX       4
#define COMMAND_PANEL_TERMINATION_TYPE_ALL_INDEX 5
#define COMMAND_PANEL_TCC_COULOMB_ALL_INDEX      6
#define COMMAND_PANEL_TVOC_VOLTAGE_ALL_INDEX     7
#define COMMAND_PANEL_RATE_CAPACITY_ALL_INDEX    8
#define COMMAND_PANEL_SAVE_FLAG_ALL_INDEX        9
#define COMMAND_PANEL_SAVE_PATH_ALL_INDEX        10

#include <QDialog>
#include <QFileDialog>

#include "h000_global_parameters.h"
#include "Entities/inc/c950_global_functions.h"

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
    /** Function 301: Hide window. */
    void hideDialog();
    /** Function 302: Set all options in command window as default value. */
    void setDefault(QString output_file);
    /** Function 303: Update all options in command window. */
    void updateInformation(int type, double min_i, double max_i, double period, double current,
                           int options, int coulomb, double ocv,
                           int capacity,
                           int save_flag, QString save_path);

    /** Function 800: Get discharge type and information. */
    QList<double> getDischarge_information();
    /** Function 801: Get termination type and information. */
    QList<double> getTermination_information();
    /** Function 802: Get battery type and information. */
    double getBattery_information();
    /** Function 803: Get all information from command panel. */
    QStringList getAllInformation();

    /** Function 810: Set discharge type. */
    void setDischargeType(int type);
    /** Function 811: Set minimum discharge current. */
    void setMinDischargeCurrent(QString min_discharge_current);
    /** Function 812: Set maximum discharge current. */
    void setMaxDischargeCurrent(QString max_discharge_current);
    /** Function 813: Set square wave period. */
    void setSquareWavePeriod(QString period);
    /** Function 814: Set constant discharge current. */
    void setConstantDischargeCurrent(QString constant_discharge_current);
    /** Function 815: Set termination type. */
    void setTerminationType(int type);
    /** Function 816: Set target coulomb. */
    void setTargetCoulomb(QString target_TCC);
    /** Function 817: Set target OCV. */
    void setTargetOCV(QString target_TOCV);
    /** Function 818: Set rate capacity. */
    void setRateCapacity(QString rate_capacity);
    /** Function 819: Set save flag. */
    void setSaveFlag(int flag);
    /** Function 820: Set save path. */
    void setSavePath(QString path);

private:
    /** Function 002: Set check boxes for discharge type. */
    void setChecked_type(int type);
    /** Function 003: Set display logic for discharge type. */
    void setLogic_type(int type);
    /** Function 004: Set check boxes for stop discharging options (termination type). */
    void setChecked_option(int option);
    /** Function 005: Set display logic for stop discharging options (termination type). */
    void setLogic_option(int option);
    /** Function 006: Set display logic for save file. */
    void setLogic_save_file(int save_file_flag);

    Ui::Command_Panel *ui;

private slots:
    /** Function 700: Slot for Browse button clicked. */
    void on_pushButton_browse_clicked();
    /** Function 701: Slot for square wave radio button toggled. */
    void on_radioButton_SW_toggled(bool checked);
    /** Function 702: Slot for terminating by coulomb counting radio button toggled. */
    void on_radioButton_TCC_toggled(bool checked);
    /** Function 703: Slot for save file check box toggled. */
    void on_checkBox_save_file_toggled(bool checked);
};

#endif // C203_COMMAND_PANEL_H
