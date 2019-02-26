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
#include "Controller/inc/c110_chart_controller.h"

/******************************************************************************
 *             Name: Chart_Controller
 *      Function ID: 000
 *      Create date: 25/02/2019
 * Last modify date: 26/02/2019
 *      Description: Construction function.
 ******************************************************************************/
Chart_Controller::Chart_Controller(QString chart_title, QString y_unit) :
    _chart_title(chart_title), _y_unit(y_unit)
{
    init();
}

/******************************************************************************
 *             Name: init
 *      Function ID: 302
 *      Create date: 26/02/2019
 * Last modify date: 26/02/2019
 *      Description: Set the chart as default values.
 ******************************************************************************/
void Chart_Controller::init()
{
    _current_ms = 0;
    _time_range = CHART_CONTROLLER_DEFAULT_TIME_RANGE;
    _timestep = CHART_CONTROLLER_DEFAULT_TIMESTEP;
    _y_range = CHART_CONTROLLER_DEFAULT_VOLTAGE_RANGE;
    _time_range_shift = 0;
    _max_minutes = 0;

    _serises = new QLineSeries();
    _serises->append(0, 0);

    _chart = new QChart();
    _chart->legend()->hide();
    _chart->addSeries(_serises);
    _chart->createDefaultAxes();

    QFont font;
    font.setPixelSize(10);
    _chart->setTitleFont(font);
    _chart->setTitleBrush(QBrush(Qt::black));
    _chart->setTitle(_chart_title);


    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(Qt::cyan));
    _serises->setPen(pen);

//    _battery_voltage_chart->setAnimationOptions(QChart::AllAnimations); // Chart animations

    _axisX = new QCategoryAxis();
    _axisX->setMin(_current_ms);
    _axisX->setMax(_time_range);
    _axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
//    axisX->setStartValue(0);

    for (_max_minutes=0; _max_minutes<11; _max_minutes++) {
        _axisX->append(QString("%1'").arg(_max_minutes) , _max_minutes*_timestep*60);
    }

    _chart->setAxisX(_axisX, _serises);
    _serises->attachAxis(_axisX);

    _axisY = new QCategoryAxis();
    _axisY->setMin(0);
    _axisY->setMax(_y_range);
    _axisY->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    for (int i=0; i<_y_range; i++) {
        _axisY->append(QString("%1 %2").arg(i).arg(_y_unit) , i);
    }

    _chart->setAxisY(_axisY, _serises);

    _chart_view = new QChartView(_chart);
    _chart_view->setRenderHint(QPainter::Antialiasing);
}


/******************************************************************************
 *             Name: getChart_view
 *      Function ID: 300
 *      Create date: 25/02/2019
 * Last modify date: 26/02/2019
 *      Description: Get chart view.
 ******************************************************************************/
QChartView *Chart_Controller::getChart_view()
{
    return _chart_view;
}

/******************************************************************************
 *             Name: addOne_new_voltage
 *      Function ID: 301
 *      Create date: 25/02/2019
 * Last modify date: 26/02/2019
 *      Description: Add one new voltage value to chart.
 ******************************************************************************/
void Chart_Controller::addOne_new_voltage(int step, double voltage_value)
{
    _current_ms += step;

    if(_current_ms > _time_range+_time_range_shift){
        _time_range_shift += step;

        _axisX->setMin(_time_range_shift);
        _axisX->setMax(_time_range+_time_range_shift);
        _axisX->setStartValue(_time_range_shift);

        _serises->remove(0);
    }

    if(_current_ms/60000  > _max_minutes-1){
        _axisX->remove(QString("%1'").arg(_max_minutes-static_cast<qint64>(_time_range/60000)-1));
        _axisX->append(QString("%1'").arg(_max_minutes) , _max_minutes*_timestep*60);
        _max_minutes++;
    }

    _serises->append(_current_ms, voltage_value);
    _chart_view->update();

#ifdef CHART_CONTROLLER_DEBUG
    qDebug() << _current_ms << voltage_value;
#endif
}

/******************************************************************************
 *             Name: reset
 *      Function ID: 302
 *      Create date: 26/02/2019
 * Last modify date: 26/02/2019
 *      Description: Reset the chart as default values.
 ******************************************************************************/
void Chart_Controller::reset()
{
    for (int i=0; i<11; i++) {
        _axisX->remove(QString("%1'").arg(_max_minutes-static_cast<qint64>(_time_range/60000)-1+i));
    }

    _current_ms = 0;
    _time_range = CHART_CONTROLLER_DEFAULT_TIME_RANGE;
    _timestep = CHART_CONTROLLER_DEFAULT_TIMESTEP;
    _y_range = CHART_CONTROLLER_DEFAULT_VOLTAGE_RANGE;
    _time_range_shift = 0;

    _axisX->setMin(_current_ms);
    _axisX->setMax(_time_range);

    for (_max_minutes=0; _max_minutes<11; _max_minutes++) {
        _axisX->append(QString("%1'").arg(_max_minutes) , _max_minutes*_timestep*60);
    }

    _serises->clear();
    _serises->append(0, 0);
}
