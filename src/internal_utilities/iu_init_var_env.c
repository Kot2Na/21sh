/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_init_var_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:37:20 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/17 18:44:02 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

void	init_env(t_exec_lst *execlist, char **env)
{
	char *ev[2] = {"", NULL};
	// execlist->sh_environ = env_new(env, V_ENVIR);
	(void)env;
	execlist->sh_environ = env_new(ev, V_ENVIR);
}
