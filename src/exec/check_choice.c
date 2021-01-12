/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_choice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelphia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:41:27 by mdelphia          #+#    #+#             */
/*   Updated: 2020/04/09 16:13:09 by mdelphia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void		alias_replacement(t_pars_list *list)
{
	int		i;
	char	*tmp;

	while (list)
	{
		i = -1;
		while (list->pars_args[++i])
		{
			tmp = get_alias_value(list->pars_args[i],
				ft_strlen(list->pars_args[i]));
			if (tmp != NULL)
			{
				free(list->pars_args[i]);
				list->pars_args[i] = ft_strdup(tmp);
			}
		}
		list = list->next;
	}
}

void		check_choice(t_exec_lst *execlist, t_pars_list *list)
{
	int status;

	if (ft_strcmp(list->name_func, "alias") &&
		ft_strcmp(list->name_func, "unalias"))
		alias_replacement(list);
	while (list)
	{
		if (list->f_delimiter & F_AMPERSANT)
			status = run_ampersant(execlist, &list);
		else
			status = check_run(execlist, &list);
		exec_next_list(status, &list);
	}
}
