/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 17:27:05 by ksharlen          #+#    #+#             */
/*   Updated: 2020/02/16 19:58:22 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "libft.h"
# include "time.h"
# include "sh_struct.h"

# define PTH_21SH_HIST ".sh_history"

t_history			*history_init(void);
char				*history_get_bottom_cmd(t_history *hist);
char				*history_get_top_cmd(t_history *hist);
t_history			*history_add_new_elem(t_history *hist, char *str);
t_history			*history_fill_history(t_history *hist, char *str);
void				history_del(t_history *hist);
char				*ft_strrchrback(const char *s, int c);

#endif
