/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 07/02/2019
 * Last modify date: 18/02/2019
 *      Description: New project dialog of MeasurementUI application.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   6XX - View control functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#ifndef C201_NEW_PROJECT_DIALOG_H
#define C201_NEW_PROJECT_DIALOG_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>

#include "h000_global_parameters.h"

#define NEW_PROJECT_DIALOG_DEBUG

#ifdef NEW_PROJECT_DIALOG_DEBUG
#include <QDebug>
#endif

namespace Ui {
class New_Project_Dialog;
}

class New_Project_Dialog : public QDialog
{
    Q_OBJECT

public:
    /** Function 000: Construction function. */
    explicit New_Project_Dialog(QWidget *parent = nullptr);
    /** Function 001: Destruction function. */
    ~New_Project_Dialog();

public slots:
    /** Function 750: Slot for triggering New Project Dialog. */
    void slot_trigger_new_project_dialog();

    /** Function 751: Slot for updating current path. */
    void slot_update_current_path(QString current_path);

private:
    Ui::New_Project_Dialog *ui;
    int _new_project_index;

    QString _current_path;

private slots:
    /** Function 700: Slot for Browse push button clicked. */
    void on_pushButton_Browse_clicked();
    /** Function 701: Slot for OK push button in button box clicked. */
    void on_buttonBox_accepted();

signals:
    void signal_new_project_comfirmed(QString project_name, QString project_path);
};

#endif // C201_NEW_PROJECT_DIALOG_H
