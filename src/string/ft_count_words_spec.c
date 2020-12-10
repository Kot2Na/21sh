/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words_spec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 21:21:37 by mozzart           #+#    #+#             */
/*   Updated: 2020/10/04 21:21:54 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

t_us		ft_count_words_spec(char *str, char c)
{
	t_us	counter;

	counter = *str ? 1 : 0;
	while ((str = ft_strchr(str, c)) && !ft_is_quoted_char(str, str, 1))
	{
		if (*(str - 1) != '\\')
		{
			++counter;
			while (*str == c)
				++str;
		}
		++str;
	}
	str && *str ? ++counter : 0;
	return (counter);
}
