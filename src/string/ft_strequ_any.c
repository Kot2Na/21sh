/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ_any.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 19:18:54 by mozzart           #+#    #+#             */
/*   Updated: 2020/10/04 19:23:31 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

t_uc	ft_strequ_any(char *haystack, char *needle_set)
{
	char	**arr;
	size_t	i;

	i = 0;
	if (!haystack || !*haystack)
		return (0);
	if (!needle_set || !*needle_set)
		return (1);
	if (!(arr = ft_strsplit(needle_set, '|')))
		return (2);
	while (*(arr + i))
	{
		if (ft_strequ(haystack, *(arr + i)))
		{
			ft_clear_splitter(&arr, -1);
			return (1);
		}
		++i;
	}
	ft_clear_splitter(&arr, -1);
	return (0);
}
