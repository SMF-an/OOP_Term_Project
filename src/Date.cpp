#include "Date.h"
#include <ctime>


using std::cout;
using std::endl;
using std::domain_error;
using std::string;
using std::to_string;
using std::ostream;


Date::Date(int y, int m, int d)   
{   
    nian = y; yue = m; ri = d;   
    int valid = IsValid();
    if(valid == 1)
    {
        throw domain_error("invalid day");
    }
    else if(valid == 2)
    {
        throw domain_error("invalid month");
    }
}


void Date::SetToday()
{
    time_t now = time(nullptr);
    tm* local_time = localtime(&now);
    nian = local_time->tm_year + 1900;
    yue = local_time->tm_mon + 1;
    ri = local_time->tm_mday;
}


Date::Date(const string& str)
{
    size_t pos1 = str.find('/');
    size_t pos2 = str.find('/', pos1 + 1);
    if(pos1 == string::npos || pos2 == string::npos || pos2 <= pos1 + 1)
    {
        throw domain_error("invalid date format");
    }
    
    nian = stoi(str.substr(0, pos1));
    yue = stoi(str.substr(pos1 + 1, pos2 - pos1 - 1));
    ri = stoi(str.substr(pos2 + 1));
    
    int valid = IsValid();
    if(valid == 1)
    {
        throw domain_error("invalid day");
    }
    else if(valid == 2)
    {
        throw domain_error("invalid month");
    }
}


bool Date::IsLeapYear() const
{
    if((nian % 100 != 0 && nian % 4 == 0) || nian % 400 == 0)
        return true;
    return false;
}


int Date::IsValid() const
{
    if(yue > 12 || yue < 1)
        return 2;
    if(ri < 1)
        return 1;
    if(IsLeapYear())
    {
        if(ri > month_list1[yue])
            return 1;
    }
    else
    {
        if(ri > month_list2[yue])
            return 1;
    }
    return 0;
}


std::string Date::Format() const
{
    return to_string(nian) + "/" + to_string(yue) + "/" + to_string(ri);
}


bool operator==(const Date& x, const Date& y)
{
    return (x.year() == y.year() && x.month() == y.month() && x.day() == y.day());
}   


bool operator!=(const Date& x, const Date& y)
{
    return !(x == y);
}


ostream& ShowCurrentTime(ostream& os)
{
    time_t now = time(nullptr);
    tm* local_time = localtime(&now);
    os << " " << Date::week_name[local_time->tm_wday] 
       << " " << Date::month_name[local_time->tm_mon]
       << "  " << local_time->tm_mday 
       << " " << local_time->tm_hour << ":" << local_time->tm_min << ":" << local_time->tm_sec 
       << " " << local_time->tm_year + 1900 << endl;
    return os;
}