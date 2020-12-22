/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 13:55:30 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/22 17:44:25 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char		*skip_args(char *str, char *splitter)
{
	while (str != splitter && !ft_isspace(*str))
		++str;
	return (str);
}

static int		check_str(const char *str, char *splitter)
{
	size_t	qty_sym;

	qty_sym = 0;
	str = ft_skiptabs(str);
	while (*str && str != splitter)
	{
		++qty_sym;
		++str;
	}
	return (qty_sym ? TRUE : FALSE);
}

static int		fill_struct(char *str_start, t_info_parser *prs, char *splitter,
							char *str)
{
	size_t	qty_args;
	char	*check_pos;

	str = str_start;
	if (parser_check_dollar(str, prs->end, splitter))
		return (1);
	while (*str && str != splitter)
	{
		str = ft_skiptabs(str);
		str = parser_skipminus(str);
		if (str == splitter)
			break ;
		check_pos = str;
		str = parser_find_ampersand(str, prs->end);
		if (!(str = pars_find_stream(str, splitter, prs->end)))
			return (1);
		str = parser_skip_quotes(str, splitter);
		if (check_pos == str)
			str = skip_args(str, splitter);
	}
	parser_check_ampersand(splitter, prs->end);
	qty_args = parser_count_args(str_start, splitter);
	qty_args = parser_get_count_args_heredoc(prs->end, qty_args);
	prs->end->pars_args = parser_fill_args(str_start, splitter, qty_args);
	return (0);
}

static int		parse_str(t_exec_lst *execlist, char **str_for_parse,
					t_info_parser *prs)
{
	char	*splitter;
	char	*str;

	str = pars_insert_tilda(execlist, str_for_parse);
	while (str && *str)
	{
		if (!(splitter = find_delimiter(str)))
			return (1);
		str = parser_skip_quotes(str, splitter);
		if ((check_str(str, splitter)) == TRUE)
			parser_add_list(prs);
		else
		{
			str = (*splitter) ? ++splitter : splitter;
			continue;
		}
		if (fill_struct(str, prs, splitter, NULL))
			return (1);
		str = skip_splitter(splitter, &prs->end->f_delimiter);
	}
	return ((str) ? 0 : 1);
}

int				parser(t_exec_lst *execlist, char **str_for_parse,
					t_info_parser *prs)
{
	if (parse_str(execlist, str_for_parse, prs))
		return (1);
	parser_fill_point_args(prs->beg);
	return (0);
}
