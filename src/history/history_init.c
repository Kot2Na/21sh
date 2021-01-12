/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:01:56 by ksharlen          #+#    #+#             */
/*   Updated: 2020/03/15 19:39:52 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

char				*ft_strrchrback(const char *s, int c)
{
	const char *p_str;

	if (s)
	{
		p_str = s;
		while (*p_str)
		{
			if (*p_str == c)
				return ((char *)p_str + 1);
			p_str++;
		}
		return ((char *)s);
	}
	return (NULL);
}

static t_history	*fill_sh_story(t_history *hist, char *line)
{
	char			*tmp;

	hist->beg->comand = ft_strdup(line);
	ft_strdel(&line);
	hist->size += 1;
	while (get_next_line(hist->fd, &line, FLAG_OFF) == 1)
	{
		tmp = line;
		hist = history_add_new_elem(hist, tmp);
		free(line);
		hist->size += 1;
	}
	get_next_line(hist->fd, &line, FLAG_ON);
	return (hist);
}

static t_history	*alloc_args(t_history *h, t_history_list *hl)
{
	h->beg = hl;
	h->end = hl;
	hl->comand = NULL;
	hl->prev = NULL;
	hl->next = NULL;
	hl->location = 1;
	h->h_list = hl;
	h->size = 0;
	history_add_new_elem(h, NULL);
	return (h);
}

void				init_path_for_sh_history(void)
{
	g_path = (char[MAX_SIZE_PATH + 1]){0};
	getcwd(g_path, MAX_SIZE_PATH);
	ft_strcat(g_path, "/");
	ft_strcat(g_path, PTH_21SH_HIST);
	ft_putendl(g_path);
}

t_history			*history_init(t_exec_lst *execlist)
{
	char			*line;
	t_history		*history;
	t_history_list	*h_list;

	init_path_for_sh_history();
	history = (t_history *)ft_memalloc(sizeof(t_history));
	ft_chk_null_ptr(history, E_MALLOC);
	h_list = (t_history_list *)ft_memalloc(sizeof(t_history_list));
	ft_chk_null_ptr(h_list, E_MALLOC);
	history->fd = open(PTH_21SH_HIST, O_CREAT | O_RDWR | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	ft_putnbr(history->fd);
	ft_putendl("");
	ft_chk_sys_error(history->fd, E_OPEN);
	history = alloc_args(history, h_list);
	if (!(get_next_line(history->fd, &line, FLAG_OFF)))
	{
		get_next_line(history->fd, &line, FLAG_ON);
		return (history);
	}
	else
		return (fill_sh_story(history, line));
	(void)execlist;
}
