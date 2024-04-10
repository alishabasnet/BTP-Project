#include "IOAble.h"

namespace seneca
{

    std::ostream &operator<<(std::ostream &os, const IOAble &obj)
    {
        return obj.write(os);
    }

    std::istream &operator>>(std::istream &is, IOAble &obj)
    {
        return obj.read(is);
    }

}
