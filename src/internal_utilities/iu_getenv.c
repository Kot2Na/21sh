/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:37:15 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/12 02:49:19 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

char		*sh21_getenv(t_exec_lst *execlist, const char *name)
{
	return (execlist->sh_environ->get(execlist->sh_environ, (char*)name));
}
