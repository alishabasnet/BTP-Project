#ifndef SENECA_IOABLE_H_
#define SENECA_IOABLE_H_

#include <iostream>

namespace seneca
{

    /**
     * @brief Interface for classes that can be read from and written to streams.
     */
    class IOAble
    {
    public:
        /// <summary>
        /// Overloaded insertion operator (<<) to write the object to the specified output stream.
        /// </summary>
        /// <param name="ostr">The output stream to write to.</param>
        /// <param name="obj">The object to write.</param>
        /// <returns>A reference to the output stream for chaining.</returns>
        friend std::ostream &operator<<(std::ostream &ostr, const IOAble &obj)
        {
            return obj.write(ostr);
        }

        /// <summary>
        /// Overloaded extraction operator (>>) to read data from the specified input stream.
        /// </summary>
        /// <param name="istr">The input stream to read from.</param>
        /// <param name="obj">The object to write.</param>
        /// <returns>A reference to the input stream for chaining.</returns>
        friend std::istream &operator>>(std::istream &istr, IOAble &obj)
        {
            return obj.read(istr);
        }

    protected:
        /// <summary>
        /// Pure virtual function that derived classes must implement to define their specific write behavior.
        /// </summary>
        /// <param name="ostr">The output stream to write to.</param>
        /// <returns>A reference to the output stream for chaining.</returns>
        virtual std::ostream &write(std::ostream &ostr) const = 0;

        /// <summary>
        /// Pure virtual function that derived classes must implement to define their specific read behavior.
        /// </summary>
        /// <param name="istr">The input stream to read from.</param>
        /// <returns>A reference to the input stream for chaining.</returns>
        virtual std::istream &read(std::istream &istr) = 0;

        // Rest of the code...
    };

} // namespace seneca

#endif // SENECA_IOABLE_H_
