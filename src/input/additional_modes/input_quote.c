/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidokin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:11:15 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/25 17:35:16 by mnidokin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_parse_key.h"

static void	put_in_stack_quote_from_str(const char *str, t_queue *qu)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"' || *str == '`')
			ft_qu_push(qu, (void *)str, sizeof(char));
		++str;
	}
}

static void	quote_init(struct s_input *inp)
{
	gap_clean_buf(&inp->gap);
	inp->save_refresh_pos = get_pos_cursor();
	--inp->save_refresh_pos.y;
	inp->save_refresh_pos.x = inp->greet.len;
	inp->cr = inp->save_refresh_pos;
	inp->key = 0;
}

static char	line_form(struct s_input *inp, char search_qt, char *src_str)
{
	char		*str;
	char		new_line;
	char		close_qt;
	t_queue		qu;

	new_line = '\n';
	ft_qu_init(&qu);
	ft_qu_push(&qu, &search_qt, sizeof(char));
	str = gap_get_buf(&inp->gap);
	if (str)
	{
		if (inp->greet.mode == '\"')
		{
			if (!(ft_search_backslash(&src_str) == EXIT_SUCCESS || ft_search_backslash(&str) == EXIT_SUCCESS))
			{
				ft_strncat(src_str, &new_line, 1);
			}
		}
		else if (((ft_search_backslash(&src_str) == EXIT_FAILURE || ft_search_backslash(&str) == EXIT_FAILURE)))
		{
			ft_strncat(src_str, &new_line, 1);
		}
		put_in_stack_quote_from_str(str, &qu);
		inp->str_for_parse = ft_strreplace(src_str, str);
		close_qt = search_double_quotes(&qu);
	}
	else
		close_qt = search_qt;
	return (close_qt);
}

static void	quote_mode(t_exec_lst *execlist, struct s_input *inp,
				char search_qt, char *src_str)
{
	char	close_qt;

	inp->greet.mode = search_qt;
	input_greeting(&inp->greet);
	quote_init(inp);
	while (inp->key != KEY_NEW_LINE)
	{
		inp->key = input_getch(execlist, inp);
		if (inp->key == ('c' & 0x1f))
		{
			input_put_new_line(inp);
			clean_struct_input(inp);
			return ;
		}
		input_process_key_press(inp);
	}
	input_put_new_line(inp);
	close_qt = line_form(inp, search_qt, src_str);
	if (close_qt != TRUE)
		quote_mode(execlist, inp, close_qt, inp->str_for_parse);
}

void		input_quote_mode(t_exec_lst *execlist, struct s_input *inp)
{
	t_queue	qu;
	int		quote_close;

	ft_qu_init(&qu);
	put_in_stack_quote_from_str(inp->str_for_parse, &qu);
	quote_close = search_double_quotes(&qu);
	if (quote_close != TRUE)
	{
		inp->greet.mode = quote_close;
		quote_mode(execlist, inp, quote_close, inp->str_for_parse);
	}
}

int	ft_search_backslash(char **str)
{
	int	index;

	index = 0;
	while ((*str)[index])
	{
		index++;
	}
	if ((*str)[index - 1] == '\\')
	{
		(*str)[index - 1] = '\0';
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
