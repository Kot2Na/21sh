/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 00:27:17 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/12 04:08:57 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

static void		delete_name(t_exec_lst *execlist, char *const *need_delete)
{
	t_env	*env;

	env = execlist->sh_environ;
	if (need_delete)
		while (*need_delete)
			sh21_unsetenv(execlist, *need_delete++);
}

char *const		*u_flag(t_exec_lst *execlist, char *const argv[])
{
	char	**split;

	if (argv && *argv)
	{
		if (!ft_strcmp(*argv, "-S"))
		{
			++argv;
			split = s_flag((char *)*argv);
			delete_name(execlist, split);
			ft_strdel_split(split);
			free(split);
			split = NULL;
		}
		else
			sh21_unsetenv(execlist, *argv);
		++argv;
	}
	return (argv);
}

static void		change_value(t_exec_lst *execlist, char *const *need_add,
								t_uc scope)
{
	struct s_nameval nval;

	if (need_add && *need_add)
	{
		if (!execlist->sh_environ)
			execlist->sh_environ = env_new((char**)need_add, scope);
		else
			while (*need_add)
			{
				nval = split_name_val(*need_add);
				execlist->sh_environ->add(execlist->sh_environ, nval.name,
											nval.value, scope);
				ft_strdel(&nval.name);
				ft_strdel(&nval.value);
				++need_add;
			}
	}
}

char	*const	*change_value_name(t_exec_lst *execlist, char *const argv[],
									t_uc scope)
{
	char	**split;

	split = NULL;
	if (*argv && !ft_strcmp(*argv, "-S"))
	{
		++argv;
		if (*argv && ft_strtabchr((char *)*argv, '='))
		{
			split = s_flag(*argv);
			change_value(execlist, split, scope);
			ft_strdel_split(split);
			free(split);
			split = NULL;
		}
	}
	else
	{
		if (*argv && ft_strtabchr(*argv, '='))
		{
			change_value(execlist, (char *const *)*&argv, scope);
			++argv;
		}
	}
	return (argv);
}

char			**s_flag(const char *str)
{
	char	**split;

	split = NULL;
	if (str)
		split = ft_strsplit_skip_space((char *)str, ' ');
	return (split);
}
