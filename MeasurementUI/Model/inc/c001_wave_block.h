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
#ifndef C001_WAVE_BLOCK_H
#define C001_WAVE_BLOCK_H
#include <QObject>

class Wave_Block
{
public:
    /** Function 000: Construction function. */
    Wave_Block(qint64 x_max);

    /** Function 300: Set first point of current wave block.*/
    void setFirst_point(qint64 x1, double y1);
    /** Function 301: Set second point of current wave block.*/
    void setSecond_point(qint64 x2, double y2);

    /** Function 302: Calculate all necessary information. */
    void calculate();

    /** Function 800: Get slope. */
    double slope();
    /** Function 801: Get intercept. */
    double intercept();
    /** Function 802: Get y starting point. */
    double y_start();
    /** Function 803: Get y ending point. */
    double y_end();
    /** Function 804: Get total power consumed by current wave block. */
    double power();

private:
    double _x1;
    double _x2;
    double _x_max;

    double _y1;
    double _y2;

    double _slope;
    double _intercept;

    double _y_start;
    double _y_end;

    double _power;
};

#endif // C001_WAVE_BLOCK_H
