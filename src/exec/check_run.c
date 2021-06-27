/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:41:46 by mdelphia          #+#    #+#             */
/*   Updated: 2020/12/09 01:14:53 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void		ignore_signals(int sig)
{
	kill(g_pid, sig);
}

static void	cod_child(t_exec_lst *execlist, t_pars_list **list)
{
	//entry_canon(&((g_init->inp).cfg_cpy));
	if (!stream_and_file(execlist, *list))
		run_exec(-1, (*list), execlist);
	else
		exit(1);
	//entry_not_canon(&((g_init->inp).cfg_cpy));
}

static int	run_fork(t_exec_lst *execlist, t_pars_list **list, t_job *jobs)
{
	t_job_l job_l;
	
	job_l.infile = jobs->stdinc;
	job_l.p = jobs->first_process;
	job_l.mypipe[0] = 0;
	job_l.mypipe[1] = 0;
	while (job_l.p)
	{
		if (job_l.p->next)
		{
			if (pipe(job_l.mypipe) < 0)
				exit(1);
			job_l.outfile = job_l.mypipe[1];
		}
		else
			job_l.outfile = jobs->stdoutc;

		if ((job_l.pid = fork()) < 0)
			error_system(execlist, EXEC_ERROR_NUM);
		if (!job_l.pid)
		{
			write_name_run(execlist, *list);
			cod_child(execlist, list);
		}
		else
		{
			if (globs()->g_shell_interac)
			{
				if (!jobs->pgid)
					jobs->pgid = job_l.pid;
				setpgid(job_l.pid, jobs->pgid);
			}
			sh21_signals(ignore_signals);
		}
		(*list)->pid = job_l.pid;

			
		if (job_l.infile != jobs->stdinc)
			close(job_l.infile);
		if (job_l.outfile != jobs->stdoutc)
			close(job_l.outfile);
		job_l.infile = job_l.mypipe[0];

		job_l.p = job_l.p->next;
		(*list)->completed = 0;

		if (!globs()->g_shell_interac)
		{
			job_wait(jobs);
		}
		else if (jobs->foreground)
			put_job_in_foreground(jobs, 0);
		else
			put_job_in_background(jobs, 0);

	}
	return ((*list)->status);
}

static int	code_pipe(t_exec_lst *execlist, t_pars_list **list, t_job *jobs)
{
	t_pipe_list	**pipelist;
	t_pipe_list	*bufpipelist;

	bufpipelist = NULL;
	pipelist = &bufpipelist;
	run_pipe(execlist, pipelist, list, jobs);
	error_system(execlist, (*list)->status);
	execlist->sh_term_lst.exec_status = (*list)->status;
	execlist->sh_term_lst.pid_last = (*list)->pid;
	free_pipe_list(*pipelist);
	return (execlist->sh_term_lst.exec_status);
}

int			check_run(t_exec_lst *execlist, t_pars_list **list, t_job *jobs)
{
	int			status;

	status = 0;
	if ((*list)->name_func)
	{
		if ((*list)->f_delimiter & F_PIPE)
			status = code_pipe(execlist, list, jobs);
		else if (check_cmd((*list)->name_func))
		{
			stream_save_std((*list)->stream_list);
			stream_and_file(execlist, *list);
			status = run_cmd(execlist, *list, jobs);
			close_and_open_std(execlist, (*list)->stream_list);
		}
		else
		{
			//ft_printf("just fork\n");
			status = run_fork(execlist, list, jobs);
		}
	}
	g_exit_status = (g_sig_status ? g_sig_status : status);
	g_sig_status = 0;
	return (status);
}
