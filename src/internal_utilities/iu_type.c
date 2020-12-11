/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:41:27 by mdelphia          #+#    #+#             */
/*   Updated: 2020/12/12 02:06:51 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

static int	check_type_args(t_pars_list *list, char *str_path, char *args)
{
	size_t i;

	i = 0;
	if (str_path)
		while (str_path[i])
		{
			find_name_path(str_path, &i, list, args);
			if (!access(list->name_run_func, 0))
				if (!access(list->name_run_func, 1))
					return (1);
		}
	return (0);
}

static int	valid_cmd(t_exec_lst *execlist, t_pars_list *list, char *args)
{
	t_env	*env;

	env = execlist->sh_environ;
	if (write_this_dir(list, args))
		return (1);
	else if (check_type_args(list, env->get(env, "PATH"), args))
		return (1);
	return (0);
}

static void	put_res_type_args(t_exec_lst *execlist, t_pars_list *list,
				char *args, int *status)
{
	if (check_cmd(args))
		ft_printf("%s is a shell builtin\n", args);
	else if (valid_cmd(execlist, list, args))
		ft_printf("%s is %s\n", args, list->name_run_func);
	else if (*args == '-')
	{
		ft_printf("type: bad option: %s\n", args);
		*status = ERROR_RUN_CMD;
	}
	else
	{
		ft_printf("%s not found\n", args);
		*status = ERROR_RUN_CMD;
	}
}

int			iu_type(t_exec_lst *execlist, t_pars_list *list)
{
	int		status;
	char	**args;

	status = GOOD_RUN_CMD;
	args = list->pars_args;
	while (*(++args))
		put_res_type_args(execlist, list, *args, &status);
	return (status);
}
