/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_init_var_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:37:20 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/12 02:49:36 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

void	init_env(t_exec_lst *execlist, char **env)
{
	execlist->sh_environ = env_new(env);
}
