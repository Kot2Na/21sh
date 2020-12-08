/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:41:46 by mdelphia          #+#    #+#             */
/*   Updated: 2020/12/07 17:29:44 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void		ignore_signals(int sig)
{
	(void)sig;
}

static void	cod_child(t_exec_lst *execlist, t_pars_list **list)
{
	if (!stream_and_file(execlist, *list))
		run_exec(-1, (*list), execlist);
	else
		exit(1);
}

static int	run_fork(t_exec_lst *execlist, t_pars_list **list)
{
	pid_t	pid;

	sh21_signals(ignore_signals);
	if ((pid = fork()) < 0)
		error_system(execlist, EXEC_ERROR_NUM);
	if (!pid)
	{
		write_name_run(execlist, *list);
		sh21_signals(ignore_signals);
		cod_child(execlist, list);
	}
	waitpid(pid, &(*list)->status, WUNTRACED);
	error_system(execlist, (*list)->status);
	status_child(execlist, (*list)->status, pid, (*list)->name_run_func);
	execlist->sh_term_lst.pid_last = pid;
	execlist->sh_term_lst.exec_status = (*list)->status;
	return ((*list)->status);
}

static int	code_pipe(t_exec_lst *execlist, t_pars_list **list)
{
	t_pipe_list	**pipelist;
	t_pipe_list	*bufpipelist;

	bufpipelist = NULL;
	pipelist = &bufpipelist;
	run_pipe(execlist, pipelist, list);
	error_system(execlist, (*list)->status);
	execlist->sh_term_lst.exec_status = (*list)->status;
	execlist->sh_term_lst.pid_last = (*list)->pid;
	free_pipe_list(*pipelist);
	return (execlist->sh_term_lst.exec_status);
}

int			check_run(t_exec_lst *execlist, t_pars_list **list)
{
	int			status;

	status = 0;
	if ((*list)->name_func)
	{
		if ((*list)->f_delimiter & F_PIPE)
			status = code_pipe(execlist, list);
		else if (check_cmd((*list)->name_func))
		{
			stream_save_std((*list)->stream_list);
			stream_and_file(execlist, *list);
			status = run_cmd(execlist, *list);
			close_and_open_std(execlist, (*list)->stream_list);
		}
		else
			status = run_fork(execlist, list);
	}
	g_exit_status = status;
	return (status);
}
