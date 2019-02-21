#-------------------------------------------------
#
# Project created by QtCreator 2019-01-30T16:58:58
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MeasurementUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        View/src/c200_mainwindow.cpp\
        Controller/src/c100_serial_controller.cpp \
        Entities/src/c900_serial_definitions.cpp \
    View/src/c201_new_project_dialog.cpp \
    Controller/src/c999_maincontroller.cpp \
    Entities/src/c950_global_functions.cpp \
    View/src/c200_01_mainwindow_file_menu_action.cpp \
    Controller/src/c999_01_maincontroller_file_menu_action.cpp \
    View/src/c200_02_mainwindow_run_menu_action.cpp \
    Controller/src/c999_02_maincontroller_run_menu_action.cpp \
    View/src/c200_03_mainwindow_function_menu_action.cpp \
    Controller/src/c999_03_maincontroller_function_menu_action.cpp \
    View/src/c202_settings_dialog.cpp \
    View/src/c203_command_panel.cpp \
    View/src/c204_output_panel.cpp \
    View/src/c290_settings_dialog_serial_port_frame.cpp \
    Controller/src/c102_settings_dialog_controller.cpp \
    Controller/src/c190_settings_dialog_serial_port_frame_controller.cpp

HEADERS += \
        View/inc/c200_mainwindow.h\
        Controller/inc/c100_serial_controller.h \
        Entities/inc/c900_serial_definitions.h \
    View/inc/c201_new_project_dialog.h \
    Controller/inc/c999_maincontroller.h \
    h000_global_parameters.h \
    Entities/inc/c950_global_functions.h \
    View/inc/c202_settings_dialog.h \
    View/inc/c203_command_panel.h \
    View/inc/c204_output_panel.h \
    View/inc/c290_settings_dialog_serial_port_frame.h \
    h001_serial_parameters.h \
    Controller/inc/c102_settings_dialog_controller.h \
    Controller/inc/c190_settings_dialog_serial_port_frame_controller.h


FORMS += \
        View/forms/c200_mainwindow.ui \
    View/forms/c201_new_project_dialog.ui \
    View/forms/c202_settings_dialog.ui \
    View/forms/c203_command_panel.ui \
    View/forms/c204_output_panel.ui \
    View/forms/c290_settings_dialog_serial_port_frame.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
