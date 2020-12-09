/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 19:42:09 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/09 00:06:19 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void		get_ret_child(t_exec_lst *execlist, const int stat_child)
{
	if (WIFEXITED(stat_child))
		execlist->sh_term_lst.ret_child = WEXITSTATUS(stat_child);
	else
		execlist->sh_term_lst.ret_child = WIFSIGNALED(stat_child);
}

void			status_child(t_exec_lst *execlist, int stat_child,
					pid_t pid_child, char *path_cmd)
{
	char	*lvl_proccess;

	lvl_proccess = sh21_getenv(execlist, SHLVL);
	if (!lvl_proccess)
		lvl_proccess = "1";
	if (stat_child == SIGINT)
	{
		g_sig_status = 130;
		ft_printf("\n");
	}
	else if (stat_child == SIGSEGV)
		print_sig_error(lvl_proccess, pid_child, ESIG, path_cmd);
	else if (stat_child == SIGABRT)
		print_sig_error(lvl_proccess, pid_child, EABR, path_cmd);
	else if (stat_child == SIGBUS)
		print_sig_error(lvl_proccess, pid_child, EBUS, path_cmd);
	else if (stat_child == SIGFPE)
		print_sig_error(lvl_proccess, pid_child, FPOT, path_cmd);
	else if (stat_child == SIGQUIT)
	{
		ft_printf("\n");
		print_sig_error(lvl_proccess, pid_child, QUIT, path_cmd);
	}
	get_ret_child(execlist, stat_child);
}

void			handler_child(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		exit(130);
	}
}

void			sh21_signals(void (*handler)(int))
{
	// signal(SIGINT, handler);
	// signal(SIGQUIT, handler);
	int sig;

	sig = 0;
	while (sig++ < SIGUSR2)
		signal(sig, handler);
	
}
