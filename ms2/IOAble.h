#ifndef SENECA_IOABLE_H
#define SENECA_IOABLE_H

#include <iostream>

namespace seneca
{

    class IOAble
    {
    public:
        virtual std::ostream &write(std::ostream &os) const = 0;

        virtual std::istream &read(std::istream &is) = 0;

        virtual ~IOAble() {}

        friend std::ostream &operator<<(std::ostream &os, const IOAble &obj);

        friend std::istream &operator>>(std::istream &is, IOAble &obj);
    };

    std::ostream &operator<<(std::ostream &os, const IOAble &obj);

    std::istream &operator>>(std::istream &is, IOAble &obj);

}

#endif
