/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 25/02/2019
 * Last modify date: 04/03/2019
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

#define CHART_CONTROLLER_DEFAULT_TIME_RANGE    120000 // 2 mins
#define CHART_CONTROLLER_DEFAULT_TIMESTEP      1000 // 1 s
#define CHART_CONTROLLER_DEFAULT_VOLTAGE_RANGE 4.5

QT_CHARTS_USE_NAMESPACE

class Chart_Controller : public QObject
{
    Q_OBJECT
public:
    /** Function 000: Construction function. */
    Chart_Controller(QString chart_title, qint64 x_range, QString y_unit);

    /** Function 300: Get chart view. */
    QChartView *getChart_view();
    /** Function 301: Add one new voltage value to chart. */
    void addOne_new_point(int step, double voltage_value);
    /** Function 302: Reset the chart as default values. */
    void reset();
    /** Function 303: Set display range of  Y axis. */
    void setY_range(double y_range_min, double y_range_max);

private:
    /** Function 002: Set the chart as default values. */
    void init();

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

    QString _chart_title;
    QString _y_unit;
};

#endif // C110_CHART_CONTROLLER_H
