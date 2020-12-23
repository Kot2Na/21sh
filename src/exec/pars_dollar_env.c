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

static char	*dollar_realloc(t_exec_lst *execlist, char **str, char *ptr)
{
	int		len;
	char	*new_str;
	char	*end_env;
	char	*env_name;

	end_env = search_first_space(ptr);
	env_name = ft_memalloc(end_env - ptr + 1);
	ft_strncpy(env_name, ptr + 1, end_env - ptr);
	len = sh21_getenv(execlist, env_name) ?
		ft_strlen(sh21_getenv(execlist, env_name)) : 0;
	new_str = ft_memalloc(ft_strlen(*str) + len + 1);
	ft_strncpy(new_str, *str, ptr - *str);
	ft_strcat(new_str, sh21_getenv(execlist, env_name) ?
		sh21_getenv(execlist, env_name) : "");
	ft_strcat(new_str, end_env + 1);
	free(env_name);
	free(*str);
	*str = new_str;
	new_str = NULL;
	return (*str);
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

static char	*pars_insert_env_value(t_exec_lst *execlist, char **str, char *ptr)
{
	ptr = *str;
	while (search_dollar(*str) && *ptr)
	{
		if (parse_is_quote(*ptr))
			ptr = parse_next_quote(ptr);
		if (*ptr == '$' && (*(ptr + 1) == '{' || *(ptr + 1) == '}'))
		{
			*str = braces_dollar_realloc(execlist, str, ptr);
			ptr = *str;
		}
		if (*ptr == '$' && *(ptr + 1) && (ft_isalpha(*(ptr + 1)) ||
			ft_isdigit(*(ptr + 1)) || *(ptr + 1) == '?' || *(ptr + 1) == '_'))
		{
			*str = dollar_realloc(execlist, str, ptr);
			ptr = *str;
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
		if ((new_line = pars_insert_env_value(execlist, ptr, NULL)))
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
