#ifndef _FILE_H
#define _FILE_H

#include <stddef.h>

/* File traversal direction. Used, for example, in search. */
enum dir {
	DIR_BWD,
	DIR_FWD,
};

/* Alias for opaque struct of opened file. */
typedef struct file File;

/*
Read only line data. Use functions to modify a string instead of modifying this
structure.
*/
struct pub_line {
	const char *chars;
	size_t len;
	const char *render;
	size_t render_len;
};

/*
Finds line by passed index and absorbs next line.

Returns 0 on success and -1 on error.

Sets `EINVAL` if current or next lines not found.
*/
int file_absorb_next_line(File *, size_t);

/*
Finds line by its index and breaks it at passed position.

Returns 0 on success and -1 on error.

Sets `EINVAL` if line not found.
*/
int file_break_line(File *, size_t, size_t);

/* Closes file and frees memory. */
void file_close(File *);

/*
Deletes character in file's line at passed position.

Returns 0 on success and -1 on error.

Sets `EINVAL` if line or character not found.
*/
int file_del_char(File *, size_t, size_t);

/*
Deletes line by its index.

Returns 0 on success and -1 on error.

Sets `EINVAL` if index is invalid or `ENOSYS` if there is one last line left
that cannot be deleted.
*/
int file_del_line(File *, size_t);

/*
Inserts character to the file's line at passed position.

Returns 0 on success and -1 on error.

Sets `EINVAL` if line not found or insertion position is invalid.
*/
int file_ins_char(File *, size_t, size_t, char);

/*
Inserts empty line at index.

Returns 0 on success and -1 on error.

Sets `EINVAL` if passed index is invalid.
*/
int file_ins_empty_line(File *, size_t);

/* Checks that file is dirty. */
char file_is_dirty(const File *);

/*
Finds line by passed index and returns its data.

Returns 0 on success and -1 on error.

Sets `EINVAL` if index is invalid.
*/
int file_line(const File *, size_t, struct pub_line *);

/* Returns lines count of opened file. */
size_t file_lines_cnt(const File *);

/*
Reads the contents of file. Adds an empty line if there are no lines in the
file. Do not forget to close file.

Returns pointer to opaque struct on success or `NULL` on error.
*/
File *file_open(const char *);

/* Gets path of opened file. */
const char *file_path(const File *);

/*
Saves file to passed path. Saves to opened file's path if argument is `NULL`.

Returns written bytes count and 0 on error.
*/
size_t file_save(File *, const char *);

/*
Saves file to spare directory with generated path. Useful if no privileges.

Writes final path to passed buffer up to passed length. The buffer must have a
capacity one greater than the length for a null byte.

Returns written bytes count on success and 0 on error.
*/
size_t file_save_to_spare_dir(File *, char *, size_t);

/*
Searches in passed direction from passed line index and passes line position.
Modifies index and position.

Temporarily changes file if direction is backward, but then restores it.

Returns 1 if result found, 0 if no result and -1 on error.

Sets `EINVAL` if index is invalid.
*/
int file_search(File *, size_t *, size_t *, const char *, enum dir);

#endif /* _FILE_H */
