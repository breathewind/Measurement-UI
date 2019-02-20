/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Global functions.
 ******************************************************************************/
#ifndef C950_GLOBAL_FUNCTIONS_H
#define C950_GLOBAL_FUNCTIONS_H

#include <QObject>
#include <QString>

#include "h000_global_parameters.h"

class Global_Functions : public QObject
{
    Q_OBJECT
public:
    /** Function 000: Construction function. */
    Global_Functions();


    /** Function 002: Extract file path from file full path. */
    static QString extractFile_path(QString file_full_path);
    /** Function 003: Extract file full name from file full path. */
    static QString extractFile_full_name(QString file_full_path);
    /** Function 004: Extract file name from file full path. */
    static QString extractFile_name(QString file_full_path);
    /** Function 005: Extract file type from file full path. */
    static QString extractFile_type(QString file_full_path);
};

#endif // C950_GLOBAL_FUNCTIONS_H
