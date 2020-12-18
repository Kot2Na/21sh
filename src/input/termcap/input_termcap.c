/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_termcap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 22:35:41 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/18 06:24:23 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_termcap.h"

void	input_tgetent(t_exec_lst *execlist)
{
	int		ok;
	char	*term;
	char	*err_msg;

	err_msg = "termcap for current terminal not found";
	if (!(term = sh21_getenv(execlist, "TERM")))
	{
		if ((ok = tgetent(T_BUFFER, "xterm")) < 1)
			if ((ok = tgetent(T_BUFFER, "screen")) < 1)
				if ((ok = tgetent(T_BUFFER, "linux")) < 1)
					if ((ok = tgetent(T_BUFFER, "vt100")) < 1)
						if ((ok = tgetent(T_BUFFER, "ansi")) < 1)
							input_error_ext(err_msg);
	}
	else if ((ok = tgetent(T_BUFFER, term)) < 1)
		input_error_ext(err_msg);
}

char	*input_tgetstr(char *cb)
{
	char	*str;

	str = NULL;
	if (cb)
	{
		str = tgetstr(cb, T_BUFFER);
		ft_chk_null_ptr(str, E_TGETSTR);
	}
	else
		input_error_ext("input_tgetstr: empty cb");
	return (str);
}

char	*input_tgoto(char *cb, int one, int two)
{
	char	*str;

	str = NULL;
	if (cb)
	{
		str = tgoto(cb, one, two);
		ft_chk_null_ptr(str, E_TGOTO);
	}
	else
		input_error_ext("input_tgoto: empty cb");
	return (str);
}

void	input_tputs(const char *str, int affcnt, int (*putc)(int))
{
	int	ret_tputs;

	if (str)
	{
		ret_tputs = tputs(str, affcnt, putc);
		ft_chk_sys_error(ret_tputs, E_TPUTS);
	}
	else
		input_error_ext("input_tputs: empty str");
}

int		input_tgetnum(char *str)
{
	int		val;

	val = -1;
	if (str)
	{
		val = tgetnum(str);
		if (val == -1)
			input_error_ext("input_tgetnum: val = -1");
	}
	else
		input_error_ext("input_tgetnum: empty str");
	return (val);
}
