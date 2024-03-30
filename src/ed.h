#ifndef _ED_H
#define _ED_H

#include "mode.h"
#include "win.h"

enum {
	ED_INPUT_NUM_RESET = -1, /* Flag to reset number input */
	ED_MSG_ARR_LEN = 64, /* Capacity of message buffer */
};

/*
Editor options.

To edit, you need to connect the editor to the terminal and then open the file.
*/
typedef struct {
	Win win; /* Info about terminal's view. This is what the user sees */
	Mode mode; /* Input mode */
	char msg[ED_MSG_ARR_LEN]; /* Message for the user */
	size_t num_input; /* Number input. 0 if not set */
	unsigned char quit_presses_rem; /* Greater than 1 if file is dirty */
} Ed;

/* Determines how many times the next action needs to be repeated. */
size_t ed_get_repeat_times(const Ed *);

/*
Writes digit to the number input. Resets if argument is reset flag.
*/
void ed_input_num(Ed *, char);

/* Determines that we need to quit. */
char ed_need_to_quit(const Ed *);

/* Use it when user presses quit key. Interacts with the remaining counter. */
void ed_on_quit_press(Ed *);

/*
Opens a file and binds editor to specified file descriptors.

Do not forget to close the editor.
*/
void ed_open(Ed *, const char *, int, int);

/* Quits opened editor. */
void ed_quit(Ed *);

/* Saves opened file. */
void ed_save(Ed *const ed);

/* Saves opened file to spare dir. Useful if no privileges. */
void ed_save_to_spare_dir(Ed *const ed);

/* Sets formatted message to the user. */
void ed_set_msg(Ed *, const char *, ...);

#endif /* _ED_H */
