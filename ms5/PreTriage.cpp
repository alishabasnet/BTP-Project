#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string.h>

#include "Utils.h"
#include "PreTriage.h"
#include "TestPatient.h"
#include "TriagePatient.h"

namespace seneca
{

    PreTriage::PreTriage(const char *dataFilename) : m_triageWaitTime(5), m_contagionWaitTime(15)
    {
        m_dataFilename = new char[strlen(dataFilename) + 1];
        strcpy(m_dataFilename, dataFilename);
        loadData();
    }

    PreTriage::~PreTriage()
    {
        saveData();
        delete[] m_dataFilename;
        for (int i = 0; i < m_lineupSize; i++)
            delete m_lineup[i];
    }

    void PreTriage::loadData()
    {
        std::cout << "Loading data..." << std::endl;
        std::ifstream file(m_dataFilename);

        if (file)
        {
            std::string line;
            std::getline(file, line, ',');
            std::istringstream iss(line);

            iss >> m_contagionWaitTime;
            file >> m_triageWaitTime;

            while (!file.eof())
            {

                if (m_lineupSize >= MAX_PATIENTS)
                {
                    std::cerr << "Warning: number of records exceeded 100" << std::endl;
                    break;
                }

                char type = '\0';

                file >> type;
                file.ignore(100, ',');
                Patient *patient = nullptr;

                if (type == 'C')
                    patient = new TestPatient();
                else if (type == 'T')
                    patient = new TriagePatient();

                if (patient)
                {
                    patient->read(file);
                    m_lineup[m_lineupSize++] = patient;
                }
            }
        }

        if (m_lineupSize == 0)
        {
            std::cerr << "No data or bad data file!" << std::endl
                      << std::endl;
        }
        else
        {
            std::cout << m_lineupSize << " Records imported..." << std::endl
                      << std::endl;
            ;
        }
    }

    void PreTriage::run()
    {
        int selection;
        Menu m_appMenu("General Healthcare Facility Pre-Triage Application\n1- Register\n2- Admit\n3- View Lineup", 0);

        while (m_appMenu >> selection)
        {
            switch (selection)
            {
            case 1:
                registerPatient();
                break;
            case 2:
                admitPatient();
                break;
            case 3:
                lineup();
                break;
            case 0:
                return;
            }
        }
    }

    void PreTriage::registerPatient()
    {
        if (m_lineupSize >= MAX_PATIENTS)
        {
            std::cerr << "Line up full!" << std::endl;
            return;
        }

        Menu m("Select Type of Registration:\n1- Contagion Test\n2- Triage", 3);

        int selection;
        m >> selection;

        Patient *p = nullptr;

        if (selection == 0)
            return;
        else if (selection == 1)
        {
            p = new TestPatient();
        }
        else if (selection == 2)
        {
            p = new TriagePatient();
        }

        std::cout << "Please enter patient information: " << std::endl;

        std::cin >> *p;
        p->setArrivalTime();

        std::cout << std::endl;
        std::cout << "******************************************" << std::endl;
        std::cout << *p;
        std::cout << "Estimated Wait Time: " << getWaitTime(*p) << std::endl;
        std::cout << "******************************************" << std::endl
                  << std::endl;

        m_lineup[m_lineupSize++] = p;
    }

    void PreTriage::admitPatient()
    {
        Menu m("Select Type of Admittance:\n1- Contagion Test\n2- Triage", 3);

        int selection;
        m >> selection;

        if (selection == 0)
            return;

        int idx = indexOfFirstInLine(selection == 1 ? 'C' : 'T');

        if (idx == -1)
        {
            std::cerr << "Lineup is empty!" << std::endl;
            return;
        }

        Patient *p = m_lineup[idx];

        Time callTime(U.getTime());

        std::cout << std::endl;
        std::cout << "******************************************" << std::endl;
        std::cout << "Call time: [" << callTime << "]" << std::endl;
        std::cout << "Calling at for ";
        p->write(std::cout);
        std::cout << "******************************************" << std::endl
                  << std::endl;

        setAverageWaitTime(*p);
        removePatientFromLineup(idx);
        U.setDebugTime(8, 49);
    }

    void PreTriage::lineup()
    {
        Menu m("Select The Lineup:\n1- Contagion Test\n2- Triage", 3);

        int selection;
        m >> selection;
        char type = '\0';

        if (selection == 0)
            return;
        else if (selection == 1)
            type = 'C';
        else if (selection == 2)
            type = 'T';

        std::cout << std::setfill(' ') << std::setw(3) << std::left << "Row"
                  << " - ";
        std::cout << std::setfill(' ') << std::setw(53) << std::left << "Patient name";
        std::cout << std::setfill(' ') << std::setw(9) << std::left << " OHIP";
        std::cout << std::setfill(' ') << std::setw(6) << std::left << " Tk #";
        std::cout << std::setfill(' ') << std::setw(5) << std::left << " Time";
        std::cout << std::endl;
        std::cout << std::setfill('-') << std::left << std::setw(79) << "";
        std::cout << std::endl;

        int counter = 0;
        for (int i = 0; i < m_lineupSize; i++)
        {

            if (m_lineup[i]->type() != type)
                continue;

            std::cout << std::setfill(' ') << std::setw(3) << std::left << counter + 1 << " - ";
            m_lineup[i]->viewInTable();
            std::cout << std::endl;

            counter++;
        }

        if (counter == 0)
        {
            std::cout << "Line up is empty!"
                      << std::endl;
        }

        std::cout << std::setfill('-') << std::left << std::setw(79) << "";
        std::cout << std::endl;
    }

    const Time PreTriage::getWaitTime(const Patient &p) const
    {
        int count = 0;
        for (int i = 0; i < m_lineupSize; i++)
            if (*m_lineup[i] == p)
                count++;

        Time waitTime = p == 'C' ? m_contagionWaitTime : m_triageWaitTime;
        return Time(waitTime) * count;
    }

    void PreTriage::setAverageWaitTime(const Patient &p)
    {
        Time currentTime;
        currentTime.reset();

        char patientType = p.type();
        int ticketNumber = p.number();

        Time waitTime = patientType == 'C' ? m_contagionWaitTime : m_triageWaitTime;
        Time t = ((currentTime - p.time()) + (waitTime * (ticketNumber - 1))) / ticketNumber;
        
        if (patientType == 'C')
            m_contagionWaitTime = t;
        else
            m_triageWaitTime = t;
    }

    int PreTriage::indexOfFirstInLine(char type) const
    {
        for (int i = 0; i < m_lineupSize; i++)
        {
            if (m_lineup[i]->type() == type)
            {
                return i;
            }
        }
        return -1;
    }

    void PreTriage::removePatientFromLineup(int index)
    {
        removeDynamicElement(m_lineup, index, m_lineupSize);
    }

    void PreTriage::saveData()
    {
        std::ofstream file(m_dataFilename);

        if (!file)
        {
            std::cout << "Failed to create the file!\n";
            return;
        }
        else
        {
            std::cout << "Saving lineup...\n";

            int triageCount = 0;
            int contTestCount = 0;

            file << m_contagionWaitTime << "," << m_triageWaitTime << std::endl;
            for (int i = 0; i < m_lineupSize; i++)
            {
                if (!m_lineup[i])
                    continue;

                char type = m_lineup[i]->type();
                if (type == 'C')
                    contTestCount++;
                else if (type == 'T')
                    triageCount++;

                m_lineup[i]->write(file);
                file << std::endl;
            }
            std::cout << contTestCount << " Contagion Tests and " << triageCount << " Triage records were saved!" << std::endl;
        }
    }
}
