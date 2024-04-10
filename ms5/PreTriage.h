#ifndef SENECA_PRETRIAGE_H
#define SENECA_PRETRIAGE_H

#include "Patient.h"
#include "Time.h"
#include "Menu.h"

namespace seneca
{

    const int MAX_PATIENTS = 100;

    class PreTriage
    {

        // wait time for TriagePatient
        Time m_triageWaitTime;

        // wait time for TestPatient
        Time m_contagionWaitTime;

        // counter to count total lineups
        int m_lineupSize = 0;

        // array to hold lineup
        Patient *m_lineup[MAX_PATIENTS];

        // variable to hold filename
        char *m_dataFilename = nullptr;

        /// <summary>
        /// Loads patient data from a file into the PreTriage system.
        /// </summary>
        void loadData();

        /// <summary>
        /// Saves patient lineup data to a file.
        /// This method saves the current patient lineup data to a file specified by the data filename attribute.
        /// </summary>
        void saveData();

        /// <summary>
        /// Displays the current lineup of patients.
        /// This method displays the current lineup of patients, categorized as Contagion or Triage patients.
        /// </summary>
        void lineup();

        /// <summary>
        /// Admits a patient from the lineup for treatment.
        /// This method prompts the user to select a lineup (Contagion or Triage) and admits that patient from the lineup for treatment.
        /// </summary>
        void admitPatient();

        /// <summary>
        /// Registers a new patient into the lineup.
        /// This method prompts the user to enter information for a new patient and adds them to the selected lineup (Contagion or Triage).
        /// </summary>
        void registerPatient();

        /// <summary>
        /// Removes a patient from the lineup at the specified index.
        /// This method removes a patient from the lineup at the specified index.
        /// </summary>
        /// <param name="index">The index of the patient to remove from the lineup.</param>
        void removePatientFromLineup(int index);

        /// <summary>
        /// Modifies and sets the average wait time for a patient after admission.
        /// This method adjusts the average wait time for the patient category (Contagion or Triage).
        /// </summary>
        /// <param name="patient">The patient whose wait time is to be modified.</param>
        void setAverageWaitTime(const Patient &p);

        /// <summary>
        /// Gets the total estimated wait time for a specific type of patient.
        /// </summary>
        /// <param name="patient">The type of patient.</param>
        /// <returns>The total estimated wait time for the specified type of patient.</returns>
        const Time getWaitTime(const Patient &p) const;

        /// <summary>
        /// Finds the index of the first patient in line that matches a specified type.
        /// </summary>
        /// <param name="type">The type of patient (C for Contagion, T for Triage).</param>
        /// <returns>The index of the first patient in line that matches the specified type, or -1 if no matching patient is found.</returns>
        int indexOfFirstInLine(char type) const;

    public:
        /// <summary>
        /// Constructor for PreTriage class.
        /// This constructor initializes the PreTriage object and load data from the file.
        /// It also initializes the wait times for contagion tests and triage from file or sets to 15 and 5.
        /// </summary>
        /// <param name="dataFilename">The name of the data file to load patients from.</param>
        PreTriage(const char *dataFilename);

        /// <summary>
        /// Destructor for PreTriage class.
        /// </summary>
        ~PreTriage();

        /// <summary>
        /// Runs the PreTriage application.
        /// Shows the main menu and handles rest of the application.
        /// </summary>
        void run(void);
    };

}

#endif
