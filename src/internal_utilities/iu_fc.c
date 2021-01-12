/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:38:24 by vdaemoni          #+#    #+#             */
/*   Updated: 2021/01/27 13:38:32 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

int		iu_fc(t_exec_lst *execlist, t_pars_list *list)
{
	int		sh_hist;
	char	c;
	int		n;
	
	n = 0;
	sh_hist = open(g_path, O_CREAT | O_RDWR | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (sh_hist < 1)
		return (1);
	while (read(sh_hist, &c, 1))
	{
		ft_putchar(c);
		if (c == '\n')
			n++;
	}
	ft_putchar('\n');
	close(sh_hist);
	return (222);
	(void)list;
	(void)execlist;
}
