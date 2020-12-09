/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:03:00 by ksharlen          #+#    #+#             */
/*   Updated: 2020/02/06 20:42:44 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_parse_key.h"

static void	gap_clean(t_gapbuf *gap)
{
	gap_clean_buf(gap);
	free(gap->buf);
}

static char	*new_line_for_heredoc(char *gap_str)
{
	char	*line;

	line = gap_str ? ft_strjoin(gap_str, "\n") : ft_strdup("\n");
	ft_strdel(&gap_str);
	return (line);
}

static int	fill_line(const char *delimiter, t_gapbuf *gap, char **line)
{
	char	*read_line;

	read_line = gap_get_buf(gap);
	gap_clean(gap);
	if (read_line && !ft_strcmp(delimiter, read_line))
	{
		ft_strdel(&read_line);
		(*line) = NULL;
		return (IS_FOUND_DELIMITER);
	}
	else
	{
		(*line) = new_line_for_heredoc(read_line);
		return (IS_NOT_FOUND_DELIMITER);
	}
}

static int	get_line(t_exec_lst *execlist, const char *delimiter, char **line)
{
	struct s_input	inp;

	
	input_init(&inp);
	inp.greet.mode = MODE_HEREDOC;
	input_greeting(&inp.greet);
	input_preparation(execlist, &inp);
	inp.hist = history_init();
	while (1)
	{
		inp.key = input_getch(execlist, &inp);
		input_process_key_press(&inp);
		if (inp.key == KEY_NEW_LINE)
		{
			write(STDOUT_FILENO, "\n", 1);
			break ;
		}
		else if (inp.key == ('c' & 0x1f))
		{
			write(STDOUT_FILENO, "\n", 1);
			gap_clean(&inp.gap);
			return (BREAK_SIGNAL);
		}
	}
	return (fill_line(delimiter, &inp.gap, line));
}

char		*input_heredoc(t_exec_lst *execlist, char *delimeter)
{
	struct termios	cpy;
	char			buf[SH21_MAX_ARG];
	int				st_heredoc;
	char			*line;

	line = NULL;
	entry_not_canon(&cpy);
	ft_bzero(buf, SH21_MAX_ARG);
	while (1)
	{
		st_heredoc = get_line(execlist, delimeter, &line);
		if (st_heredoc == IS_FOUND_DELIMITER || st_heredoc == BREAK_SIGNAL)
		{
			ft_strdel(&line);
			break ;
		}
		ft_strcat(buf, line);
		ft_strdel(&line);
	}
	entry_canon(&cpy);
	return (st_heredoc == BREAK_SIGNAL ? NULL : ft_strdup(buf));
}
