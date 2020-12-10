/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelphia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:43:00 by mdelphia          #+#    #+#             */
/*   Updated: 2020/03/08 20:35:56 by mdelphia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void		close_all_fd(t_pipe_list *pipelist)
{
	t_pipe_list *buf_pipelist;

	buf_pipelist = pipelist;
	while (buf_pipelist)
	{
		close(buf_pipelist->pfd[0]);
		close(buf_pipelist->pfd[1]);
		buf_pipelist = buf_pipelist->prev;
	}
}

static void		close_pipe_fd(t_pipe_list *pipelist)
{
	t_pipe_list	*buf_pipelist;

	buf_pipelist = pipelist->prev;
	if (buf_pipelist)
		close(buf_pipelist->pfd[1]);
	else
		return ;
	buf_pipelist = buf_pipelist->prev;
	close_all_fd(buf_pipelist);
}

static void		cod_child(t_exec_lst *execlist, t_pipe_list **pipelist,
					t_pars_list *list, t_job *jobs)
{
	t_pipe_list *buf_pipelist;
	

	buf_pipelist = ((*pipelist)->prev) ? (*pipelist)->prev : (*pipelist);
	if (list->f_delimiter & F_PIPE)
		dup_fd_and_close((*pipelist)->pfd[1], STDOUT_FILENO);
	else
		close((*pipelist)->pfd[1]);
	close((*pipelist)->pfd[0]);
	close_pipe_fd(*pipelist);
	stream_and_file(execlist, list);
	if (check_cmd(list->name_func))
	{
		stream_and_file(execlist, list);
		dup_fd_and_close(buf_pipelist->pfd[0], STDIN_FILENO);
		run_cmd(execlist, list, jobs);
		exit(list->status);
	}
	else
	{
		write_name_run(execlist, list);
		run_exec(buf_pipelist->pfd[0], list, execlist);
	}
}

static void		cod_parent(t_exec_lst *execlist, pid_t pid,
					t_pipe_list **pipelist, t_pars_list **list, t_job *jobs)
{
	t_pars_list *buf_list;

	buf_list = (*list);
	if ((buf_list->next) && (buf_list->f_delimiter & F_PIPE))
	{
		(*list) = (*list)->next;
		run_pipe(execlist, pipelist, list, jobs);
	}
	buf_list->completed = 0;
	close_all_fd(*pipelist);
	waitpid(pid, &buf_list->status, WUNTRACED);
	buf_list->completed = 1;
	error_system(execlist, buf_list->status);
	buf_list->pid = pid;
}

void			run_pipe(t_exec_lst *execlist, t_pipe_list **pipelist,
					t_pars_list **list, t_job *jobs)
{
	pid_t		pid;

	(*pipelist) = new_pipe_list(execlist, *pipelist);
	pipe((*pipelist)->pfd);
	if ((pid = fork()) < 0)
		error_system(execlist, EXEC_ERROR_NUM);
	if (!pid)
	{
		jobs->pgid == 0 ? jobs->pgid = pid : 0;
		setpgid(pid, jobs->pgid);
		recover_shell_signals();
		if (!(*list)->foreground)
		{
			tcsetpgrp(globs()->g_shell_term, jobs->pgid);
		}
		recover_shell_signals();
		cod_child(execlist, pipelist, (*list), jobs);
	}
	cod_parent(execlist, pid, pipelist, list, jobs);
}
