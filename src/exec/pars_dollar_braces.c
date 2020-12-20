/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_dollar_braces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:48:01 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/12/20 18:07:31 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"

char		*errors_braces(char **str, char *err_msg)
{
	ft_putstr_fd(err_msg, STDERR_FILENO);
	free(*str);
	return (NULL);
}

char		*braces_dollar_realloc(t_exec_lst *execlist, char **str,
									char *ptr)
{
	int		len;
	char	*new_str;
	char	*end_env;
	char	*env_name;

	end_env = search_first_space(ptr + 1);
	end_env++;
	if (*end_env != '}')
		return (errors_braces(str, "42sh: bad substitution\n"));
	env_name = ft_memalloc(end_env - ptr);
	ft_strncpy(env_name, ptr + 2, end_env - ptr - 2);
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
