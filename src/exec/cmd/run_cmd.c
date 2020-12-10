/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:56:21 by mdelphia          #+#    #+#             */
/*   Updated: 2020/12/07 16:10:33 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	find_and_run_cmd(t_exec_lst *execlist, t_pars_list *list, t_job *jobs)
{
	int argc;

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
	else if (!ft_strcmp("jobs", list->name_func))
		list->status = sh42_jobs(jobs);
	else if (!ft_strcmp("env", list->name_func))
		exec_env(execlist, list, jobs);
	return (execlist->sh_term_lst.exec_status = list->status);
}

int			run_cmd(t_exec_lst *execlist, t_pars_list *list, t_job *jobs)
{
	if (list->f_delimiter & V_DOLLAR)
		insert_dollar_args(execlist, list);
	return (find_and_run_cmd(execlist, list, jobs));
}
