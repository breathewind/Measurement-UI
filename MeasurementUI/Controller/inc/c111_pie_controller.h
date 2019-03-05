/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 05/03/2019
 * Last modify date: 05/03/2019
 *      Description: Pie chart controller.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#ifndef C111_PIE_CONTROLLER_H
#define C111_PIE_CONTROLLER_H

#include <QObject>
#include <QChart>
#include <QCategoryAxis>
//#include <QValueAxis>
#include <QChartView>

#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

#include "h000_global_parameters.h"

#ifdef PIE_CONTROLLER_DEBUG
#include <QtDebug>
#endif

QT_CHARTS_USE_NAMESPACE

class Pie_Controller : public QObject
{
    Q_OBJECT
public:
    /** Function 000: Construction function. */
    explicit Pie_Controller(QObject *parent = nullptr);

    /** Function 300: Set the percentage of slice0. slice1 will be kept consistent with the percentage of slice0. */
    void setUsed_percentage(qreal used_percentage);
    /** Function 301: Reset pie chart. */
    void reset();

    /** Function 800: Get chart view. */
    QChartView *getChart_view();

public slots:

private:
    /** Function 002: Set the pie chart using default values. */
    void init();

    QPieSeries *_series;
    QPieSlice *_slice0;
    QPieSlice *_slice1;

    QChart *_chart;
    QChartView *_chart_view;

signals:
};

#endif // C111_PIE_CONTROLLER_H
