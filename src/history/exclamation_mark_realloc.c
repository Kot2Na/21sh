/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation_mark_realloc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:08:18 by vdaemoni          #+#    #+#             */
/*   Updated: 2021/01/27 14:08:19 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

char	*realloc_with_exclamation_mark(char *s, t_history *hist)
{
	char	*tmp;
	size_t	i;

	i = -1;
	tmp = s;
	while (s[++i])
	{
		if (s[i] == '!' && s[i + 1] && s[i + 1] == '!')
		{
			tmp = ft_strnew(ft_strlen(s) + ft_strlen(hist->end->prev->comand));
			free(s);
			break ;
		}
	}
	return (tmp);
	(void)hist;
}
