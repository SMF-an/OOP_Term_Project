#ifndef GUARD_date_h
#define GUARD_date_h

#include <iostream>
#include <string>

class Date
{
    public:
        Date(): nian(0), yue(0), ri(0)   { };
        Date(int y, int m, int d);  
        Date(const std::string&);
        void SetToday();
        
        int year()  const   {   return nian;    }
        int month()  const   {   return yue;    }
        int day()  const   {   return ri;    }
        bool IsLeapYear() const;
        int IsValid()    const;
        std::string Format() const;

        static constexpr const char* month_name[12] = {
            "January", "February", "March", "April", 
            "May", "June", "July", "August", "September", 
            "October", "November", "December"
        };
        static constexpr const char* week_name[7] = {
            "Sun", "Mon", "Tues", "Wednes", 
            "Thurs", "Fri", "Satur"
        };

    private:
        int nian;
        int yue;
        int ri;

        static constexpr const int month_list1[13] = {0, 31, 29, 31, 30 ,31, 30, 31, 31, 30, 31, 30, 31};
        static constexpr const int month_list2[13] = {0, 31, 28, 31, 30 ,31, 30, 31, 31, 30, 31, 30, 31};
};
bool operator==(const Date&, const Date&);
bool operator!=(const Date&, const Date&);
std::ostream& ShowCurrentTime(std::ostream&);
#endif