#ifndef SENECA_PATIENT_H_
#define SENECA_PATIENT_H_

#include <iostream>
#include "Ticket.h"
#include "IOAble.h"

namespace seneca
{

    /**
     * @brief Abstract base class representing a patient in the healthcare system.
     */
    class Patient : public IOAble
    {
    protected:
        // Dynamically allocated character array for the patient's name
        char *m_name;
        // Patient's OHIP number (9 digits)
        int m_ohipNumber;
        // Patient's ticket
        Ticket m_ticket;

        /// <summary>
        /// Helper function to allocate memory for the patient's name.
        /// </summary>
        /// <param name="name">The name to allocate memory for.</param>
        /// <returns>True on success, false on failure.</returns>
        bool setName(const char *name);

        /// <summary>
        /// Helper function to check validity of OHIP number.
        /// </summary>
        /// <param name="ohipNumber">The OHIP number to validate.</param>
        /// <returns>True if valid, false if not valid.</returns>
        bool isOhipNumberValid(int ohipNumber) const;

    public:
        /// <summary>
        /// Constructor that initializes the patient's ticket with the provided number.
        /// </summary>
        /// <param name="ticketNumber">The ticket number for the patient.</param>
        Patient(int ticketNumber);

        /// <summary>
        /// Copy constructor that performs a deep copy of the patient object.
        /// </summary>
        /// <param name="other">The Patient object to copy from.</param>
        Patient(const Patient &other);

        /// <summary>
        /// Pure virtual destructor to enforce derived classes implement it
        /// </summary>
        /// <param name="number">The ticket number for the patient.</param>
        virtual ~Patient() = 0;

        /// <summary>
        /// Overloaded assignment operator (=) that performs a deep copy of the patient object.
        /// </summary>
        /// <param name="other">The Patient object to copy from.</param>
        /// <returns>A reference to the current Patient object (for chaining).</returns>
        Patient &operator=(const Patient &other);

        /// <summary>
        /// Get ticket time for patient.
        /// </summary>
        /// <returns>Time.</returns>
        Time time() const;

        /// <summary>
        /// Get ticket number for patient.
        /// </summary>
        /// <returns>int</returns>
        int number() const;

        /// <summary>
        /// Overloaded equality operator to compare the patient's type with a character.
        /// </summary>
        /// <param name="other">The character to compare with.</param>
        /// <returns>True if the patient's type is the same as the provided character, false otherwise.</returns>
        bool operator==(char other) const;

        /// <summary>
        /// Overloaded equality operator to compare the patient's type with another patient's type.
        /// </summary>
        /// <param name="other">The other patient to compare with.</param>
        /// <returns>True if the patient types are the same, false otherwise.</returns>
        bool operator==(const Patient &other) const;

        /// <summary>
        /// Pure virtual function that identifies the patient type (implemented in derived classes).
        /// </summary>
        /// <returns>A character representing the patient type (e.g., 'T' for Triage, 'C' for Contagion test).</returns>
        virtual char type() const = 0;

        /// <summary>
        /// Sets the patient's arrival time to the current time.
        /// </summary>
        void setArrivalTime();

        /// <summary>
        /// Cast operator to boolean (checks if name and OHIP are valid).
        /// </summary>
        /// <returns>True if name and OHIP are valid, false otherwise.</returns>
        operator bool() const;

        /// <summary>
        /// Cast operator to const char* (returns address of name).
        /// </summary>
        /// <returns>The address of the patient's name (const char*).</returns>
        operator const char *() const;

        /// <summary>
        /// Overloaded insertion operator (<<) to write patient information to ostream.
        /// </summary>
        /// <param name="ostr">The output stream to write to.</param>
        /// <param name="patient">The patient object to write.</param>
        /// <returns>A reference to the output stream for chaining.</returns>
        friend std::ostream &operator<<(std::ostream &ostr, const Patient &patient);

        /// <summary>
        /// Overloaded extraction operator (>>) to read patient information from istream.
        /// </summary>
        /// <param name="istr">The input stream to read from.</param>
        /// <param name="patient">The patient object to read into.</param>
        /// <returns>A reference to the input stream for chaining.</returns>
        friend std::istream &operator>>(std::istream &istr, Patient &patient);

        /// <summary>
        /// Reads patient information from istream (different formats for cin and file).
        /// </summary>
        /// <param name="istr">The input stream to read from.</param>
        /// <returns>A reference to the input stream for chaining.</returns>
        std::istream &read(std::istream &istr);

        /// <summary>
        /// Writes patient information to ostream (different formats for cout, clog, and file).
        /// </summary>
        /// <param name="ostr">The output stream to write to.</param>
        /// <returns>A reference to the output stream for chaining.</returns>
        std::ostream &write(std::ostream &ostr) const;
    };

}

#endif
