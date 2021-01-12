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

# include "sh.h"

typedef struct			s_aliases
{
	char				*name;
	char				*value;
	struct s_aliases	*next;
}						t_aliases;

int						g_exit_status;
int						g_sig_status;
int						g_pid;
t_init					*g_init;
t_aliases				*g_aliases;

#endif
