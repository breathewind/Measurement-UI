/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 22/02/2019
 * Last modify date: 04/03/2019
 *      Description: Main window controller.
 *                   - Functional slots.
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: slot_update_data_from_settings
 *      Function ID: 750
 *      Create date: 22/02/2019
 * Last modify date: 22/02/2019
 *      Description: Slot for updating data from settings dialog to main
 *                   controller.
 ******************************************************************************/
void MainController::slot_update_data_from_settings(QList<QStringList> data_set)
{
    _dmm_baudrate = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_DMM).at(MEASUREMENTUI_INDEX_BAUDRATE);
    _dmm_databits = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_DMM).at(MEASUREMENTUI_INDEX_DATABITS);
    _dmm_stopbits = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_DMM).at(MEASUREMENTUI_INDEX_STOPBITS);
    _dmm_parity = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_DMM).at(MEASUREMENTUI_INDEX_PARITY);
    _dmm_flowcontrol = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_DMM).at(MEASUREMENTUI_INDEX_FLOWCONTROL);
    _dmm_port = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_DMM).at(MEASUREMENTUI_INDEX_PORT);

    _bc_baudrate = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_BC).at(MEASUREMENTUI_INDEX_BAUDRATE);
    _bc_databits = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_BC).at(MEASUREMENTUI_INDEX_DATABITS);
    _bc_stopbits = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_BC).at(MEASUREMENTUI_INDEX_STOPBITS);
    _bc_parity = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_BC).at(MEASUREMENTUI_INDEX_PARITY);
    _bc_flowcontrol = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_BC).at(MEASUREMENTUI_INDEX_FLOWCONTROL);
    _bc_port = data_set.at(SETTINGS_DIALOG_CONTROLLER_DATA_BC).at(MEASUREMENTUI_INDEX_PORT);

#ifdef MAINCONTROLLER_DEBUG
    debug_printSerial_information();
#endif
}

/******************************************************************************
 *             Name: slot_retrieveDMM_data
 *      Function ID: 751
 *      Create date: 25/02/2019
 * Last modify date: 26/02/2019
 *      Description: Slot for retrieving data from DMM when capture timer
 *                   timeout is reached.
 ******************************************************************************/
void MainController::slot_retrieveDMM_data(QString received_data)
{
    _data_read_buffer = received_data;
    _thistime_recorder = _main_elapsed_timer.elapsed();
#ifdef MAINCONTROLLER_DEBUG
    qint64 elapsed_time = _elapsed_timer.elapsed();
    qDebug() << "+ MainController: " << __FUNCTION__ << " The measurement operation took: " << elapsed_time << " milliseconds";
    qDebug() << "+ MainController: " << __FUNCTION__ << "- received_data: " << received_data;
#endif
}

/******************************************************************************
 *             Name: slot_read_serial_buffer
 *      Function ID: 752
 *      Create date: 25/02/2019
 * Last modify date: 28/02/2019
 *      Description: Slot for reading data from data read buffer when capture
 *                   timer timeout is reached.
 ******************************************************************************/
void MainController::slot_read_serial_buffer()
{
    _capture_timer->stop();

    switch(_sampling_command){
    case MAINCONTROLLER_VOLT_COMMAND_RUN:
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__ << "- data: " << QString("%1 V").arg(_data_read_buffer.toDouble());
#endif
        _battery_voltage_chart_view_controller->addOne_new_point(static_cast<int>(_thistime_recorder-_lastime_recorder), _data_read_buffer.toDouble());

        _lastime_recorder = _thistime_recorder;
        captureOne_measurement();
        break;
    case MAINCONTROLLER_VOLT_COMMAND_STOP:
        _DMM_controller->closeSerial();
        break;
    case MAINCONTROLLER_VOLT_COMMAND_PAUSE:
        break;
    default:
        break;
    }
}

/******************************************************************************
 *             Name: slot_retrieveDMM_data_for_current
 *      Function ID: 753
 *      Create date: 28/02/2019
 * Last modify date: 05/03/2019
 *      Description: Slot for retrieving data from DMM during current
 *                   measurement when one data to read is ready.
 ******************************************************************************/
void MainController::slot_retrieveDMM_data_for_current(QString received_data)
{
    int execution_time_recorder = static_cast<int>(_execution_elapsed_timer->elapsed());
    _data_read_buffer_current = received_data.toDouble()/_sense_resistance;

    switch (_execution_command) {
    case MAINCONTROLLER_EXE_COMMAND_RUN:
        createWave_block(execution_time_recorder);
        if(_total_mAh > _max_mAh){
            handleStop();
        }
        break;
    case MAINCONTROLLER_EXE_COMMAND_CALIBRATION:
        if( _calibration_factor == 8) {
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__ << "Calibration finished";
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "Final value: " << _control_resistance;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "Final current: " << _data_read_buffer_current;
#endif
//            _execution_command = MAINCONTROLLER_EXE_COMMAND_STOP;
//            _DMM_controller_current->closeSerial();
//            _BC_controller->closeSerial();
             startExecution(_control_resistance);
             _resistance_change_flag = false;
            _toggle_flag = MAINCONTROLLER_TOGGLE_FLAG_ON;
            if(_last_step_current > _data_read_buffer_current){
                _min_step_current = _last_step_current - _data_read_buffer_current;
            } else {
                _min_step_current = _data_read_buffer_current - _last_step_current;
            }
            _last_step_current = _data_read_buffer_current;
            _last_last_step_current = _data_read_buffer_current;
            return;
        }
        if(_data_read_buffer_current < _target_current && _calibration_factor == 0){
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__ << "Target current is larger than the maximum current";
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "Target current: " << _target_current;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "Maximum current: " << _data_read_buffer_current;
#endif
            return;
        }
        if(_data_read_buffer_current > _target_current){
            _control_resistance -= (128>>_calibration_factor);
        } else {
             _control_resistance += (128>>_calibration_factor);
        }
        _calibration_factor++;
        _BC_controller->sendMCU_Value(static_cast<char>(_control_resistance));
        _execution_capture_timer->start(1000);
        _last_step_current = _data_read_buffer_current;
        break;
    default:
        break;
    }

#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__ << "- received_data: " << received_data;
    qDebug() << "+ MainController: " << __FUNCTION__ << "- _current: " << _data_read_buffer_current;
    qDebug() << "+ MainController: " << __FUNCTION__ << "- _min_step_current: " << _min_step_current;
#endif
}

/******************************************************************************
 *             Name: slot_read_serial_buffer_for_current
 *      Function ID: 754
 *      Create date: 27/02/2019
 * Last modify date: 28/02/2019
 *      Description: Slot for reading data from data read buffer during current
 *                   measurement when capture timer timeout is reached.
 ******************************************************************************/
//void MainController::slot_read_serial_buffer_for_current()
//{
//    _capture_timer_current->stop();
//    _DMM_controller->writeDMM_command(":SYST:REM", false);
//    _DMM_controller->writeDMM_command(MEASUREMENTUI_VOLTAGE_COMMAND);
//}

/******************************************************************************
 *             Name: slot_change_load_current
 *      Function ID: 755
 *      Create date: 27/02/2019
 * Last modify date: 04/03/2019
 *      Description: Slot for changing load current when execution timer
 *                   timeout is reached.
 ******************************************************************************/
void MainController::slot_change_load_current()
{
    _execution_timer->stop();
    switch(_execution_command){
    case MAINCONTROLLER_EXE_COMMAND_RUN:
        if(_toggle_flag == MAINCONTROLLER_TOGGLE_FLAG_ON){
            startExecution(0);
            if(_resistance_change_flag){
                _min_step_current = (_last_last_step_current-_last_step_current)/static_cast<double>(_different_factor);
#ifdef MAINCONTROLLER_DEBUG
                qDebug() << "+ MainController: " << __FUNCTION__ << "- new _min_step_current: " << _min_step_current;
#endif
            }

             _last_last_step_current = _last_step_current;
            _last_step_current = _data_read_buffer_current;
#ifdef MAINCONTROLLER_DEBUG
            qDebug() << "+ MainController: " << __FUNCTION__ << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
            qDebug() << "+ MainController: " << __FUNCTION__ << "- _last_last_step_current: " << _last_last_step_current;
            qDebug() << "+ MainController: " << __FUNCTION__ << "- _last_step_current: " << _last_step_current;
#endif
            _different_factor =  static_cast<char>((_target_current-_last_step_current)/_min_step_current);
            if(_different_factor >0){
                _control_resistance += _different_factor;
                _resistance_change_flag = true;
#ifdef MAINCONTROLLER_DEBUG
                qDebug() << "+ MainController: " << __FUNCTION__ << "-------------------------------------------------------- ";
                qDebug() << "+ MainController: " << __FUNCTION__ << "- different_factor: " << static_cast<double>(_different_factor);
#endif
            } else if(_different_factor < 0) {
                _control_resistance -= static_cast<uint8_t>((_last_step_current- _target_current)/_min_step_current) ;
                _resistance_change_flag = true;
#ifdef MAINCONTROLLER_DEBUG
                qDebug() << "+ MainController: " << __FUNCTION__ << "n-------------------------------------------------------- ";
                qDebug() << "+ MainController: " << __FUNCTION__ << "- different_factor: " << static_cast<double>(_different_factor);
#endif
            }
        } else {
            startExecution(_control_resistance);
        }
        _toggle_flag = !_toggle_flag;
        break;
    case MAINCONTROLLER_EXE_COMMAND_STOP:
        _BC_controller->closeSerial();
        _DMM_controller_current->closeSerial();
        break;
    default:
        break;
    }
}

/******************************************************************************
 *             Name: slot_start_second_half_meausurement
 *      Function ID: 756
 *      Create date: 28/02/2019
 * Last modify date: 28/02/2019
 *      Description: Slot for startomg second half load current meausurement
 *                   when execution capture timer timeout is reached.
 ******************************************************************************/
void MainController::slot_start_second_half_meausurement()
{
    _execution_capture_timer->stop();
    _DMM_controller_current->writeDMM_command(":SYST:REM", false);
    _DMM_controller_current->writeDMM_command(MEASUREMENTUI_VOLTAGE_COMMAND);
}

/******************************************************************************
 *             Name: slot_battery_voltage_received
 *      Function ID: 757
 *      Create date: 04/03/2019
 * Last modify date: 05/03/2019
 *      Description: Slot for voltage current received from battery monitor.
 ******************************************************************************/
void MainController::slot_battery_voltage_received(QString voltage_value)
{
    qint64 current_time;
    _realtime_battery_voltage = voltage_value.toDouble()/1024.0*5.0;
    current_time = _main_elapsed_timer.elapsed();
    if(_execution_command == MAINCONTROLLER_EXE_COMMAND_RUN){
        _battery_voltage_chart_view_controller->addOne_new_point(static_cast<int>(current_time-_last_elapsed_time), _realtime_battery_voltage);
    }
//#ifdef MAINCONTROLLER_DEBUG
//                qDebug() << "+ MainController: " << __FUNCTION__ << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ";
//                qDebug() << "+ MainController: " << __FUNCTION__ << "- voltage_value: " << voltage_value;
//                qDebug() << "+ MainController: " << __FUNCTION__ << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ";
//#endif

    _last_elapsed_time = current_time;
}

/******************************************************************************
 *             Name: slot_read_battery_voltage
 *      Function ID: 758
 *      Create date: 04/03/2019
 * Last modify date: 04/03/2019
 *      Description: Slot for sending read voltage comand to MCU when voltage
 *                    capture timer timeout is reached.
 ******************************************************************************/
void MainController::slot_read_battery_voltage()
{
    _voltage_capture_timer->stop();
    _BC_controller->readVoltage();
    _voltage_capture_timer->start(_voltage_timer_timeout);
}

