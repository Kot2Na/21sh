/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:28:46 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/18 06:21:50 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_init.h"

static void	set_shlvl(t_exec_lst *execlist)
{
	char	*p_shlvl;
	char	*ret_itoa;
	int		num_shlvl;

	p_shlvl = getenv("SHLVL");
	if (p_shlvl)
	{
		num_shlvl = ft_atoi(p_shlvl);
		++num_shlvl;
		ret_itoa = ft_itoa(num_shlvl);
		ft_chk_null_ptr(ret_itoa, E_MALLOC);
		sh21_setenv(execlist, "SHLVL", ret_itoa, FLAG_ON);
		ft_strdel(&ret_itoa);
	}
	else
	{
		sh21_setenv(execlist, "SHLVL", "1", FLAG_ON);
	}
}

void		sh21_init_start_env(t_exec_lst *execlist,
					const struct s_user_info *user)
{
	char	*buf;

	buf = (char[SH21_MAX_PATH]){0};
	sh21_setenv(execlist, "USER", user->user, FLAG_ON);
	sh21_setenv(execlist, "SHELL", P_N, FLAG_ON);
	set_shlvl(execlist);
	getcwd(buf, SH21_MAX_PATH);
	sh21_setenv(execlist, "PWD", buf, FLAG_ON);
	sh21_setenv(execlist, "HOME", user->home_d, FLAG_ON);
}
