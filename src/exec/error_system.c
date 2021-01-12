/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelphia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 19:21:09 by mdelphia          #+#    #+#             */
/*   Updated: 2020/02/29 20:50:28 by mdelphia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int			wr_to_stderr(char *msg1, char *msg2, char *msg3)
{
	ft_putstr_fd(msg1, STDERR_FILENO);
	if (msg2)
		ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg2, STDERR_FILENO);
	if (msg3)
		ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg3, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}

void		error_system(t_exec_lst *execlist, int status)
{
	if (status == EXEC_ERROR_NUM)
		exit((execlist->sh_term_lst.exec_status = EXEC_ERROR_NUM));
}
