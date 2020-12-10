/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 19:51:35 by mozzart           #+#    #+#             */
/*   Updated: 2020/10/04 19:54:21 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char			*ft_strjoin_free(char *s1, char *s2)
{
	char *res;

	if (!s1 && !(s1 = ft_strnew(0)))
		return (NULL);
	if (!(res = ft_strjoin(s1, s2)))
		return (NULL);
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (res);
}
