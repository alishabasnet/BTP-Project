#include <iomanip>
#include "Utils.h"
#include "Time.h"

namespace seneca
{

    Time::Time(unsigned int min)
    {
        minutes = min;
    }

    Time &Time::reset()
    {
        minutes = U.getTime();
        return *this;
    }

    void Time::read(std::istream &is)
    {
        std::string input;
        is >> input;

        /**
         * reference taken from internet
         * 1. find/get index of certain character on string
         * https://www.geeksforgeeks.org/std-find-in-cpp
         */

        // 1. Find the index of ":" in input, and if it is -1 (npos), set istream as failbit
        if (input.find(':') == std::string::npos)
            return is.setstate(std::ios::failbit);

        size_t pos = input.find(':');
        int hours = std::stoi(input.substr(0, pos));
        int mins = std::stoi(input.substr(pos + 1));

        minutes = hours * 60 + mins;
    }

    void Time::write(std::ostream &ostr) const
    {
        unsigned int hours = minutes / 60;
        unsigned int mins = minutes % 60;

        // print hours
        ostr << std::setw(2) << std::setfill('0') << hours;
        // print colon

        ostr << ":";

        // print minute
        ostr << std::setw(2) << std::setfill('0') << mins;
    }

    std::ostream &operator<<(std::ostream &ostr, const Time &time)
    {
        time.write(ostr);
        return ostr;
    }

    std::istream &operator>>(std::istream &istr, Time &time)
    {
        time.read(istr);
        return istr;
    }

    Time::operator unsigned int() const
    {
        return minutes;
    }

    Time &Time::operator*=(int val)
    {
        minutes *= val;
        return *this;
    }

    Time &Time::operator-=(const Time &D)
    {
        if (minutes >= D.minutes)
            minutes -= D.minutes;
        else
            minutes = (minutes + 1440) - D.minutes;

        return *this;
    }

    Time Time::operator-(const Time &T) const
    {
        Time result;

        if (minutes >= T.minutes)
            result.minutes = minutes - T.minutes;
        else
            result.minutes = (minutes + 1440) - T.minutes;

        return result;
    }
}