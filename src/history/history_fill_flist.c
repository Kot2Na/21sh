/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_fill_flist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 22:55:57 by ksharlen          #+#    #+#             */
/*   Updated: 2020/03/18 14:09:03 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

t_history	*history_add_new_elem(t_history *hist, char *str)
{
	t_history_list *tmp;

	tmp = (t_history_list *)ft_memalloc(sizeof(t_history_list));
	ft_chk_null_ptr(tmp, E_MALLOC);
	hist->h_list = hist->end;
	hist->h_list->next = tmp;
	tmp->prev = hist->h_list;
	tmp->location = hist->h_list->location + 1;
	if (str)
		hist->h_list->comand = ft_strdup(ft_strrchrback(str, ':'));
	tmp->comand = NULL;
	hist->h_list = tmp;
	hist->end = tmp;
	hist->h_list->next = NULL;
	return (hist);
}

static int	full_spaces_command(char *s)
{
	int i;

	i = -1;
	while (s[++i] == 32)
		NULL ;
	if (s[i])
		return (0);
	return (1);
}

t_history	*history_fill_history(t_history *hist, char *str)
{
	if (str)
	{
		if (full_spaces_command(str) == 0)
		{
			if (!hist->end->prev->comand || ft_strcmp(hist->end->prev->comand, str))
			{
				hist = history_add_new_elem(hist, str);
				ft_printf("%v%zd:", hist->fd, time(NULL));
				ft_printf("%v%s\n", hist->fd, hist->h_list->prev->comand);
			}
		}
	}
	hist->h_list = hist->end;
	return (hist);
}
