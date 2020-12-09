/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 22:10:43 by ksharlen          #+#    #+#             */
/*   Updated: 2020/04/29 23:33:56 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_parse_key.h"

#define IS_CTR_D	0
#define IS_CTR_C	1
#define NOT_EXT_KEY	2

void		input_put_new_line(struct s_input *inp)
{
	int	last_rows_from_str;

	if (inp->gap.len_string + inp->greet.len > (size_t)inp->win.cols)
	{
		last_rows_from_str =
			(inp->gap.len_string + inp->greet.len) / inp->win.cols;
		inp->cr.y = inp->save_refresh_pos.y + last_rows_from_str;
		set_cursor_pos(0, inp->cr.y);
	}
	write(STDOUT_FILENO, "\n", 1);
}

void		clean_struct_input(struct s_input *inp)
{
	if (inp)
	{
		gap_clean_buf(&inp->gap);
		ft_strdel(&inp->str_for_parse);
	}
}

static int	check_ext_key(struct s_input *inp)
{
	int		ext_key;

	ext_key = NOT_EXT_KEY;
	if (inp->key == ('d' & 0x1f) && !inp->gap.len_string)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		entry_canon(&inp->cfg_cpy);
		ext_key = IS_CTR_D;
	}
	else if (inp->key == ('c' & 0x1f))
	{
		g_exit_status = 130;
		input_put_new_line(inp);
		clean_struct_input(inp);
		ext_key = IS_CTR_C;
	}
	return (ext_key);
}

void		input_preparation(t_exec_lst *execlist, struct s_input *inp)
{
	input_tgetent(execlist);
	ft_strdel(&inp->str_for_parse);
	gap_clean_buf(&inp->gap);
	entry_not_canon(&inp->cfg_cpy);
	inp->win = get_win_size();
	inp->cr = get_pos_cursor();
	--inp->cr.x;
	--inp->cr.y;
	inp->save_refresh_pos = inp->cr;
	inp->key = 0;
}

void		input_begin(t_exec_lst *execlist, struct s_input *inp)
{
	int	ext_key;

	inp->greet.mode = MODE_DFLT;
	input_greeting_init(execlist, &inp->greet, &inp->u_info);
	input_greeting(&inp->greet);
	input_preparation(execlist, inp);
	while (inp->key != KEY_NEW_LINE)
	{
		inp->key = input_getch(execlist, inp);
		ext_key = check_ext_key(inp);
		if (ext_key == IS_CTR_D || ext_key == IS_CTR_C)
			return ;
		input_process_key_press(inp);
	}
	input_put_new_line(inp);
	if (inp->gap.len_string)
		inp->str_for_parse = gap_get_buf(&inp->gap);
	input_additional_modes(execlist, inp);
	history_fill_history(inp->hist, inp->str_for_parse);
	entry_canon(&inp->cfg_cpy);
}
