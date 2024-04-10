#include "TriagePatient.h"

namespace seneca
{
    int TriagePatient::nextTriageTicket = 1;

    TriagePatient::TriagePatient() : Patient(nextTriageTicket++)
    {
        m_symptoms = nullptr;
    }

    TriagePatient::TriagePatient(const TriagePatient &other) : Patient(other)
    {
        if (other.m_symptoms != nullptr)
        {
            m_symptoms = new char[strlen(other.m_symptoms) + 1];
            strcpy(m_symptoms, other.m_symptoms);
        }
        else
        {
            m_symptoms = nullptr;
        }
    }

    TriagePatient::~TriagePatient()
    {
        delete[] m_symptoms;
        m_symptoms = nullptr;
    }

    TriagePatient &TriagePatient::operator=(const TriagePatient &other)
    {
        if (this != &other)
        {
            Patient::operator=(other);

            delete[] m_symptoms;
            if (other.m_symptoms != nullptr)
            {
                m_symptoms = new char[strlen(other.m_symptoms) + 1];
                strcpy(m_symptoms, other.m_symptoms);
            }
            else
            {
                m_symptoms = nullptr;
            }
        }
        return *this;
    }

    char TriagePatient::type() const
    {
        return 'T';
    }

    std::ostream &TriagePatient::write(std::ostream &ostr) const
    {
        if (&ostr == &std::cout)
            ostr << "TRIAGE" << std::endl;

        Patient::write(ostr);

        if (m_symptoms == nullptr)
            return ostr;

        if (&ostr == &std::cout)
        {
            ostr << "Symptoms: " << m_symptoms << std::endl;
        }
        else
        {
            ostr << "," << m_symptoms;
        }
        return ostr;
    }

    std::istream &TriagePatient::read(std::istream &istr)
    {

        Patient::read(istr);
        char symptoms[512] = {'\0'};

        if (&istr == &std::cin)
        {
            std::cout << "Symptoms: ";
            istr.getline(symptoms, 511);
        }
        else
        {
            istr.ignore(100, ',');
            istr.getline(symptoms, 511);
        }

        delete[] m_symptoms;
        m_symptoms = new char[strlen(symptoms) + 1];
        strcpy(m_symptoms, symptoms);

        if (istr.fail())
        {
            delete[] m_symptoms;
            m_symptoms = nullptr;
        }

        nextTriageTicket = m_ticket.number() + 1;
        return istr;
    }

    std::istream &operator>>(std::istream &is, TriagePatient &patient)
    {
        patient.read(is);
        return is;
    }

    std::ostream &operator<<(std::ostream &os, const TriagePatient &patient)
    {
        patient.write(os);
        return os;
    }

} // namespace seneca
