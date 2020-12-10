/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_spliter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 19:54:02 by mozzart           #+#    #+#             */
/*   Updated: 2020/10/04 19:54:15 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void		*ft_clear_splitter(char ***a, long len)
{
	char **arr;

	if (!a || !*a)
		return (NULL);
	arr = *a;
	if (len >= 0)
	{
		while (len--)
			if (arr[len])
				ft_strdel(&arr[len]);
	}
	else
	{
		len = 0;
		while (arr[len])
		{
			ft_strdel(&arr[len]);
			++len;
		}
	}
	free(*a);
	*a = NULL;
	return (NULL);
}
