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
#include "Controller/inc/c111_pie_controller.h"

/******************************************************************************
 *             Name: Pie_Controller
 *      Function ID: 000
 *      Create date: 05/03/2019
 * Last modify date: 05/03/2019
 *      Description: Construction function.
 ******************************************************************************/
Pie_Controller::Pie_Controller(QObject *parent) : QObject(parent)
{
    init();
}

/******************************************************************************
 *             Name: init
 *      Function ID: 002
 *      Create date: 05/03/2019
 * Last modify date: 05/03/2019
 *      Description: Set the chart using default values.
 ******************************************************************************/
void Pie_Controller::init()
{
    _series = new QPieSeries();
    _series->append("Used", 0);
    _series->append("Unused", 1);

    _slice0 = _series->slices().at(0);
//    _slice1->setExploded();
    _slice0->setLabelVisible(false);
//    _slice1->setPen(QPen(Qt::darkGreen, 2));
    _slice0->setBrush(Qt::red);

    _slice1 = _series->slices().at(1);
    _slice1->setLabelVisible(false);
    _slice1->setBrush(Qt::blue);

    _chart = new QChart();
    _chart->addSeries(_series);
    _chart->setTitle("Bettery Capacity (mAh)");
//    _chart->legend()->hide();

    _chart_view = new QChartView(_chart);
    _chart_view->setRenderHint(QPainter::Antialiasing);

    setUsed_percentage(.90);
}

/******************************************************************************
 *             Name: setUsed_percentage
 *      Function ID: 300
 *      Create date: 05/03/2019
 * Last modify date: 05/03/2019
 *      Description: Set the percentage of slice0. slice1 will be kept
 *                   consistent with the percentage of slice0.
 ******************************************************************************/
void Pie_Controller::setUsed_percentage(qreal used_percentage)
{
    _slice0->setValue(used_percentage);
    _slice1->setValue(1-used_percentage);
}

/******************************************************************************
 *             Name: reset
 *      Function ID: 301
 *      Create date: 05/03/2019
 * Last modify date: 05/03/2019
 *      Description: Reset pie chart.
 ******************************************************************************/
void Pie_Controller::reset()
{
    setUsed_percentage(0);
}

/******************************************************************************
 *             Name: getChart_view
 *      Function ID: 800
 *      Create date: 05/03/2019
 * Last modify date: 05/03/2019
 *      Description: Get chart view.
 ******************************************************************************/
QChartView *Pie_Controller::getChart_view()
{
    return _chart_view;
}
