#ifndef SENECA_TRIAGEPATIENT_H_
#define SENECA_TRIAGEPATIENT_H_

#include "Patient.h"
#include <cstring>
#include <iostream>

namespace seneca
{

    class TriagePatient : public Patient
    {
    private:
        // Character pointer to hold the symptoms of the patient
        char *m_symptoms;
        // Counter to count ticket number of next triage patient
        static int nextTriageTicket;

    public:
        /// <summary>
        /// Default constructor for TriagePatient.
        /// </summary>
        TriagePatient();

        /// <summary>
        /// Copy constructor for TriagePatient.
        /// </summary>
        /// <param name="other">The other TriagePatient object to copy from.</param>
        TriagePatient(const TriagePatient &other);

        /// <summary>
        /// Destructor for TriagePatient.
        /// </summary>
        ~TriagePatient();

        /// <summary>
        /// Assignment operator overload for TriagePatient.
        /// </summary>
        /// <param name="other">The other TriagePatient object to assign from.</param>
        /// <returns>A reference to the assigned TriagePatient object.</returns>
        TriagePatient &operator=(const TriagePatient &other);

        /// <summary>
        /// Returns the type of the patient ('T' for TriagePatient).
        /// </summary>
        /// <returns>The character representing the type of the patient.</returns>
        char type() const override;

        /// <summary>
        /// Writes the patient's information to the output stream.
        /// </summary>
        /// <param name="ostr">The output stream to write to.</param>
        /// <returns>A reference to the output stream.</returns>
        std::ostream &write(std::ostream &ostr) const override;

        /// <summary>
        /// Reads the patient's information from the input stream.
        /// </summary>
        /// <param name="istr">The input stream to read from.</param>
        /// <returns>A reference to the input stream.</returns>
        std::istream &read(std::istream &istr) override;

        /// <summary>
        /// Friend function to overload the input stream extraction operator.
        /// </summary>
        /// <param name="is">The input stream to read from.</param>
        /// <param name="patient">The TriagePatient object to populate.</param>
        /// <returns>A reference to the input stream.</returns>
        friend std::istream &operator>>(std::istream &is, TriagePatient &patient);

        /// <summary>
        /// Friend function to overload the output stream insertion operator.
        /// </summary>
        /// <param name="os">The output stream to write to.</param>
        /// <param name="patient">The TriagePatient object to write.</param>
        /// <returns>A reference to the output stream.</returns>
        friend std::ostream &operator<<(std::ostream &os, const TriagePatient &patient);
    };

} // namespace seneca

#endif // SENECA_TRIAGEPATIENT_H_
