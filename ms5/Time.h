#ifndef SENECA_TIME_H_
#define SENECA_TIME_H_

#include <iostream>

namespace seneca
{

    class Time
    {
    private:
        unsigned int minutes;

    public:
        Time(unsigned int min = 0u);
        Time &reset();

        void read(std::istream &istr);
        void write(std::ostream &ostr) const;

        operator unsigned int() const;

        Time &operator*=(int val);
        Time &operator-=(const Time &D);
        Time operator-(const Time &T) const;

        friend std::istream &operator>>(std::istream &istr, Time &time);
        friend std::ostream &operator<<(std::ostream &ostr, const Time &time);
    };

}

#endif
