/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_common_screen.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 01:28:50 by ksharlen          #+#    #+#             */
/*   Updated: 2020/02/06 23:23:51 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_parse_key.h"

void	check_change_winsize(struct s_input *inp)
{
	struct s_win	wn;

	input_tgetent();
	wn = get_win_size();
	if (ft_memcmp(&wn, &inp->win, sizeof(struct s_win)))
	{
		// inp->win = wn;
		input_update_stat_win(inp, &wn);
	}
		// inp->win = wn;
}

void	input_update_stat_win(struct s_input *inp, struct s_win *wn)
{
	ssize_t	curr_qt_rows;
	ssize_t	chg_qt_rows;
	ssize_t	reminder;

	curr_qt_rows = ((inp->len_greet + inp->gap.len_string) / inp->win.cols) +
	((inp->len_greet + inp->gap.len_string) % inp->win.cols ? 1 : 0);
	chg_qt_rows = (inp->len_greet + inp->gap.len_string) / wn->cols +
	((inp->len_greet + inp->gap.len_string) % wn->cols ? 1 : 0);
	reminder = curr_qt_rows - chg_qt_rows;
	if (reminder)
	{
		if (reminder > 0)
		{
			inp->save_refresh_pos.y += FT_ABS(reminder);
		}
		else
		{
			inp->save_refresh_pos.y -= FT_ABS(reminder);
		}
	}
	inp->win = *wn;
	inp->cr = get_pos_cursor();
	--inp->cr.x;
	--inp->cr.y;
}

int		check_line_footnote_down(struct s_input *inp)
{
	int	is_footnote;

	is_footnote = FALSE;
	if (inp->cr.x == inp->win.cols - 1)
	{
		++inp->cr.y;
		inp->cr.x = 0;
		is_footnote = TRUE;
	}
	return (is_footnote);
}

int		check_line_footnote_up(struct s_input *inp)
{
	int is_footnote;

	is_footnote = FALSE;
	if (!inp->cr.x)
	{
		--inp->cr.y;
		inp->cr.x = inp->win.cols - 1;
		is_footnote = TRUE;
	}
	return (is_footnote);
}

void	clear_full_screen(struct s_input *inp)
{
	char				*str;
	struct s_cursor		cursor_after_clear;

	if (inp->save_refresh_pos.y)
	{
		cursor_after_clear.y = inp->cr.y - inp->save_refresh_pos.y;
		cursor_after_clear.x = inp->cr.x;
		visibility_cursor(NOT_VISIBLE_CUR);
		str = input_tgetstr(CL);
		tputs(str, 0, ft_putchar);
		inp->len_greet = inp->greet(&inp->u_info);
		inp->save_refresh_pos = get_pos_cursor();//!Может быть ошибк
		--inp->save_refresh_pos.x;
		--inp->save_refresh_pos.y;
		str = gap_get_buf(&inp->gap);
		write(STDOUT_FILENO, str, inp->gap.len_string);
		ft_strdel(&str);
		inp->cr = cursor_after_clear;
		set_cursor_pos(inp->cr.x, inp->cr.y);
		visibility_cursor(VISIBLE_CUR);
	}
}
