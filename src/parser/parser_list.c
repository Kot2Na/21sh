/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 19:49:04 by ksharlen          #+#    #+#             */
/*   Updated: 2020/02/22 20:06:12 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_pars_list	*new_elem(void)
{
	t_pars_list	*new;

	new = (t_pars_list *)ft_memalloc(sizeof(t_pars_list));
	ft_chk_null_ptr(new, E_MALLOC);
	new->stream_list = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->pid = 0;
	new->status = 0;
	new->f_delimiter = 0;
	new->nbr_ampersant = 0;
	new->foreground = 1;
	new->completed = 0;
	new->stopped = 0;
	new->name_func = NULL;
	ft_bzero(new->name_run_func, BUFSIZ);
	new->pars_args = NULL;
	new->str_status = NULL;
	new->str_lastpid = NULL;
	return (new);
}

void				parser_add_list(t_info_parser *prs)
{
	t_pars_list	*new;

	if (prs)
	{
		new = new_elem();
		if (prs->beg)
		{
			prs->end->next = new;
			new->prev = prs->end;
			prs->end = new;
		}
		else
		{
			prs->beg = new;
			prs->end = new;
		}
	}
}
