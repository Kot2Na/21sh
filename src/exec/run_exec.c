/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:42:49 by mdelphia          #+#    #+#             */
/*   Updated: 2020/12/12 02:48:01 by tvanessa         ###   ########.fr       */
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

void		write_name_run(t_exec_lst *execlist, t_pars_list *list)
{
	t_env *env;

	env = execlist->sh_environ;
	if (write_this_dir(list, list->name_func))
		return ;
	if (exec_fill_way_for_path(execlist,
		env->get(env, "PATH"), list))
		return ;
	error_run_exec(&execlist->sh_term_lst.exec_status, list);
}

void		run_exec(int fd, t_pars_list *list, t_exec_lst *execlist)
{
	char	**env;

	env = execlist->sh_environ->all(execlist->sh_environ);
	if (list->f_delimiter & V_DOLLAR)
		insert_dollar_args(execlist, list);
	if (fd > -1)
		dup_fd_and_close(fd, STDIN_FILENO);
	if (execve(list->name_run_func, list->pars_args, env))
		error_run_exec(&execlist->sh_term_lst.exec_status, list);
	free(env);
	env = NULL;
}
