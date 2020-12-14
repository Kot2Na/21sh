/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_name_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 15:31:10 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/12/12 15:31:11 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

static int	belongs_to_env(char *name, t_exec_lst *execlist)
{
	if (name && *name)
	{
		if (sh21_getenv(execlist, name))
			return (1);
		if (!ft_strcmp("TERM_SESSION_ID", name) ||
		!ft_strcmp("SSH_AUTH_SOCK", name) ||
		!ft_strcmp("LC_TERMINAL_VERSION", name) ||
		!ft_strcmp("COLORFGBG", name) || !ft_strcmp("ITERM_PROFILE", name) ||
		!ft_strcmp("XPC_FLAGS", name) || !ft_strcmp("LANG", name) ||
		!ft_strcmp("PWD", name) || !ft_strcmp("SHELL", name) ||
		!ft_strcmp("TERM_PROGRAM_VERSION", name) ||
		!ft_strcmp("TERM_PROGRAM", name) || !ft_strcmp("PATH", name) ||
		!ft_strcmp("LC_TERMINAL", name) || !ft_strcmp("COLORTERM", name) ||
		!ft_strcmp("TERM", name) || !ft_strcmp("HOME", name) ||
		!ft_strcmp("TMPDIR", name) || !ft_strcmp("USER", name) ||
		!ft_strcmp("XPC_SERVICE_NAME", name) ||
		!ft_strcmp("LOGNAME", name) ||
		!ft_strcmp("ITERM_SESSION_ID", name) ||
		!ft_strcmp("__CF_USER_TEXT_ENCODING", name) ||
		!ft_strcmp("SHLVL", name) || !ft_strcmp("OLDPWD", name) ||
		!ft_strcmp("OLD_PWD", name) || !ft_strcmp("_", name))
			return (1);
	}
	return (0);
}

static char	*get_name(char *name_func)
{
	size_t	i;
	char	*res;

	i = 0;
	while (name_func[i] && name_func[i] != '=')
		i++;
	res = ft_strnew(i + 1);
	ft_memcpy(res, name_func, i);
	return (res);
}

static char	*get_value(char *name_func)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	while (name_func[i] && name_func[i] != '=')
		i++;
	i++;
	j = i;
	while (name_func[j])
		j++;
	res = ft_strnew(j - i + 1);
	ft_strcpy(res, &name_func[i]);
	return (res);
}

int			ft_name_value(t_exec_lst *execlist, t_pars_list *list)
{
	char	*name;
	char	*value;

	name = get_name(list->name_func);
	value = get_value(list->name_func);
	if (belongs_to_env(name, execlist))
		sh21_setenv(execlist, name, value, 1);
	else
		ft_printf("set name=value\n");
	free(name);
	free(value);
	return (0);
}
