/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_greeting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidokin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 02:55:39 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/22 14:09:43 by mnidokin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_greeting.h"

static int		input_dflt_greeting(t_greet *greet)
{
	int		ret_num_sym;

	ret_num_sym = 0;
	ft_putstr(COLOR_TIME);
	ret_num_sym += ft_printf("[%s]", greet->time);
	ft_putchar(' ');
	ft_putstr(COLOR_USER);
	ret_num_sym += ft_printf("%s", greet->user);
	ft_putchar(' ');
	ft_putstr(COLOR_DIR);
	ret_num_sym += ft_printf("(%s)", greet->curr_d);
	ft_putchar(' ');
	ft_putstr(COLOR_YELLOW);
	ret_num_sym += ft_printf("$>");
	ft_putchar(' ');
	ft_putstr(COLOR_DFLT);
	return (ret_num_sym);
}

int				input_additional_greet(t_greet *greet, const char *print_greet)
{
	int		len_greet;

	(void)(greet);
	len_greet = ft_printf("%s", print_greet);
	return (len_greet);
}

void			input_greeting(t_greet *greet)
{
	if (greet->mode == MODE_DFLT)
		greet->len = input_dflt_greeting(greet);
	else if (greet->mode == MODE_QUOTE || greet->mode == '\'')
		greet->len = input_additional_greet(greet, QUOTE);
	else if (greet->mode == MODE_DQUOTE || greet->mode == '\"')
		greet->len = input_additional_greet(greet, DQUOTE);
	else if (greet->mode == MODE_BQUOTE || greet->mode == '`')
		greet->len = input_additional_greet(greet, BQUOTE);
	else if (greet->mode == MODE_HEREDOC)
		greet->len = input_additional_greet(greet, HEREDOC);
}
