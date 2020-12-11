/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:16:22 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/12 02:54:07 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

static void		env_init(t_cmd_env *env)
{
	env->cmd = NULL;
	env->opt = 0;
}

static int		fill_env_opt(char *opts, t_cmd_env *env)
{
	size_t	i;

	i = 0;
	if (opts[i] == '-')
		while (opts[++i])
		{
			if (opts[i] == 'P')
				env->opt |= F_P;
			else if (opts[i] == 'S')
				env->opt |= F_S;
			else if (opts[i] == 'i')
				env->opt |= F_I;
			else if (opts[i] == 'u')
				env->opt |= F_U;
			else
				return (1);
		}
	return (0);
}

static int		sh_env_getopt(int argc, char **opts, t_cmd_env *env)
{
	int		i;
	int		status;

	i = 1;
	status = 0;
	if (argc > 1)
		while (opts[i] && !status)
			status = fill_env_opt(opts[i++], env);
	return (status);
}

static int		get_opt(int argc, char **opts, t_cmd_env *env)
{
	enum e_err		err;

	err = SUCCESS;
	if (sh_env_getopt(argc, opts, env))
	{
		ft_printf("%v%s\n	   %s\n", STDERR_FILENO, USG, USG_1);
		return (FAILURE);
	}
	return (err);
}

int				sh21_env(t_exec_lst *execlist, int argc,
					char **argv)
{
	t_cmd_env		m_env;
	enum e_err		err;

	err = FAILURE;
	env_init(&m_env);
	err = get_opt(argc, argv, &m_env);
	if (err == SUCCESS)
	{
		++argv;
		work_opt(execlist, argv, &m_env);
	}
	return (err);
}
