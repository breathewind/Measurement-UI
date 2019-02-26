/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 26/02/2019
 * Last modify date: 26/02/2019
 *      Description: Wave block model.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#include "Model/inc/c001_wave_block.h"

/******************************************************************************
 *             Name: Wave_Block
 *      Function ID: 000
 *      Create date: 26/02/2019
 * Last modify date: 26/02/2019
 *      Description: Construction function.
 ******************************************************************************/
Wave_Block::Wave_Block(qint64 x_max) : _x_max(static_cast<double>(x_max))
{

}

/******************************************************************************
 *             Name: setFirst_point
 *      Function ID: 300
 *      Create date: 26/02/2019
 * Last modify date: 26/02/2019
 *      Description: Set first point of current wave block.
 ******************************************************************************/
void Wave_Block::setFirst_point(qint64 x1, double y1)
{
    _x1 = static_cast<double>(x1);
    _y1 = y1;
}

/******************************************************************************
 *             Name: setSecned_point
 *      Function ID: 301
 *      Create date: 26/02/2019
 * Last modify date: 26/02/2019
 *      Description: Set second point of current wave block.
 ******************************************************************************/
void Wave_Block::setSecond_point(qint64 x2, double y2)
{
    _x2 = static_cast<double>(x2);
    _y2 = y2;
}

/******************************************************************************
 *             Name: calculate
 *      Function ID: 302
 *      Create date: 26/02/2019
 * Last modify date: 26/02/2019
 *      Description: Set second point of current wave block.
 ******************************************************************************/
void Wave_Block::calculate()
{
    _slope = (_y1-_y2) / (_x1-_x2);
    _intercept = (_x1*_y2 - _x2*_y1) / (_x1-_x2);
    _y_start = _intercept;
    _y_end = _slope * _x_max + _intercept;
    _power = (_y_start+_y_end)*_x_max/2/3600;
}

/******************************************************************************
 *             Name: slope
 *      Function ID: 800
 *      Create date: 26/02/2019
 * Last modify date: 26/02/2019
 *      Description: Get slope.
 ******************************************************************************/
double Wave_Block::slope()
{
    return _slope;
}

/******************************************************************************
 *             Name: intercept
 *      Function ID: 801
 *      Create date: 26/02/2019
 * Last modify date: 26/02/2019
 *      Description: Get intercept.
 ******************************************************************************/
double Wave_Block::intercept()
{
    return _intercept;
}

/******************************************************************************
 *             Name: y_start
 *      Function ID: 802
 *      Create date: 26/02/2019
 * Last modify date: 26/02/2019
 *      Description: Get y starting point.
 ******************************************************************************/
double Wave_Block::y_start()
{
    return _y_start;
}

/******************************************************************************
 *             Name: _y_end
 *      Function ID: 803
 *      Create date: 26/02/2019
 * Last modify date: 26/02/2019
 *      Description: Get y ending point.
 ******************************************************************************/
double Wave_Block::y_end()
{
    return _y_end;
}

/******************************************************************************
 *             Name: power
 *      Function ID: 804
 *      Create date: 26/02/2019
 * Last modify date: 26/02/2019
 *      Description: Get total power consumed by current wave block.
 ******************************************************************************/
double Wave_Block::power()
{
    return _power;
}

