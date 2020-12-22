/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidokin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:56:21 by mdelphia          #+#    #+#             */
/*   Updated: 2020/12/22 14:18:57 by mnidokin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	find_and_run_cmd(t_exec_lst *execlist, t_pars_list *list, int argc)
{
	argc = ft_lineslen(list->pars_args);
	if (!ft_strcmp("true", list->name_func))
		list->status = cmd_true();
	else if (!ft_strcmp("false", list->name_func))
		list->status = cmd_false();
	else if (!ft_strcmp("cd", list->name_func))
		list->status = sh21_cd(execlist, argc, list->pars_args, NULL);
	else if (!ft_strcmp("echo", list->name_func))
		list->status = sh21_echo(argc, list->pars_args, NULL);
	else if (!ft_strcmp("pwd", list->name_func))
		list->status = sh21_pwd(argc, list->pars_args, NULL);
	else if (!ft_strcmp("setenv", list->name_func))
		list->status = sh21_setenv(execlist, list->pars_args[1],
		list->pars_args[2], 1);
	else if (!ft_strcmp("unsetenv", list->name_func))
		list->status = sh21_unsetenv(execlist, list->pars_args[1]);
	else if (!ft_strcmp("exit", list->name_func))
		list->status = exit_with_code(list);
	else if (!ft_strcmp("type", list->name_func))
		list->status = iu_type(execlist, list);
	else if (!ft_strcmp("env", list->name_func))
		exec_env(execlist, list);
	else if (!ft_strcmp("test", list->name_func))
	{
		list->status = iu_test(list->pars_args);
		ft_putstr(COLOR_USER);
		ft_putstr("test return = ");
		ft_putstr(FT_COLOR_GREEN);
		if (list->status == EXIT_SUCCESS)
			ft_putstr("ok");
		else
			ft_putstr("wrong");
		ft_putstr(COLOR_DFLT);
		ft_putendl("");
	}
	return (execlist->sh_term_lst.exec_status = list->status);
}

int			run_cmd(t_exec_lst *execlist, t_pars_list *list)
{
	if (list->f_delimiter & V_DOLLAR)
		insert_dollar_args(execlist, list);
	return (find_and_run_cmd(execlist, list, 0));
}
