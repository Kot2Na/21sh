/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_name_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 15:31:10 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/12/18 06:39:28 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

#define SH_ENVVARS_SIZE 77

char *g_env_vars[SH_ENVVARS_SIZE] = {"ARFLAGS", "IFS", "MAILPATH", "PS1", "CC",
	"LANG", "MAILRC", "PS2", "CDPATH", "LC_ALL", "MAKEFLAGS", "PS3", "CFLAGS",
	"LC_COLLATE", "MAKESHELL", "PS4", "CHARSET", "LC_CTYPE", "MANPATH", "PWD",
	"COLUMNS", "LC_MESSAGES", "MBOX", "RANDOM", "DATEMSK", "LC_MONETARY",
	"MORE", "SECONDS", "DEAD", "LC_NUMERIC", "MSGVERB", "SHELL", "EDITOR",
	"LC_TIME", "NLSPATH", "TERM", "ENV", "LDFLAGS", "NPROC", "TERMCAP",
	"EXINIT", "LEX", "OLDPWD", "TERMINFO", "FC", "LFLAGS", "OPTARG", "TMPDIR",
	"FCEDIT", "LINENO", "OPTERR", "TZ",
	"FFLAGS", "LINES", "OPTIND", "USER", "GET", "LISTER", "PAGER", "VISUAL",
	"GFLAGS", "LOGNAME", "PATH", "YACC", "HISTFILE", "LPDEST", "PPID", "YFLAGS",
	"HISTORY", "MAIL", "PRINTER", "HISTSIZE", "MAILCHECK", "PROCLANG", "HOME",
	"MAILER", "PROJECTDIR"};

static int	belongs_to_env(char *name, t_exec_lst *execlist)
{
	int i;

	i = -1;
	if (name && *name)
	{
		if (sh21_getenv(execlist, name))
			return (1);
		while (++i < SH_ENVVARS_SIZE)
			if (!ft_strcmp(g_env_vars[i], name))
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
	if (name_func[i] == 0)
		return (NULL);
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

static void	error_not_found(char *s)
{
	ft_putstr_fd(STR_ERR_SHELL, STDERR_FILENO);
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

int			ft_name_value(t_exec_lst *execlist, t_pars_list *list, int i)
{
	char	*name;
	char	*value;
	int		err;

	err = SUCCESS;
	while (list->pars_args[++i])
	{
		name = get_name(list->pars_args[i]);
		if (!name)
		{
			err = 127;
			error_not_found(list->pars_args[i]);
			break ;
		}
		value = get_value(list->pars_args[i]);
		if (belongs_to_env(name, execlist))
			sh21_setenv(execlist, name, value, 1);
		else
			execlist->sh_environ->add(execlist->sh_environ, name, value, \
					V_INTERN);
		free(name);
		free(value);
	}
	return (err);
}
