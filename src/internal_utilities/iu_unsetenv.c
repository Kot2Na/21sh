/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:37:38 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/12 02:52:45 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

int			sh21_unsetenv(t_exec_lst *execlist, const char *name)
{
	enum e_err		err;

	err = FAILURE;
	if (name && *name)
	{
		execlist->sh_environ->del(execlist->sh_environ, (char*)name);
		err = SUCCESS;
	}
	return (err);
}
