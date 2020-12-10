/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_find_ampersand.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelphia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 21:25:16 by mdelphia          #+#    #+#             */
/*   Updated: 2020/03/21 21:25:16 by mdelphia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		parser_check_ampersand(char *splitter, t_pars_list *list)
{
	if (*splitter != '&' || (*splitter == '&' && *(splitter + 1) == '&'))
		return ;
	if (*splitter == '&' && (*splitter == ' ' || *splitter == '\n'))
	{
		list->foreground = 0;
		return;
	}
	write_flag_and_nbr_ampersand(list);
}
