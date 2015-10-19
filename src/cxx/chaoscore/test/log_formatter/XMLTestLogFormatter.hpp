/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_TEST_LOGFORMATTER_XMLLOGFORMATTER_HPP_
#define CHAOSCORE_TEST_LOGFORMATTER_XMLLOGFORMATTER_HPP_

#include "chaoscore/test/log_formatter/AbstractTestLogFormatter.hpp"

namespace chaos
{
namespace test
{
namespace log_formatter
{

/*!
 * \brief Test Log Formatter that writes logs as XML.
 */
class XMLTestLogFormatter : public AbstractTestLogFormatter
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Creates a new XML Test Log Formatter.
     */
    XMLTestLogFormatter( std::ostream* stream );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void open_log();

    virtual void close_log();

    virtual void open_test(
            const chaos::str::UTF8String& path,
            const chaos::str::UTF8String& id );

    virtual void close_test();

    virtual void report_failure(
            const chaos::str::UTF8String& type,
            const chaos::str::UTF8String& file,
                  chaos::int32            line,
            const chaos::str::UTF8String& message );
};

} // namespace log_formatter
} // namespace test
} // namespace chaos

#endif
