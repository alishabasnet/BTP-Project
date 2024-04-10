#include "TestPatient.h"

namespace seneca
{

    int TestPatient::nextTestTicket = 1;

    TestPatient::TestPatient() : Patient(nextTestTicket++) {}

    char TestPatient::type() const
    {
        return 'C';
    }

    std::ostream &TestPatient::write(std::ostream &ostr) const
    {
        if (&ostr == &std::cout)
        {
            ostr << "Contagion TEST" << std::endl;
        }
        Patient::write(ostr);
        return ostr;
    }

    std::istream &TestPatient::read(std::istream &istr)
    {
        Patient::read(istr);
        nextTestTicket = m_ticket.number() + 1;
        return istr;
    }

    std::ostream &operator<<(std::ostream &ostr, const TestPatient &patient)
    {
        patient.write(ostr);
        return ostr;
    }

    std::istream &operator>>(std::istream &istr, TestPatient &patient)
    {
        patient.read(istr);
        return istr;
    }

} // namespace seneca
