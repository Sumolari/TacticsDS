#ifndef FMAW_IO_H
#define FMAW_IO_H

#include <cstdio>

namespace FMAW {

namespace IO {

/**
 * Prepares filesystem.
 */
void init();

/**
 * Opens the file whose name is specified in the parameter filename and
 * associates it with a stream that can be identified in future operations by
 * the FILE pointer returned.
 *
 * The operations that are allowed on the stream and how these are performed are
 * defined by the mode parameter.
 *
 * The returned pointer can be disassociated from the file by calling fclose.
 * All opened files are automatically closed on normal program termination.
 *
 * @param  filename C string containing the name of the file to be opened.
 *                  Its value shall follow the file name specifications of the
 *                  running environment and can include a path (if supported by
 *                  the system).

 * @param  mode     C string containing a file access mode. It can be:
 *                  "r" read: Open file for input operations. The file must
 *                            exist.
 *                  "w" write: Create an empty file for output operations. If a
 *                             file with the same name already exists, its
 *                             contents are discarded and the file is treated as
 *                             a new empty file.
 *                  "a" append: Open file for output at the end of a file.
 *                              Output operations always write data at the end
 *                              of the file, expanding it. Repositioning
 *                              operations (fseek, fsetpos, rewind) are ignored.
 *                              The file is created if it does not exist.
 *                  "r+" read/update: Open a file for update (both for input
 *                                    and output). The file must exist.
 *                  "w+" write/update: Create an empty file and open it for
 *                                     update (both for input and output). If a
 *                                     file with the same name already exists
 *                                     its contents are discarded and the file
 *                                     is treated as a new empty file.
 *                  "a+" append/update: Open a file for update (both for input
 *                                      and output) with all output operations
 *                                      writing data at the end of the file.
 * @return          If the file is successfully opened, the function returns a
 *                  pointer to a FILE object that can be used to identify the
 *                  stream on future operations.
 *                  Otherwise, a null pointer is returned.
 */
FILE *fopen(const char *filename, const char *mode);

/**
 * Closes the file associated with the stream and disassociates it.
 *
 * All internal buffers associated with the stream are disassociated from it and
 * flushed: the content of any unwritten output buffer is written and the
 * content of any unread input buffer is discarded.
 *
 * Even if the call fails, the stream passed as parameter will no longer be
 * associated with the file nor its buffers.
 *
 * @param  stream Pointer to a FILE object that specifies the stream to be
 *                closed.
 * @return        If the stream is successfully closed, a zero value is returned.
 *                On failure, EOF is returned.
 */
int fclose(FILE *stream);

/**
 * Writes the C string pointed by format to the stream. If format includes
 * format specifiers (subsequences beginning with %), the additional arguments
 * following format are formatted and inserted in the resulting string replacing
 * their respective specifiers.
 *
 * After the format parameter, the function expects at least as many additional
 * arguments as specified by format.
 *
 * @param  stream Pointer to a FILE object that identifies an output stream.
 * @param  format C string that contains the text to be written to the stream.
 *                Depending on the format string, the function may expect a s
 *                equence of additional arguments, each containing a value to be
 *                used to replace a format specifier in the format string (or a
 *                pointer to a storage location, for n).
 *                There should be at least as many of these arguments as the
 *                number of values specified in the format specifiers.
 *                Additional arguments are ignored by the function.
 * @return        On success, the total number of characters written is returned.
 *                If a writing error occurs, the error indicator (ferror) is set
 *                and a negative number is returned.
 *                If a multibyte character encoding error occurs while writing
 *                wide characters, errno is set to EILSEQ and a negative number
 *                is returned.
 */
int fprintf(FILE *stream, const char *format, ...);

/**
 * Reads data from the stream and stores them according to the parameter format
 * into the locations pointed by the additional arguments.
 *
 * The additional arguments should point to already allocated objects of the
 * type specified by their corresponding format specifier within the format
 * string.
 *
 * @param  stream Pointer to a FILE object that identifies the input stream to
 *                read data from.
 * @param  format C string that contains a sequence of characters that control
 *                how characters extracted from the stream are treated.
 * @return        On success, the function returns the number of items of the
 *                argument list successfully filled. This count can match the
 *                expected number of items or be less (even zero) due to a
 *                matching failure, a reading error, or the reach of the
 *                end-of-file.
 *                If a reading error happens or the end-of-file is reached while
 *                reading, the proper indicator is set (feof or ferror). And, if
 *                either happens before any data could be successfully read, EOF
 *                is returned.
 *                If an encoding error happens interpreting wide characters, the
 *                function sets errno to EILSEQ.
 */
int fscanf(FILE *stream, const char *format, ...);

/**
 * If the given stream was open for writing (or if it was open for updating and
 * the last i/o operation was an output operation) any unwritten data in its
 * output buffer is written to the file.
 *
 * If stream is a null pointer, all such streams are flushed.
 *
 * In all other cases, the behavior depends on the specific library
 * implementation. In some implementations, flushing a stream open for
 * reading causes its input buffer to be cleared (but this is not portable
 * expected behavior).
 *
 * The stream remains open after this call.
 *
 * When a file is closed, either because of a call to fclose or because the
 * program terminates, all the buffers associated with it are automatically
 * flushed.
 *
 * @param  stream Pointer to a FILE object that specifies a buffered stream.
 * @return        A zero value indicates success.
 *                If an error occurs, EOF is returned and the error indicator
 *                is set (see ferror).
 */
int fflush(FILE *stream);

}

}

#endif