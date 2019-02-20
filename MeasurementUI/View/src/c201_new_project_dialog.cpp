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
#include "View/inc/c201_new_project_dialog.h"
#include "ui_c201_new_project_dialog.h"

/******************************************************************************
 *             Name: New_Project_Dialog
 *      Function ID: 000
 *      Create date: 07/02/2019
 * Last modify date: 16/02/2019
 *      Description: Construction function.
 ******************************************************************************/
New_Project_Dialog::New_Project_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::New_Project_Dialog)
{
    ui->setupUi(this);

    setModal(true);
    setWindowTitle("New Project");
    setFixedSize(600,160);

    _new_project_index = 0;
}

/******************************************************************************
 *             Name: ~New_Project_Dialog
 *      Function ID: 001
 *      Create date: 07/02/2019
 * Last modify date: 07/02/2019
 *      Description: Destruction function.
 ******************************************************************************/
New_Project_Dialog::~New_Project_Dialog()
{
    delete ui;
}

/******************************************************************************
 *             Name: on_pushButton_Browse_clicked
 *      Function ID: 700
 *      Create date: 16/02/2019
 * Last modify date: 16/02/2019
 *      Description: Slot for Browse push button clicked.
 ******************************************************************************/
void New_Project_Dialog::on_pushButton_Browse_clicked()
{
    QString project_name = QFileDialog::getExistingDirectory(this, tr("Choose directory for new project"), _current_path);
    if(project_name.length() > 0){
        _current_path = project_name;
    }
    ui->lineEdit_Loaction->setText(_current_path);

}

/******************************************************************************
 *             Name: on_buttonBox_accepted
 *      Function ID: 701
 *      Create date: 16/02/2019
 * Last modify date: 16/02/2019
 *      Description: Slot for OK push button in button box clicked.
 ******************************************************************************/
void New_Project_Dialog::on_buttonBox_accepted()
{
    _current_path = ui->lineEdit_Loaction->text();
    emit signal_new_project_comfirmed(ui->lineEdit_ProjectName->text(), _current_path);
}

/******************************************************************************
 *             Name: slot_trigger_new_project_dialog
 *      Function ID: 750
 *      Create date: 16/02/2019
 * Last modify date: 16/02/2019
 *      Description: Slot for triggering New Project Dialog.
 ******************************************************************************/
void New_Project_Dialog::slot_trigger_new_project_dialog()
{
//    qDebug() << "slot_trigger_new_project_dialog";

    _new_project_index++;
    ui->lineEdit_ProjectName->setText(MEASUREMENTUI_DAFAULT_PROJECT_NAME+QString::number(_new_project_index));
    ui->lineEdit_Loaction->setText(_current_path);
    show();
}

/******************************************************************************
 *             Name: slot_update_project_path
 *      Function ID: 751
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Slot for updating current path.
 ******************************************************************************/
void New_Project_Dialog::slot_update_current_path(QString current_path)
{
    _current_path = current_path;

#ifdef NEW_PROJECT_DIALOG_DEBUG
    qDebug() << "New_Project_Dialog: project path updated to: " << _current_path ;
#endif
}

