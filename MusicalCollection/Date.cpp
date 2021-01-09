#include "Date.h"

Date::Date()
{
    day = 0;
    month = 0;
    year = 0;
}

Date::Date(int _day, int _month, int _year )
{
    if (!Date::isDateValid(_day, _month, _year))throw ("Bad Date");
    day = _day;
    month = _month;
    year = _year;
}

bool Date::isLeap(int year)
{
    return (((year % 4 == 0) &&
        (year % 100 != 0)) ||
        (year % 400 == 0));
}

bool Date::isDateValid(int d, int m, int y)
{
    if (y > c_MAX_VALID_YEAR ||
        y < c_MIN_VALID_YEAR)
        return false;
    if (m < 1 || m > 12)
        return false;
    if (d < 1 || d > 31)
        return false;
    if (m == 2)
    {
        if (isLeap(y))
            return (d <= 29);
        else
            return (d <= 28);
    }
    if (m == 4 || m == 6 ||
        m == 9 || m == 11)
        return (d <= 30);

    return true;
}
int Date::getDay() const
{
    return day;
}

int Date::getMonth()const
{
    return month;
}

int Date::getYear()const
{
    return year;
}
