/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:37:33 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/12 03:44:50 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

int				sh21_setenv(t_exec_lst *execlist, const char *name,
					const char *value, const int replace)
{
	enum e_err		err;

	err = FAILURE;
	(void)replace;
	if (name && value && *name)
	{
		if (!execlist->sh_environ->set(execlist->sh_environ, (char*)name,
										(char*)value) ||
			!execlist->sh_environ->add(execlist->sh_environ, (char*)name,
										(char*)value, V_ENVIR))
			err = SUCCESS;
	}
	return (err);
}
