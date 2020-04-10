/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_insert_tilda.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 21:39:19 by tjonella          #+#    #+#             */
/*   Updated: 2020/04/10 20:57:20 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char		*tilda_realloc(char **str, char *ptr)
{
	int		len;
	char	*new_str;
	char	*env;

	env = sh21_getenv("HOME");
	len = ft_strlen(env);
	new_str = ft_memalloc(ft_strlen(*str) + len + 1);
	ft_strncpy(new_str, *str, ptr - *str);
	ft_strcat(new_str, env);
	ft_strcat(new_str, ptr + 1);
	free(env);
	free(*str);
	*str = new_str;
	new_str = NULL;
	return (*str);
}

static int		search_tilda(char *str)
{
	while (*str)
	{
		if (*str == '~')
			return (1);
		str++;
	}
	return (0);
}

char			*pars_insert_tilda(char **str)
{
	char	*ptr;

	ptr = *str;
	while (search_tilda(*str) && *ptr)
	{
		if (parse_is_quote(*ptr))
			ptr = parse_next_quote(ptr);
		if (*ptr == '~')
		{
			*str = tilda_realloc(str, ptr);
			ptr = *str;
		}
		else
			ptr++;
	}
	return (*str);
}
