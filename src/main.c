/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:55:32 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/09 00:40:44 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	sh21_finish(char **sh_environ)
{
	ft_strdel_split(sh_environ);
	free(sh_environ);
}

int			main(int argc, char **argv, char **env)
{
	t_init			init;

	(void)(argc);
	(void)(argv);
	(void)(env);
	sh21_init(&init, env, &init.execlist);
	g_init = &init;
	while (1)
	{
		input_begin(&init.execlist, &init.inp);
		if ((!init.inp.str_for_parse && init.inp.key == ('d' & 0x1f)))
			break ;
		else if (init.inp.str_for_parse &&
		!parser(&init.execlist, &(init.inp.str_for_parse), &init.prs))
		{
			job_control(&init.execlist, init.prs.beg, &init.jobs, init.inp.str_for_parse);
			//init.jobs.command = ft_strdup(init.inp.str_for_parse);
			//check_choice(&init.execlist, init.prs.beg, &init.jobs);
		}
		init.prs.beg = NULL;
		init.prs.end = NULL;
		//free_befor_exec(&init.prs);
	}
	job_destroy(init.jobs);
	input_finish(&init.inp);
	sh21_finish(init.execlist.sh_environ);
	return (0);
}
