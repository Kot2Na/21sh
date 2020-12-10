/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stranychr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 20:43:47 by tvanessa          #+#    #+#             */
/*   Updated: 2020/10/03 20:44:07 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_stranychr(char *str, char *anyc)
{
	char *c;
	char *tmp;

	c = NULL;
	tmp = NULL;
	while (*anyc)
	{
		if ((tmp = ft_strchr(str, *anyc)))
		{
			if (!c || c > tmp)
				c = tmp;
		}
		++anyc;
	}
	return (c);
}
