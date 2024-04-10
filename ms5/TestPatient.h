#ifndef SENECA_TESTPATIENT_H_
#define SENECA_TESTPATIENT_H_

#include "Patient.h"

namespace seneca
{

    /// <summary>
    /// Represents a patient undergoing contagion testing.
    /// Inherits from the base Patient class.
    /// </summary>
    class TestPatient : public Patient
    {
    private:
        // Counter to count ticket number of next test patient
        static int nextTestTicket;

    public:
        /// <summary>
        /// Default constructor.
        /// Constructs a TestPatient object and increments the nextTestTicket.
        /// </summary>
        TestPatient();

        /// <summary>
        /// Overrides the type function to return the patient type ('C' for contagion test patient).
        /// </summary>
        /// <returns>The character representing the patient type.</returns>
        virtual char type() const override;

        /// <summary>
        /// Overrides the write function to write patient information to an output stream.
        /// </summary>
        /// <param name="ostr">The output stream to write to.</param>
        /// <returns>The reference to the output stream.</returns>
        virtual std::ostream &write(std::ostream &ostr) const override;

        /// <summary>
        /// Overrides the read function to read patient information from an input stream.
        /// </summary>
        /// <param name="istr">The input stream to read from.</param>
        /// <returns>The reference to the input stream.</returns>
        virtual std::istream &read(std::istream &istr) override;

        /// <summary>
        /// Overrides the << operator to write patient information to an output stream.
        /// </summary>
        /// <param name="os">The output stream to write to.</param>
        /// <param name="patient">The TestPatient object to write.</param>
        /// <returns>The reference to the output stream.</returns>
        friend std::ostream &operator<<(std::ostream &os, const TestPatient &patient);

        /// <summary>
        /// Overrides the >> operator to read patient information from an input stream.
        /// </summary>
        /// <param name="is">The input stream to read from.</param>
        /// <param name="patient">The TestPatient object to read into.</param>
        /// <returns>The reference to the input stream.</returns>
        friend std::istream &operator>>(std::istream &is, TestPatient &patient);
    };

} // namespace seneca

#endif // SENECA_TESTPATIENT_H_
