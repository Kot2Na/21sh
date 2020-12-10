/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ampersant.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelphia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:42:36 by mdelphia          #+#    #+#             */
/*   Updated: 2020/03/12 21:04:21 by mdelphia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	put_nbr_ampersant(char *str_nbr_ampersant, pid_t pid)
{
	ft_putstr("\n[");
	ft_putstr(str_nbr_ampersant);
	ft_putstr("]\t");
	ft_putstr(ft_itoa(pid));
	ft_putchar('\n');
}

static void	put_name_func(t_pars_list *buf_list, int check_nbr_ampersand)
{
	while (buf_list->nbr_ampersant == check_nbr_ampersand)
	{
		if (!buf_list->status)
			ft_putstr(buf_list->name_func);
		else
		{
			ft_putstr("\n\t\t\texit ");
			ft_putnbr(buf_list->status);
			ft_putchar('\t');
			ft_putstr(buf_list->name_func);
		}
		ft_putchar('\n');
		buf_list = buf_list->next;
		if (buf_list->nbr_ampersant == check_nbr_ampersand)
			ft_putstr(" | ");
	}
	ft_putchar('\n');
}

static void	put_end_ampersant(t_pars_list *buf_list, char *str_nbr_ampersant)
{
	ft_putchar('[');
	ft_putstr(str_nbr_ampersant);
	ft_putstr("] done\t");
	put_name_func(buf_list, buf_list->nbr_ampersant);
}

int			run_ampersant(t_exec_lst *execlist, t_pars_list **list, t_job *jobs)
{
	pid_t		pid;
	char		str_nbr_ampersant[BUFSIZ];
	t_pars_list	*buf_list;

	buf_list = *list;
	if ((pid = fork()) < 0)
		error_system(execlist, EXEC_ERROR_NUM);
	if (!pid)
	{
		if (!(pid = fork()))
		{
			execlist->sh_term_lst.pid_last = pid;
			ft_strcat(str_nbr_ampersant, ft_itoa((*list)->nbr_ampersant));
			put_nbr_ampersant(str_nbr_ampersant, pid);
			check_run(execlist, list, jobs);
			waitpid(pid, 0, WUNTRACED);
			put_end_ampersant(buf_list, str_nbr_ampersant);
			exit(0);
		}
		exit(0);
	}
	waitpid(pid, &(*list)->status, WUNTRACED);
	execlist->sh_term_lst.exec_status = 0;
	error_system(execlist, (*list)->status);
	return (0);
}
