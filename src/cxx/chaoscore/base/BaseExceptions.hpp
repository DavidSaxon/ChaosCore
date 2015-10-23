/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_BASE_EXCEPTIONS_HPP_
#define CHAOSCORE_BASE_EXCEPTIONS_HPP_

#include <exception>

#include "chaoscore/base/string/UTF8String.hpp"

namespace chaos
{

/*!
 * \brief Base generic exceptions defined by ChaosCore.
 */
namespace ex
{

//------------------------------------------------------------------------------
//                                CHAOS EXCEPTION
//------------------------------------------------------------------------------

/*!
 * \brief Abstract base class that all ChaosCore Exceptions extend from.
 *
 * This class directly inherits from std::exception.
 */
class ChaosException : public std::exception
{
public:

    //--------------------------------DESTRUCTOR--------------------------------

    virtual ~ChaosException() throw()
    {
    }

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    /*!
     * \return The reason for the exception.
     */
    virtual const char* what() const throw()
    {
        return m_Message.get_cstring();
    }

    /*!
     * \return The reason for the exception.
     */
    const chaos::str::UTF8String& get_message() const
    {
        return m_Message;
    }

protected:

    //-------------------------------CONSTRUCTOR--------------------------------

    /*!
     * \brief Super constructor for objects derived from ChaosException.
     *
     * \param message A message decribing the reason for the exception.
     */
    ChaosException( const chaos::str::UTF8String& message )
        :
        m_Message ( message )
    {
    }

private:

    //----------------------------PRIVATE ATTRIBUTES----------------------------

    // The message explaining the reason for the exception
    chaos::str::UTF8String m_Message;
};


//------------------------------------------------------------------------------
//                           INDEX OUT OF BOUNDS ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns that an invalid value has been supplied.
 */
class ValueError : public ChaosException
{
public:

    ValueError( const chaos::str::UTF8String& message )
        :
        ChaosException( message )
    {
    }
};

/*!
 * \brief Warns that an index has been requested outside of the allowed bounds.
 */
class IndexOutOfBoundsError : public ChaosException
{
public:

    IndexOutOfBoundsError( const chaos::str::UTF8String& message )
        :
        ChaosException( message )
    {
    }
};


//------------------------------------------------------------------------------
//                             CONVERSION DATA ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns that the provided data for a type conversion was bad or invalid.
 */
class ConversionDataError : public ChaosException
{
public:

    ConversionDataError( const chaos::str::UTF8String& message )
        :
        ChaosException( message )
    {
    }
};

} // namespace ex
} // namespace chaos

#endif
