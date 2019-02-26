/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 25/02/2019
 * Last modify date: 26/02/2019
 *      Description: Chart controller.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#ifndef C110_CHART_CONTROLLER_H
#define C110_CHART_CONTROLLER_H

#include <QObject>
#include <QChart>
//#include <QSplineSeries>
#include <QLineSeries>
#include <QCategoryAxis>
//#include <QValueAxis>
#include <QChartView>

#include "h000_global_parameters.h"

#ifdef CHART_CONTROLLER_DEBUG
#include <QtDebug>
#endif

#define CHART_CONTROLLER_DEFAULT_TIME_RANGE    600000 // 10 mins
#define CHART_CONTROLLER_DEFAULT_TIMESTEP      1000 // 1 s
#define CHART_CONTROLLER_DEFAULT_VOLTAGE_RANGE 4.5

QT_CHARTS_USE_NAMESPACE

class Chart_Controller : public QObject
{
    Q_OBJECT
public:
    /** Function 000: Construction function. */
    Chart_Controller(QString chart_title, QString y_unit);

    /** Function 300: Get chart view. */
    QChartView *getChart_view();
    /** Function 301: Add one new voltage value to chart. */
    void addOne_new_voltage(int step, double voltage_value);

private:
    QChart *_chart;
    QLineSeries *_serises;
    QChartView *_chart_view;


    qint64 _current_ms;
    qint64 _time_range;
    qint64 _time_range_shift;
    qint64 _max_minutes;
    int _timestep;

    double _y_range;

    QCategoryAxis *_axisX;
    QCategoryAxis *_axisY;
};

#endif // C110_CHART_CONTROLLER_H
