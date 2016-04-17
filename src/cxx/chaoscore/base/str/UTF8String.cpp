#include <algorithm>
#include <cstddef>
#include <cstring>
#include <sstream>

#include "chaoscore/base/BaseExceptions.hpp"
#include "chaoscore/base/data/ByteOperations.hpp"
#include "chaoscore/base/str/UTF8String.hpp"
#include "chaoscore/base/str/UnicodeOperations.hpp"

namespace chaos
{
namespace str
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

UTF8String::UTF8String()
    :
    m_data       ( nullptr ),
    m_data_length( 0 ),
    m_length     ( 0 )
{
    // assign the empty string
    assign_internal( "", 0 );
}

UTF8String::UTF8String( const char* data )
    :
    m_data       ( nullptr ),
    m_data_length( 0 ),
    m_length     ( 0 )
{
    // assign the data
    assign_internal( data );
}

UTF8String::UTF8String( const char* data, std::size_t length )
    :
    m_data       ( nullptr ),
    m_data_length( 0 ),
    m_length     ( 0 )
{
    // assign the data
    assign_internal( data, length );
}

UTF8String::UTF8String( const UTF8String& other )
    :
    m_data       ( nullptr ),
    m_data_length( 0 ),
    m_length     ( 0 )
{
    // assign the data with the known length
   assign_internal( other.m_data, other.m_data_length );
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

UTF8String::~UTF8String()
{
    // ensure we delete the internal data buffer
    delete[] m_data;
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

const UTF8String& UTF8String::operator=( const UTF8String& other )
{
    assign( other );
    return *this;
}

bool UTF8String::operator==( const UTF8String& other ) const
{
    return strcmp(
            reinterpret_cast< const char* >( m_data ),
            reinterpret_cast< const char* >( other.m_data )
    ) == 0;
}

bool UTF8String::operator!=( const UTF8String& other ) const
{
    return !( ( *this ) == other );
}

bool UTF8String::operator<( const UTF8String& other ) const
{
    // iterate over each code point until we find one that is less than the
    // other
    for ( std::size_t i = 0;
          i < std::min( get_length(), other.get_length() );
          ++i )
    {
        // do a straight comparison on each code point until we find a character
        // that is less than
        chaos::uint32 a = get_code_point( i );
        chaos::uint32 b = other.get_code_point( i );
        if ( a < b )
        {
            return true;
        }
        if ( b < a )
        {
            return false;
        }
    }
    // is this string shorter?
    return get_length() < other.get_length();
}

UTF8String UTF8String::operator+( const UTF8String& other ) const
{
    return UTF8String( *this ).concatenate( other );
}

UTF8String& UTF8String::operator+=( const UTF8String& other )
{
    return this->concatenate( other );
}

UTF8String UTF8String::operator*( chaos::uint32 count ) const
{
    return UTF8String( *this ).repeat( count );
}

UTF8String& UTF8String::operator*=( chaos::uint32 count )
{
    return this->repeat( count );
}

UTF8String& UTF8String::operator<<( const UTF8String& other )
{
    return this->concatenate( other );
}

UTF8String& UTF8String::operator<<( const char* other )
{
    return this->concatenate( UTF8String( other ) );
}

UTF8String& UTF8String::operator<<( const std::string& other )
{
    return this->concatenate( UTF8String( other.c_str() ) );
}

UTF8String& UTF8String::operator<<( bool other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( char other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

#ifdef CHAOS_OS_WINDOWS

UTF8String& UTF8String::operator<<( unsigned long other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

#endif

UTF8String& UTF8String::operator<<( chaos::int8 other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( chaos::uint8 other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( chaos::int16 other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( chaos::uint16 other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( chaos::int32 other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( chaos::uint32 other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( chaos::int64 other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( chaos::uint64 other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( float other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void UTF8String::assign( const char* data )
{
    assign_internal( data );
}

void UTF8String::assign( const char* data, std::size_t length )
{
    assign_internal( data, length );
}

void UTF8String::assign( const UTF8String& other )
{
    assign_internal( other.m_data, other.m_data_length );
}

UTF8String& UTF8String::concatenate( const UTF8String& other )
{
    // calculate the new size of the data (but remove the first string's NULL
    // terminator)
    std::size_t new_length = ( m_data_length - 1 ) + other.m_data_length;
    // allocate a new array to hold the increase data size, ignoring one of the
    // NULL terminators
    char* new_data = new char[ new_length ];
    // copy over the data from the strings
    memcpy( new_data, m_data, m_data_length - 1 );
    memcpy(
            new_data + ( m_data_length - 1 ),
            other.m_data,
            other.m_data_length
    );
    // finally assign and return
    assign_internal( new_data, new_length );
    return *this;
}

UTF8String& UTF8String::repeat( chaos::uint32 count )
{
    std::size_t c_length = m_data_length - 1;
    // calculate the new length
    std::size_t new_length = ( c_length * count ) + 1;
    // allocate a new block of data
    char* new_data = new char[ new_length ];
    // write new data
    for( std::size_t i = 0; i < count; ++i )
    {
        memcpy(
                new_data + ( c_length * i ),
                m_data,
                m_data_length - 1
        );
    }
    // add the null terminator
    new_data[ new_length - 1 ] = '\0';
    // finally assign and return
    assign_internal( new_data, new_length );
    return *this;
}

bool UTF8String::starts_with( const UTF8String& substring ) const
{
    // the substring must be shorter than the actual string
    if ( substring.m_length > m_length )
    {
        return false;
    }
    // check until we find a mismatch
    for ( std::size_t i = 0; i < substring.m_length; ++i )
    {
        if ( substring.get_symbol( i ) != get_symbol( i ) )
        {
            return false;
        }
    }

    // no mismatch
    return true;
}

bool UTF8String::ends_with( const UTF8String& substring ) const
{
    // the substring must be shorter than the actual string
    if ( substring.m_length > m_length )
    {
        return false;
    }
    // check until we find a mismatch
    std::size_t diff = m_length - substring.m_length;
    for ( std::size_t i = substring.m_length; i > 0; --i )
    {
        if ( substring.get_symbol( i - 1 ) != get_symbol( diff + ( i - 1 ) ) )
        {
            return false;
        }
    }

    // no mismatch
    return true;
}

std::size_t UTF8String::find_first( const UTF8String& substring ) const
{
    // the substring must be shorter than the actual string
    if ( substring.m_length > m_length )
    {
        return chaos::str::npos;
    }
    // check against each character
    for( std::size_t i = 0; i < m_length - ( substring.m_length - 1 ); ++i )
    {
        // check that each symbol matches
        bool match = true;
        for ( std::size_t j = 0; j < substring.m_length; ++j )
        {
            if ( substring.get_symbol_value( j ) != get_symbol_value( i + j ) )
            {

                match = false;
                break;
            }
        }
        if ( match )
        {
            return i;
        }
    }
    return chaos::str::npos;
}

std::size_t UTF8String::find_last( const UTF8String& substring ) const
{
    // the substring must be shorter than the actual string
    if ( substring.m_length > m_length )
    {
        return chaos::str::npos;
    }
    // check against each character
    for( std::size_t i = m_length - substring.m_length;
         i != chaos::str::npos;
         --i )
    {
        // check that each symbol matches
        bool match = true;
        for ( std::size_t j = 0; j < substring.m_length; ++j )
        {
            if ( substring.get_symbol( j ) != get_symbol( i + j ) )
            {
                match = false;
                break;
            }
        }
        if ( match )
        {
            return i;
        }
    }
    return chaos::str::npos;
}

std::vector< UTF8String > UTF8String::split(
        const UTF8String& delimiter ) const
{
    // check the delimiter
    if ( delimiter.is_empty() )
    {
        throw chaos::ex::ValueError( "Provided delimiter is empty." );
    }

    // create the vector to return
    std::vector< UTF8String > elements;

    UTF8String element;
    for( std::size_t i = 0; i < m_length; )
    {
        // are we looking at the delimiter
        if ( substring( i, delimiter.get_length() ) == delimiter )
        {
            // add what we have so far
            elements.push_back( element );
            // clear element
            element = "";
            // increment past the delimiter
            i += delimiter.get_length();
        }
        else
        {
            element += get_symbol( i );
            ++i;
        }
    }
    // add the final element
    elements.push_back( element );


    return elements;
}

void UTF8String::remove_duplicates( const UTF8String& substring )
{
    // do nothing if an empty substring has been provided
    if ( substring.is_empty() )
    {
        return;
    }

    // TODO this can be optmised

    // input and output strings
    UTF8String input( *this );
    UTF8String output;

    std::size_t i = input.find_first( substring );
    while( i != chaos::str::npos )
    {
        // add up to and including the substring
        output << input.substring(
                0,
                i + substring.get_length()
        );
        input = input.substring(
                i + substring.get_length(),
                input.get_length()
        );
        // filter away the rest of the duplicates
        while( input.starts_with( substring ) )
        {
            input = input.substring(
                    substring.get_length(),
                    input.get_length()
            );
        }
        i = input.find_first( substring );
    }
    // add what's left of the input
    output << input;

    assign( output );
}

bool UTF8String::is_int() const
{
    // iterate over each code point and ensure that it's a digit
    for ( std::size_t i = 0; i < m_length; ++i )
    {
        chaos::uint32 code_point = get_code_point( i );

        // the first symbol is allowed to be '-'
        if ( i == 0                                  &&
            get_symbol( i ) != "-"                   &&
            !chaos::str::is_digit( code_point )    )
        {
            return false;
        }
        // every other character must be a digit
        else if ( i != 0 && !chaos::str::is_digit( code_point ) )
        {
            return false;
        }
    }
    // valid int
    return !is_empty();
}

bool UTF8String::is_uint() const
{
    // iterate of each code point and ensure that it's a digit
    for ( std::size_t i = 0; i < m_length; ++i )
    {
        if ( !chaos::str::is_digit( get_symbol_value( i ) ) )
        {
            // not a digit
            return false;
        }
    }
    // valid unsigned int
    return !is_empty();
}

bool UTF8String::is_float() const
{
    bool point_found = false;
    // iterate of each code point
    for ( std::size_t i = 0; i < m_length; ++i )
    {
        chaos::uint32 code_point = get_symbol_value( i );

        if ( !chaos::str::is_digit( code_point ) )
        {
            if ( i == 0 && get_symbol( i ) == "-" )
            {
                continue;
            }
            if ( get_symbol( i ) == "." && !point_found )
            {
                point_found = true;
                continue;
            }
            return false;
        }
    }
    return !is_empty();
}

UTF8String UTF8String::substring( std::size_t start, std::size_t end ) const
{
    // return empty if the index is the length of this string
    if ( start == get_length() )
    {
        return UTF8String();
    }

    // is the index valid
    check_symbol_index( start );

    // TODO: can this be optimised to copy raw data array?

    UTF8String result;
    for ( std::size_t i = start;
          i < std::min( get_length(),  start + end );
          ++i )
    {
        result += get_symbol( i );
    }

    return result;
}

std::string UTF8String::to_std_string() const
{
    return std::string(
            reinterpret_cast< char* >( m_data ),
            m_data_length - 1
    );
}

bool UTF8String::to_bool() const
{
    // is the conversion valid?
    if ( !is_int() )
    {
        UTF8String error_message;
        error_message << "Cannot convert: \'" << *this << " to bool as it is "
                      << "not valid.";
        throw chaos::ex::ConversionDataError( error_message );
    }
    // do conversion and return
    for ( std::size_t i = 0; i < get_length(); ++i )
    {
        if ( get_symbol( i ) != "0" )
        {
            return true;
        }
    }
    return false;
}

chaos::int32 UTF8String::to_int32() const
{
    // is the conversion valid?
    if ( !is_int() )
    {
        UTF8String error_message;
        error_message << "Cannot convert: \'" << *this << " to int32 as it is "
                      << "not valid.";
        throw chaos::ex::ConversionDataError( error_message );
    }
    // do and return conversion
    return static_cast< chaos::int32 >( std::strtol( get_raw(), NULL, 0 ) );
}

chaos::uint32 UTF8String::to_uint32() const
{
    // is the conversion valid?
    if ( !is_uint() )
    {
        UTF8String error_message;
        error_message << "Cannot convert: \'" << *this << " to uint32 as it is "
                      << "not valid.";
        throw chaos::ex::ConversionDataError( error_message );
    }
    // do and return conversion
    return static_cast< chaos::uint32 >( strtoul( get_raw(), NULL, 0 ) );
}

chaos::int64 UTF8String::to_int64() const
{
    // is the conversion valid?
    if ( !is_int() )
    {
        UTF8String error_message;
        error_message << "Cannot convert: \'" << *this << " to int64 as it is "
                      << "not valid.";
        throw chaos::ex::ConversionDataError( error_message );
    }
    // do and return conversion
    return static_cast< chaos::int64 >( std::strtol( get_raw(), NULL, 0 ) );
}

chaos::int64 UTF8String::to_uint64() const
{
    // is the conversion valid?
    if ( !is_uint() )
    {
        UTF8String error_message;
        error_message << "Cannot convert: \'" << *this << " to uint64 as it is "
                      << "not valid.";
        throw chaos::ex::ConversionDataError( error_message );
    }
    // do and return conversion
    return static_cast< chaos::uint64 >(
            std::strtoul( get_raw(), NULL, 0 ) );
}

//----------------------------------ACCESSORS-----------------------------------

std::size_t UTF8String::get_length() const
{
    return m_length;
}

bool UTF8String::is_empty() const
{
    // less than once since non-empty data will contain a NULL terminator
    return m_data_length <= 1;
}

UTF8String UTF8String::get_symbol( std::size_t index ) const
{
    // is the index valid
    check_symbol_index( index );

    // get the byte position
    std::size_t byte_index = get_byte_index_for_symbol_index( index );
    // get the width of the byte
    std::size_t byte_width = get_byte_width( byte_index );

    return UTF8String( &m_data[ byte_index ], byte_width );
}

chaos::uint32 UTF8String::get_symbol_value( std::size_t index ) const
{
    // is the index valid?
    check_symbol_index( index );

    // get the bytes that make up the symbol
    std::size_t byte_index = get_byte_index_for_symbol_index( index );
    std::size_t byte_width = get_byte_width( byte_index );

    return chaos::data::bytes_to_uint32( &m_data[ byte_index ], byte_width );
}

chaos::uint32 UTF8String::get_code_point( std::size_t index ) const
{
    // is the index valid?
    check_symbol_index( index );

    // get the width so we know how to convert
    std::size_t width = get_symbol_width( index );
    chaos::uint32 value = get_symbol_value( index );

    if ( width == 1 )
    {
        return value;
    }
    else if ( width == 2 )
    {
        return ( ( value << 6 ) & 0x00007C0 ) |
               ( ( value >> 8 ) & 0x0000003F );
    }
    else if ( width == 3 )
    {
        return ( ( value << 12 ) & 0x0000F000 ) |
               ( ( value >> 2  ) & 0x00000FC0 ) |
               ( ( value >> 16 ) & 0x0000003F );
    }
    else
    {
        return ( ( value << 18 ) & 0x001C0000 ) |
               ( ( value << 4  ) & 0x0003F000 ) |
               ( ( value >> 10 ) & 0x00000FC0 ) |
               ( ( value >> 24 ) & 0x0000003F );
    }
}

std::size_t UTF8String::get_byte_index_for_symbol_index(
        std::size_t symbol_index ) const
{
    // is the index valid?
    check_symbol_index( symbol_index );

    // TODO: can this be optimized?
    std::size_t current_index = 0;
    for ( std::size_t i = 0; i < m_data_length - 1; )
    {
        if ( current_index == symbol_index )
        {
            return i;
        }

        ++current_index;
        // increase by byte width
        i += get_byte_width( i );
    }

    // something broke
    return chaos::str::npos;
}

std::size_t UTF8String::get_symbol_width( std::size_t index ) const
{
    // is the index valid
    check_symbol_index( index );

    std::size_t byte_index = get_byte_index_for_symbol_index( index );
    return get_byte_width( byte_index );
}

const char* UTF8String::get_raw() const
{
    return m_data;
}

std::size_t UTF8String::get_byte_length() const
{
    return m_data_length;
}

std::size_t UTF8String::get_symbol_index_for_byte_index(
        std::size_t byte_index ) const
{
    // is the index valid?
    check_byte_index( byte_index );

    std::size_t current_index = 0;
    for ( std::size_t i = 0; i < m_data_length - 1; )
    {
        std::size_t next = i + get_byte_width( i );

        if ( byte_index >= i && byte_index < next )
        {
            return current_index;
        }

        ++current_index;
        // increase by byte width
        i = next;
    }

    // something broke
    return chaos::str::npos;
}

std::size_t UTF8String::get_byte_width( std::size_t byte_index ) const
{
    // is the index valid?
    check_byte_index( byte_index );

    // single byte character
    if ( ( m_data[ byte_index ] & 0x80 ) == 0 )
    {
        return 1;
    }
    // double byte character
    else if ( ( m_data[ byte_index ] & 0xE0 ) == 0xC0 )
    {
        return 2;
    }
    // triple byte character
    else if ( ( m_data[ byte_index ] & 0xF0 ) == 0xE0 )
    {
        return 3;
    }
    // quad byte character
    else
    {
        return 4;
    }
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void UTF8String::assign_internal(
        const char* data,
        std::size_t existing_length )
{
    // if there is already content in the internal buffer delete it
    delete[] m_data;

    // cast the incoming data to a cstring
    // const char* data = static_cast< const char* >( data );

    // get number of bytes in the data
    bool is_null_terminated = true;
    if ( existing_length == chaos::str::npos )
    {
        // the length includes the NULL terminator
        existing_length = strlen( data ) + 1;
        m_data_length = existing_length;
    }
    else if ( existing_length > 0 && data[ existing_length - 1 ] == '\0' )
    {
        // the length includes a NULL terminator
        is_null_terminated = true;
        m_data_length = existing_length;
    }
    else
    {
        // the length doesn't include a NULL terminator
        is_null_terminated = false;
        m_data_length = existing_length + 1;
    }

    // allocate storage for the internal data buffer
    m_data = new char[ m_data_length ];
    // copy data to internal array
    memcpy( m_data, data, existing_length );
    // should a NULL terminator be added to the end?
    if ( !is_null_terminated )
    {
        m_data[ m_data_length - 1 ] = '\0';
    }

    // to calculate the number of utf-8 symbols in the string
    // TODO: could be optimised?
    m_length = 0;
    for ( std::size_t i = 0; i < m_data_length - 1; )
    {
        ++m_length;
        // increase index by byte width
        i += get_byte_width( i );
    }
}

void UTF8String::check_symbol_index( std::size_t index ) const
{
    if ( index >= m_length )
    {
        UTF8String error_message;
        error_message << "Provided index: " << index << " is greater or equal "
                      << "to the number of symbols in the string: " << m_length;
        throw chaos::ex::IndexOutOfBoundsError( error_message );
    }
}

void UTF8String::check_byte_index( std::size_t index ) const
{
    if ( index >= m_data_length )
    {
        UTF8String error_message;
        error_message << "Provided index: " << index << " is greater or equal "
                      << "to the number of bytes in the string: "
                      << m_data_length;
        throw chaos::ex::IndexOutOfBoundsError( error_message );
    }
}

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

std::ostream& operator<<( std::ostream& stream, const UTF8String& s )
{
    // TODO: proper printing
    stream << s.get_raw();
    return stream;
}

} // namespace str
} // namespace chaos