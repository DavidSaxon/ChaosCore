/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_IO_SYS_FILEWRITER_HPP_
#define CHAOSCORE_IO_SYS_FILEWRITER_HPP_

#include "chaoscore/io/sys/FileHandle.hpp"

class ofstream;

namespace chaos
{
namespace io
{
namespace sys
{

/*!
 * \brief Object used to write to new or existing files on the file system.
 *
 * TODO: DOC, example use etc
 *
 * TODO: only supports UTF-8 and binary
 */
class FileWriter : public chaos::io::sys::FileHandle
{
private:

    CHAOS_DISALLOW_COPY_AND_ASSIGN( FileWriter );

public:

    //--------------------------------------------------------------------------
    //                                 ENUMERATOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Flags that can be used to describe how the file handle should be
     *        opened.
     *
     * These flags can be combined together using the logical OR operator.
     */
    enum Flag
    {
        /// No flags specified
        FLAG_NONE   = 0,
        /// Operations are performed in binary mode rather than text mode.
        FLAG_BINARY = 1U << 0,
        /// If the file already exists new data will be written to the end of
        /// of the file. If this flag is not specified writing to existing file
        /// will cause the original contents to be discarded.
        FLAG_APPEND = 1U << 1
    };

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Default constructor.
     *
     * Creates a new unopened FileWriter with no initial path set.
     *
     * \param flags Flags used to described how the FileWriter should be opened.
     *              See chaos::io::sys::FileWriter::Flag for more details.
     * \param encoding The encoding that will be used to write text to the file.
     */
    FileWriter(
            chaos::uint32 flags = FileWriter::FLAG_NONE,
            chaos::str::Encoding encoding = chaos::str::ENCODING_UTF8);

    /*!
     * \brief Open constructor.
     *
     * Creates a new FileWriter and attempts to open it to the given path.
     *
     * \throws chaos::io::sys::InvalidPathError If the path cannot be opened.
     *
     * \param path Path to open this FileWriter to.
     * \param flags Flags used to described how the FileWriter should be opened.
     *              See chaos::io::sys::FileWriter::Flag for more details.
     * \param encoding The encoding that will be used to write text to the file.
     */
    FileWriter(
            const chaos::io::sys::Path& path,
            chaos::uint32 flags = FileWriter::FLAG_NONE,
            chaos::str::Encoding encoding = chaos::str::ENCODING_UTF8);

    /*!
     * \brief Move constructor.
     *
     * \param other The FileWriter to move resources from.
     */
    FileWriter(FileWriter&& other);

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~FileWriter();

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief chaos::str::UTF8String stream operator.
     *
     * Writes the given chaos::str::UTF8String to the file writer's buffer.
     *
     * \throws chaos::ex::StateError If this file handle is not open.
     */
    FileWriter& operator<<( const chaos::str::UTF8String& text );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Opens the writer to the internal path.
     *
     * \throws chaos::ex::StateError If this FileWriter is already open.
     *
     * \throws chaos::io::sys::InvalidPathError If the path cannot be opened.
     */
    virtual void open();

    /*!
     * \brief Sets the path and opens this writer to it.
     *
     * This function is synonymous to:
     *
     * \code
     * my_file_writer.set_path(path);
     * my_file_writer.open();
     * \endcode
     *
     * \throws chaos::ex::StateError If this FileWriter is already open.
     *
     * \throws chaos::io::sys::InvalidPathError If the path cannot be opened.
     */
    virtual void open(const chaos::io::sys::Path& path);

    /*!
     * \brief Closes this file writer and writes data to the file system.
     *
     * Once the file is closed write operations cannot be performed until the
     * file writer is reopened.
     *
     * This function does not need to be explicitly called. When this object is
     * destroyed it will be ensured that data is written and the handle is
     * closed.
     *
     * \throws chaos::ex::StateError If this file handle is not open.
     */
    virtual void close();

    /*!
     * \brief Writes an chaos::str::UTF8String to the internal buffer of this
     *        file writer.
     *
     * The internal buffer is only written to the file system when this file
     * writer is closed.
     *
     * \throws chaos::ex::StateError If this FileWriter is not open.
     */
    void write(const chaos::str::UTF8String& text);

    /*!
     * \brief Convenience function to write text with a following new line
     *        character.
     *
     * See write().
     *
     * \throws chaos::ex::StateError If this file handle is not open.
     */
    void write_line(const chaos::str::UTF8String& text);

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief The output stream being used to write to disk.
     */
    std::ofstream* m_stream;
};

} // namespace sys
} // namespace io
} // namespace chaos

#endif
