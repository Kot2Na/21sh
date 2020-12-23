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

int			errors_braces(char *err_msg)
{
	g_exit_status = 1;
	ft_putstr_fd(err_msg, STDERR_FILENO);
	return (1);
}

char		*dollar_realloc(t_exec_lst *execlist, char **str, char *ptr)
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

char		*exit_status_realloc(char **str, char *ptr, int braces)
{
	int		len;
	char	*value;
	char	*new_str;
	char	*end_env;

	value = ft_itoa(g_exit_status);
	end_env = ptr + 2 + braces;
	len = ft_strlen(value);
	new_str = ft_memalloc(ft_strlen(*str) + len - 1 - braces);
	ft_strncpy(new_str, *str, ptr - *str);
	ft_strcat(new_str, value);
	ft_strcat(new_str, end_env);
	free(*str);
	free(value);
	*str = new_str;
	new_str = NULL;
	return (*str);
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
