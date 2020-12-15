/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update_last_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 22:27:36 by mozzart           #+#    #+#             */
/*   Updated: 2020/12/15 04:00:21 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

t_uc	env_update_last_cmd(char **cmd, t_env **env)
{
	char	tmp[PATH_MAX];
	char	**val;

	tmp[0] = '_';
	tmp[1] = '=';
	val = cmd;
	while (*val && ++val)
		;
	--val;	
	if (env && *env)
	{
		if ((*env)->set(*env, "_", *val))
			if ((*env)->add(*env, "_", *val, V_ENVIR))
				return (1);
	}
	else if (!*env)
	{
		ft_strcat(tmp, *val);
		if (!(*env = env_new_var(tmp, V_ENVIR)))
			return (1);
		ft_bzero(tmp, PATH_MAX);
	}
	return (0);
}
