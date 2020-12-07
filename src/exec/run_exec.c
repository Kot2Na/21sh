/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:42:49 by mdelphia          #+#    #+#             */
/*   Updated: 2020/12/07 14:44:59 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	error_run_exec(int *exec_status, t_pars_list *list)
{
	ft_putstr_fd(STR_ERR_SHELL, STDERR_FILENO);
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putstr_fd(list->name_func, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	*exec_status = 127;
	exit(127);
}

static int	write_name_environ(char *str, char *buf)
{
	size_t i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		buf[i] = str[i];
		++i;
	}
	buf[i] = '\0';
	return (1);
}

char		*find_path_param(char **sh_environ)
{
	size_t	i;
	short	shift_to_start_path;
	char	buf[BUFSIZ];

	i = 0;
	shift_to_start_path = 5;
	while (sh_environ && sh_environ[i])
	{
		if (sh_environ[i][0] == 'P' &&
			write_name_environ(sh_environ[i], buf) &&
			!ft_strcmp(buf, "PATH"))
			return (sh_environ[i] + shift_to_start_path);
		++i;
	}
	return (NULL);
}

void		write_name_run(t_exec_lst *execlist, t_pars_list *list)
{
	if (write_this_dir(list, list->name_func))
		return ;
	if (exec_fill_way_for_path(execlist,
		find_path_param(execlist->sh_environ), list))
		return ;
	error_run_exec(&execlist->sh_term_lst.exec_status, list);
}

void		run_exec(int fd, t_pars_list *list, t_exec_lst *execlist)
{
	if (list->f_delimiter & V_DOLLAR)
		insert_dollar_args(execlist, list);
	if (fd > -1)
		dup_fd_and_close(fd, STDIN_FILENO);
	if (execve(list->name_run_func, list->pars_args, execlist->sh_environ))
		error_run_exec(&execlist->sh_term_lst.exec_status, list);
}
