/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_dollar_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 03:51:19 by mdelphia          #+#    #+#             */
/*   Updated: 2020/12/20 18:02:20 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"

char		*search_first_space(char *ptr)
{
	ptr++;
	while (*ptr && (ft_isalpha(*ptr) || ft_isdigit(*ptr) || *ptr == '_' ||
				*ptr == '?'))
		ptr++;
	return (ptr - 1);
}

static int	search_dollar(char *str)
{
	while (*str)
	{
		if (*str == '$')
			return (1);
		str++;
	}
	return (0);
}

static char	*way_of_realloc(t_exec_lst *execlist, char **str, char *ptr,
							int *worked)
{
	if (*(ptr + 1) && *(ptr + 2) && *(ptr + 3) &&
		*(ptr + 1) == '{' && *(ptr + 2) == '?' && *(ptr + 3) == '}')
	{
		*str = exit_status_realloc(str, ptr, 2);
		*worked = 1;
	}
	else if (*(ptr + 1) && *(ptr + 1) == '{')
	{
		*str = braces_dollar_realloc(execlist, str, ptr);
		*worked = 1;
	}
	else if (*(ptr + 1) && *(ptr + 1) == '?')
	{
		*str = exit_status_realloc(str, ptr, 0);
		*worked = 1;
	}
	else if (*(ptr + 1) && (ft_isalpha(*(ptr + 1)) ||
		ft_isdigit(*(ptr + 1)) || *(ptr + 1) == '_'))
	{
		*str = dollar_realloc(execlist, str, ptr);
		*worked = 1;
	}
	return (*str);
}

static char	*pars_insert_env_value(t_exec_lst *execlist, char **str, char *ptr,
									int worked)
{
	ptr = *str;
	while (search_dollar(*str) && *ptr)
	{
		if (parse_is_quote(*ptr))
			ptr = parse_next_quote(ptr);
		if (*ptr == '$')
		{
			*str = way_of_realloc(execlist, str, ptr, &worked);
			if (worked)
			{
				ptr = *str;
				worked = 0;
			}
			else
				ptr++;
		}
		else
			ptr++;
	}
	if (!ft_strlen(*str))
	{
		free(*str);
		return (NULL);
	}
	return (*str);
}

void		insert_dollar_args(t_exec_lst *execlist, t_pars_list *list)
{
	char	**ptr;
	char	*new_line;
	int		i;

	i = 0;
	ptr = list->pars_args;
	while (*ptr)
	{
		if ((new_line = pars_insert_env_value(execlist, ptr, NULL, 0)))
		{
			list->pars_args[i] = new_line;
			ptr++;
			i++;
		}
		else
			ptr = pars_dollar_shift_args(list->pars_args, i);
	}
	list->name_func = *(list->pars_args);
}
