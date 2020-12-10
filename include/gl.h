/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 13:53:09 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/12/10 02:15:21 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_H
# define GL_H

# include "sh_struct.h"

int				g_exit_status;
int				g_sig_status;
int				g_pid;
t_init			*g_init;

typedef struct  s_globs
{
	pid_t       g_shell_pgid;
	int         g_shell_term;
	int         g_shell_interac;
	t_job		*g_first_job;
}               t_globs;

#endif
