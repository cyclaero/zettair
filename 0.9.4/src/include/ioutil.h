/* ioutil.h declares various utility io functions.
 *
 * written wew 2006-06-20, by abstracting code from elsewhere.
 */

#ifndef IOUTIL_H
#define IOUTIL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function to atomically perform a read.
 *
 * The normal read(2) function can return after reading
 * less than SIZE bytes, if EOF occurs first, or because FD 
 * points to a pipe or socket and less than SIZE bytes were
 * currently available, or because a signal occurred during
 * reading.  This function however will 
 * not return successfully until it has read exactly SIZE 
 * bytes.  If EOF occurs before SIZE bytes is read,
 * this counts as an error.
 *
 * XXX If FD is of a type that supports non-blocking operation
 * (i.e. not a regular file), and O_NONBLOCK is set on FD,
 * then if at any time there is no data available for reading,
 * this function will return an ERROR.  For this reason (and
 * because in any case it doesn't make much sense) you should
 * NOT use this function with non-blocking file descriptors.
 *
 * Return: SIZE on success, or -1 on error.
 */
ssize_t ioutil_atomic_read(int fd, void *buf, unsigned int size);

/* internal function to atomically perform a write. 
 *
 * The normal write(2) function can return after writing
 * less than SIZE bytes, if for instance the write is
 * interrupted by a signal.
 *
 * XXX If FD is of a type that supports non-blocking operation
 * (i.e. not a regular file), and O_NONBLOCK is set on FD,
 * then if at any time FD is unable to accept any data for
 * writing, this function will return an ERROR.  For this reason (and
 * because in any case it doesn't make much sense) you should
 * NOT use this function with non-blocking file descriptors.
 *
 * Return: SIZE on success, or -1 on error.
 */
ssize_t ioutil_atomic_write(int fd, void *buf, unsigned int size);

#ifdef __cplusplus
}
#endif

#endif /* IOUTIL_H */
