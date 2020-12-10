/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_quoted_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 21:07:57 by mozzart           #+#    #+#             */
/*   Updated: 2020/09/25 21:08:12 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

t_uc			ft_is_quoted_char(char *str, char *c, t_us all_quotes)
{
	t_us double_q;
	t_us single_q;

	double_q = 0;
	single_q = 0;
	while (str < c)
	{
		if (*str == '\'' && !double_q && *(str - 1) != '\\')
			single_q ^= 1;
		if (*str == '"' && !single_q && *(str - 1) != '\\' && all_quotes)
			double_q ^= 1;
		++str;
	}
	return ((single_q | double_q));
}
