/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:41:27 by mdelphia          #+#    #+#             */
/*   Updated: 2020/12/19 17:19:44 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_and_fill_flag_dollar(char *str, t_pars_list *list)
{
	if (*str == '$' && *(str - 1) != '\\' &&
		(ft_isalpha(*(str + 1)) || ft_isdigit(*(str + 1)) ||
			(*(str + 1) == '}') || (*(str + 1) == '{')))
	{
		list->f_delimiter |= V_DOLLAR;
		return (1);
	}
	return (0);
}

int			error_with_braces(char *str)
{
	int		i;
	char	*end_env;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] == '}')
			return (errors_braces("42sh: parse error near `}'\n"));
		if (str[i] == '$' && str[i + 1] == '{')
		{
			end_env = search_first_space(&str[i + 1]);
			end_env++;
			if (*end_env != '}')
				return (errors_braces("42sh: bad substitution\n"));
			else
			{
				if (*(end_env + 1) && *(end_env + 1) == '}')
					return (errors_braces("42sh: parse error near `}'\n"));
			}
		}
	}
	return (0);
}

int			parser_check_dollar(char *str, t_pars_list *list, char *splitter)
{
	while (str < splitter)
	{
		if (check_and_fill_flag_dollar(str, list) == 1)
		{
			if (error_with_braces(str))
				return (1);
			break ;
		}
		++str;
	}
	return (0);
}
