/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:37:38 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/12 03:58:19 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

int			sh21_export(t_exec_lst *execlist, const char *name)
{
	enum e_err		err;

	err = FAILURE;
	if (name && *name)
	{
		execlist->sh_environ->export(execlist->sh_environ, (char*)name);
		err = SUCCESS;
	}
	return (err);
}
