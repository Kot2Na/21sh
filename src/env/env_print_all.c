/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 17:15:46 by mozzart           #+#    #+#             */
/*   Updated: 2020/12/18 05:58:07 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

t_uc		env_print_all(t_env *env, t_uc scope)
{
	while (env && env->name)
	{
		if (scope == V_ALL || scope == env->scope)
			ft_printf("%s\n", env->full_string);
		env = env->next;
	}
	return (0);
}
