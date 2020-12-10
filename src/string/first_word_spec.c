/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_word_spec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 18:29:12 by mozzart           #+#    #+#             */
/*   Updated: 2020/12/09 21:59:48 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char			*first_word_spec(char *str, t_uc fc)
{
	char	*res;
	size_t	len;

	len = fc;
	while (str[len] && !ft_isspec(str[len]))
		++len;
	if (!(res = ft_strndup(str, len)))
		return (NULL);
	return (res);
}
