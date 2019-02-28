/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 18/02/2019
 * Last modify date: 28/02/2019
 *      Description: Main window controller.
 *                   - Functions related to file menu actions.
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: handleStart
 *      Function ID: 236
 *      Create date: 18/02/2019
 * Last modify date: 27/02/2019
 *      Description: Function for handle operations related to Start.
 ******************************************************************************/
void MainController::handleStart()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__;
    debug_printSerial_information();
#endif
    _execution_period = MAINCONTTROLLER_DEFAULT_EXECUTION_TIMER_TIMEOUT;

/** Serial port configuration */
    /** DMM controller */
    _DMM_controller->setPortName(_dmm_port);
    _DMM_controller->setBaudRate(__serial_definitions.getBaudrate(_dmm_baudrate));
    _DMM_controller->setParity(static_cast<QSerialPort::Parity>(__serial_definitions.getParity(_dmm_parity)));
    _DMM_controller->setDataBits(static_cast<QSerialPort::DataBits>(__serial_definitions.getDataBits(_dmm_databits)));
    _DMM_controller->setStopBits(static_cast<QSerialPort::StopBits>(__serial_definitions.getStopBits(_dmm_stopbits)));
    _DMM_controller->setFlowControl(static_cast<QSerialPort::FlowControl>(__serial_definitions.getFlowcontrol(_dmm_flowcontrol)));
    /** BC controller */
    _BC_controller->setPortName(_bc_port);
    _BC_controller->setBaudRate(__serial_definitions.getBaudrate(_bc_baudrate));
    _BC_controller->setParity(static_cast<QSerialPort::Parity>(__serial_definitions.getParity(_bc_parity)));
    _BC_controller->setDataBits(static_cast<QSerialPort::DataBits>(__serial_definitions.getDataBits(_bc_databits)));
    _BC_controller->setStopBits(static_cast<QSerialPort::StopBits>(__serial_definitions.getStopBits(_bc_stopbits)));
    _BC_controller->setFlowControl(static_cast<QSerialPort::FlowControl>(__serial_definitions.getFlowcontrol(_bc_flowcontrol)));

    _main_elapsed_timer.start();
//    _lastime_recorder =  _main_elapsed_timer.elapsed();

    _battery_voltage_chart_view_controller->reset();
    _load_current_chart_view_controller->reset();

    _DMM_controller->startSerial();
    _BC_controller->startSerial();

    _DMM_controller->writeDMM_command(":SYST:REM", false);

#ifdef MAINCONTROLLER_DEBUG
    test_counter = 0;
#endif

    startExecution();
//    captureOne_measurement();
}


/******************************************************************************
 *             Name: handleStop
 *      Function ID: 237
 *      Create date: 18/02/2019
 * Last modify date: 28/02/2019
 *      Description: Function for handle operations related to Stop.
 ******************************************************************************/
void MainController::handleStop()
{
    _sampling_command = MAINCONTROLLER_VOLT_COMMAND_STOP;
//    _sampling_command_current = MAINCONTROLLER_CURR_COMMAND_STOP;

    _execution_command = MAINCONTROLLER_EXE_COMMAND_STOP;

#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__;
#endif
}

