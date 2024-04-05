/* TODO: v1.1: Calculate window size manually using cursor positions and end of window. */
/* TODO: v1.1: Detect scroll bar to display status correctly. Normalize in xterm-256color on Ubuntu 23.10. */
/* TODO: v1.1: Optimize and review searching code. */
/* TODO: v1.1: Normalize searching with tabs. */
/* TODO: v1.1: Test where we do not need win_scroll. */
/* TODO: v1.1: Just input search query in search mode. After Enter key save search query (do not show it on the status). Move forward using Enter and move backward using Tab. */
/* TODO: v1.2: Create Cell struct to handle all symbols including UTF-8. Create structs Win->Renders->Render->Cells->Cell. Rerender lines on window side */
/* TODO: v1.3: Use linked list for lines array and line's content parts. */
/* TODO: v1.3: Undo operations. Also rename "del" to "remove" where needed. */
/* TODO: v1.4: Add local clipboard. Use it in functions. */
/* TODO: v1.4: Xclip patch to use with local clipboard. */
/* TODO: v1.5: Add more clear docs and comments. */
/* TODO: v1.5: Support huge files. */
/* TODO: v1.6: API with status codes instead of err.h. Add tests */

#include <err.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "ed.h"

static const char *const usage = "Usage:\n\t$ se <filename>";

/* Handle editor signals. */
static void handle_signal(int signal);

static Ed *ed;

static void
handle_signal(int signal)
{
	ed_handle_signal(ed, signal);
}

int
main(const int argc, const char *const *const argv)
{
	/* Check filename in arguments */
	if (argc != 2)
		errx(EXIT_FAILURE, usage);

	/* Opens file in the editor */
	ed = ed_open(argv[1], STDIN_FILENO, STDOUT_FILENO);

	/* Register signals handler */
	if (signal(SIGWINCH, handle_signal) == SIG_ERR)
		err(EXIT_FAILURE, "Failed to set signal handler.");

	while (1) {
		/* Draws editor's content on the screen */
		ed_draw(ed);
		/* Check that we need to quit. Need here to clear screen before quit */
		if (ed_need_to_quit(ed))
			break;
		/* Wait and process key presses */
		ed_wait_and_proc_key(ed);
	}

	/* Quit the editor */
	ed_quit(ed);
	return EXIT_SUCCESS;
}
