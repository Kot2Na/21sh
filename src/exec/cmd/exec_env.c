/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:56:21 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/12 03:37:23 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	**skip_env_args(char **parse_list, int *argc)
{
	char	**new_args;
	char	**cpy_prs;

	cpy_prs = parse_list;
	while (parse_list && *parse_list)
	{
		if (!ft_strchr(*parse_list, '='))
			break ;
		++parse_list;
		--(*argc);
	}
	new_args = ft_linedup(parse_list);
	ft_strdel_split(cpy_prs);
	free(cpy_prs);
	return (new_args);
}

static char	**skip_env_flags(char **pars_list, int *argc)
{
	size_t	i;
	char	**cpy_prs;
	char	**new_args;
	size_t	skip_args;

	i = 0;
	skip_args = 0;
	cpy_prs = pars_list;
	++pars_list;
	--(*argc);
	while ((int)i < *argc && *pars_list)
	{
		if (**pars_list == '-')
		{
			++pars_list;
			++skip_args;
		}
		++i;
	}
	new_args = ft_linedup(pars_list);
	ft_strdel_split(cpy_prs);
	free(cpy_prs);
	*argc -= skip_args;
	return (new_args);
}

void		exec_env(t_exec_lst *execlist, t_pars_list *list)
{
	char	**cpy_environ_src;
	int		argc;
	char	**environ;

	environ = execlist->sh_environ->all(execlist->sh_environ);
	cpy_environ_src = ft_linedup(environ);
	free(environ);
	argc = ft_lineslen(list->pars_args);
	sh21_env(execlist, argc, list->pars_args);
	list->pars_args = skip_env_flags(list->pars_args, &argc);
	list->pars_args = skip_env_args(list->pars_args, &argc);
	if (argc > 0)
	{
		list->name_func = list->pars_args[0];
		check_run(execlist, &list);
		execlist->sh_environ->destroy(execlist->sh_environ);
		execlist->sh_environ = env_new(cpy_environ_src, V_ENVIR);
	}
	else
		env_print_all(execlist->sh_environ, V_ENVIR);
	ft_strdel_split(cpy_environ_src);
	free(cpy_environ_src);
}
