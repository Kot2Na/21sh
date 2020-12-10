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

void		check_choice(t_exec_lst *execlist, t_pars_list *list, t_job *jobs)
{
	int status;

	while (list)
	{
		// Я не знаю, зачем этот код нужен..
		//if (list->f_delimiter & F_AMPERSANT)
		//	status = run_ampersant(execlist, &list, jobs);
		//else
			status = check_run(execlist, &list, jobs);
		exec_next_list(status, &list);
	}
}
