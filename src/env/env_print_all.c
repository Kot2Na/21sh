/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 17:15:46 by mozzart           #+#    #+#             */
/*   Updated: 2020/12/12 03:04:21 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

t_uc		env_print_all(t_env *env)
{
	while (env)
	{
		ft_printf("%s\n", env->full_string);
		env = env->next;
	}
	return (0);
}
