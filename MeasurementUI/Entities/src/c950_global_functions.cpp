/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Global functions.
 ******************************************************************************/
#include "Entities/inc/c950_global_functions.h"

/******************************************************************************
 *             Name: Global_Functions
 *      Function ID: 000
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Construction function.
 ******************************************************************************/
Global_Functions::Global_Functions()
{

}

/******************************************************************************
 *             Name: extractFile_path
 *      Function ID: 002
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Extract file path from file full path.
 ******************************************************************************/
QString Global_Functions::extractFile_path(QString file_full_path)
{
    return file_full_path.left(file_full_path.lastIndexOf(MEASUREMENTUI_DIR_SYMBOL));
}

/***********************************************************************
 *             Name: extractFile_full_name
 *      Function ID: 003
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Extract file full name from file full path
 ***********************************************************************/
QString Global_Functions::extractFile_full_name(QString file_full_path)
{
    return file_full_path.right(file_full_path.size() - file_full_path.lastIndexOf(MEASUREMENTUI_DIR_SYMBOL) - 1);
}

/***********************************************************************
 *             Name: extractFile_name
 *      Function ID: 004
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Extract file name from file full path
 ***********************************************************************/
QString Global_Functions::extractFile_name(QString file_full_path)
{
    QString file_full_name = extractFile_full_name(file_full_path);
    return file_full_name.left(file_full_name.lastIndexOf("."));
}

/***********************************************************************
 *             Name: extractFile_type
 *      Function ID: 005
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Extract file name from file full type
 ***********************************************************************/
QString Global_Functions::extractFile_type(QString file_full_path)
{
    if(file_full_path.lastIndexOf(".")>=0){
        return file_full_path.right(file_full_path.size() - file_full_path.lastIndexOf(".") - 1);
    }else{
        return QString();
    }
}
