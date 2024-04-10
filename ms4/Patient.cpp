#include <iomanip>
#include <sstream>
#include <string.h>

#include "Utils.h"
#include "Ticket.h"
#include "Patient.h"

namespace seneca
{
    bool Patient::setName(const char *name)
    {
        if (name != nullptr)
        {
            delete[] m_name;
            m_name = new char[strlen(name) + 1];
            strcpy(m_name, name);
            return true;
        }

        m_name = nullptr;
        return false;
    }

    Patient::Patient(int ticketNumber) : m_ticket(ticketNumber)
    {
        m_name = nullptr;
        m_ohipNumber = 0;
    }

    Patient::Patient(const Patient &other) : m_ticket(other.m_ticket)
    {
        m_name = new char[strlen(other.m_name) + 1];
        strcpy(m_name, other.m_name);

        m_ticket = other.m_ticket;
        m_ohipNumber = other.m_ohipNumber;
    }

    Patient::~Patient()
    {
        delete[] m_name;
        m_name = nullptr;
    }

    Patient &Patient::operator=(const Patient &other)
    {
        if (this == &other)
            return *this;

        setName(other.m_name);
        m_ticket = other.m_ticket;
        m_ohipNumber = other.m_ohipNumber;

        return *this;
    }

    bool Patient::isOhipNumberValid(int ohipNumber) const
    {
        return ohipNumber >= 100000000 && ohipNumber <= 999999999;
    }

    Time Patient::time() const
    {
        return m_ticket.time();
    }

    int Patient::number() const
    {
        return m_ticket.number();
    }

    Patient::operator bool() const
    {
        return m_name != nullptr && isOhipNumberValid(m_ohipNumber);
    }

    Patient::operator const char *() const
    {
        return m_name;
    }

    bool Patient::operator==(char other) const
    {
        return type() == other;
    }

    bool Patient::operator==(const Patient &other) const
    {
        return type() == other.type();
    }

    std::ostream &Patient::write(std::ostream &ostr) const
    {
        if (!*this)
            ostr << "Invalid Patient Record" << std::endl;

        else if (&ostr == &std::cout)
        {
            ostr << "Ticket No: " << m_ticket.number()
                 << ", Issued at: " << m_ticket.time() << std::endl;
            ostr << m_name << ", OHIP: " << m_ohipNumber << std::endl;
        }
        else if (&ostr == &std::clog)
        {
            ostr << std::left << std::setw(53) << std::setfill('.') << m_name;
            ostr << m_ohipNumber;

            // Insert the ticket number in 5 spaces, right-justified
            ostr << std::setw(5) << std::setfill(' ') << std::right << m_ticket.number();

            // Insert the ticket time
            ostr << " " << m_ticket.time();
        }
        else
        {
            ostr << type();
            ostr << "," << m_name;
            ostr << "," << m_ohipNumber << ",";
            m_ticket.write(ostr);
        }

        return ostr;
    }

    std::istream &Patient::read(std::istream &istr)
    {
        char tempName[51];
        std::string ohipNumber;

        if (&istr == &std::cin)
        {
            std::cout << "Name: ";
            istr.getline(tempName, 50);
            setName(tempName);

            // read ohip number
            std::cout << "OHIP: ";

            while (true)
            {
                std::getline(istr, ohipNumber);
                std::istringstream iss(ohipNumber);
                if (!(iss >> m_ohipNumber))
                {
                    std::cout << "Bad integer value, try again: ";
                    istr.clear();
                }
                else if (!isOhipNumberValid(m_ohipNumber))
                    std::cout << "Invalid value enterd, retry[100000000 <= value <= 999999999]: ";
                else
                    break;
            }
        }
        else
        {
            istr.get(tempName, 51, ',');
            if (strlen(tempName) <= 0)
            {
                delete[] m_name;
                m_name = nullptr;
                istr.setstate(std::ios_base::failbit);
                return istr;
            }
            else
            {
                setName(tempName);
            }

            istr.ignore();
            istr >> m_ohipNumber;

            if (!isOhipNumberValid(m_ohipNumber))
            {
                m_ohipNumber = 0;
                istr.setstate(std::ios_base::failbit);
                return istr;
            }

            istr.ignore(100, ',');

            std::string data;
            bool shouldStop = false;
            while (true)
            {
                char ch = '\0';
                char peek = istr.peek();
                if (peek == '\n' || (shouldStop && peek == ','))
                    break;

                istr >> ch;
                data += ch;

                if (!shouldStop && ch == ',')
                    shouldStop = true;
            }

            std::istringstream iss(data);
            m_ticket.read(iss);
        }
        return istr;
    }

    std::ostream &operator<<(std::ostream &os, const Patient &patient)
    {
        patient.write(os);
        return os;
    }

    std::istream &operator>>(std::istream &is, Patient &patient)
    {
        patient.read(is);
        return is;
    }

    void Patient::setArrivalTime()
    {
        m_ticket.resetTime();
    }

}