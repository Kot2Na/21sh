/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:35:51 by vdaemoni          #+#    #+#             */
/*   Updated: 2021/01/13 19:35:55 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

void	free_alias_elem(t_aliases *elem)
{
	free(elem->name);
	free(elem->value);
	free(elem);
}

int		free_all_aliases(void)
{
	t_aliases *tmp;

	tmp = g_aliases;
	while (tmp != NULL)
	{
		g_aliases = tmp->next;
		free_alias_elem(tmp);
		tmp = g_aliases;
	}
	g_aliases = NULL;
	return (0);
}

int		iu_unalias(t_exec_lst *execlist, t_pars_list *list)
{
	t_aliases	*tmp;
	t_aliases	*del;
	int			i;
	int			status;

	status = 0;
	i = 0;
	if (!list->pars_args[1])
		return (wr_to_stderr("unalias", "not enough arguments", NULL));
	if (!ft_strcmp(list->pars_args[1], "-a"))
	{
		if (list->pars_args[2])
			return (wr_to_stderr("unalias", "-a", "too many arguments"));
		return (free_all_aliases());
	}
	while (list->pars_args[++i])
	{
		tmp = g_aliases;
		if (tmp && !ft_strcmp(tmp->name, list->pars_args[i]))
		{
			g_aliases = tmp->next;
			free_alias_elem(tmp);
		}
		else if (get_alias_value(list->pars_args[i],
			ft_strlen(list->pars_args[i])) != NULL)
		{
			del = tmp->next;
			while (del != NULL && ft_strcmp(del->name, list->pars_args[i]))
			{
				del = del->next;
				tmp = tmp->next;
			}
			tmp->next = del->next;
			free_alias_elem(del);
		}
		else
			status = wr_to_stderr("unalias", "no such hash table element",
				list->pars_args[i]);
	}
	return (status);
	(void)execlist;
}
