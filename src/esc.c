#include <stdio.h>
#include <string.h>
#include "color.h"
#include "esc.h"
#include "vec.h"

int
esc_alt_scr_on(Vec *const buf)
{
	int ret;

	ret = vec_append(buf, "\x1b[?1049h", 8);
	return ret;
}

int
esc_alt_scr_off(Vec *const buf)
{
	int ret;

	ret = vec_append(buf, "\x1b[?1049l", 8);
	return ret;
}

int
esc_clr_win(Vec *const buf)
{
	int ret;

	ret = vec_append(buf, "\x1b[2J", 4);
	return ret;
}

int
esc_color_bg(Vec *const buf, const struct color c)
{
	int ret;

	ret = vec_append_fmt(buf, "\x1b[48;2;%hhu;%hhu;%hhum", c.r, c.g, c.b);
	return ret;
}

int
esc_color_fg(Vec *const buf, const struct color c)
{
	int ret;

	ret = vec_append_fmt(buf, "\x1b[38;2;%hhu;%hhu;%hhum", c.r, c.g, c.b);
	return ret;
}

int
esc_color_end(Vec *const buf)
{
	int ret;

	ret = vec_append(buf, "\x1b[0m", 4);
	return ret;
}

int
esc_cur_hide(Vec *const buf)
{
	int ret;

	ret = vec_append(buf, "\x1b[?25l", 6);
	return ret;
}

int
esc_cur_set(Vec *const buf, const unsigned short row, const unsigned short col)
{
	int ret;

	ret = vec_append_fmt(buf, "\x1b[%hu;%huH", row + 1, col + 1);
	return ret;
}

int
esc_cur_show(Vec *const buf)
{
	int ret;

	ret = vec_append(buf, "\x1b[?25h", 6);
	return ret;
}

int
esc_extr_arrow_key(
	const char *const seq,
	const size_t len,
	enum arrow_key *const key
) {
	int cmp;

	/* Check length */
	if (3 != len)
		return -1;

	cmp = strncmp("\x1b[", seq, 2);
	/* Check prefix and arrow key */
	if (0 == cmp && ARROW_KEY_UP <= seq[2] && seq[2] <= ARROW_KEY_LEFT) {
		*key = seq[2];
		return 0;
	}
	return -1;
}

int
esc_extr_mouse_wh_key(
	const char *const seq,
	const size_t len,
	enum mouse_wh_key *const key
) {
	int cmp;

	/* Check length */
	if (4 != len)
		return -1;

	cmp = strncmp("\x1b[M", seq, 3);
	/* Check prefix and wheel key */
	if (0 == cmp && MOUSE_WH_KEY_UP <= seq[3] && seq[3] <= MOUSE_WH_KEY_DOWN) {
		*key = seq[3];
		return 0;
	}
	return -1;
}

int
esc_go_home(Vec *const buf)
{
	int ret;

	ret = vec_append(buf, "\x1b[H", 3);
	return ret;
}

int
esc_mouse_wh_track_off(Vec *const buf)
{
	int ret;

	ret = vec_append(buf, "\x1b[?1000l", 8);
	return ret;
}

int
esc_mouse_wh_track_on(Vec *const buf)
{
	int ret;

	ret = vec_append(buf, "\x1b[?1000h", 8);
	return ret;
}
