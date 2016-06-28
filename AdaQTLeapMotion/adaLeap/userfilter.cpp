#include "userfilter.h"

UserFilter::UserFilter():sum(0),count(0),
    begin(0),end(0)
{

}
/**
 * @brief UserFilter::addItem
 * @return
 */
bool UserFilter::addItem(float item)
{    
    data[end] = item;
    if(++end >= CON_SIZE) end = 0;
    sum = sum + item;
    count ++;

    if(count >= FILGER_PARA)
    {
        sum = sum - data[begin];
        if(++begin >= CON_SIZE) begin = 0;
        count --;
    }
    result = sum / count;
    return true;
}
/**
 * @brief UserFilter::getResult
 * @return
 */
float UserFilter::getResult()
{
    return result;
}
