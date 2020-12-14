/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelphia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:52:25 by mdelphia          #+#    #+#             */
/*   Updated: 2020/04/07 14:28:38 by mdelphia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	write_character(char *buf, char sim)
{
	buf[0] = sim;
	buf[1] = '\0';
}

static int	check_name_cmd(char *name_func)
{
	if (!(ft_strcmp("true", name_func)) ||
		!(ft_strcmp("false", name_func)) ||
		!(ft_strcmp("cd", name_func)) ||
		!(ft_strcmp("echo", name_func)) ||
		!(ft_strcmp("pwd", name_func)) ||
		!(ft_strcmp("set", name_func)) ||
		!(ft_strcmp("unset", name_func)) ||
		!(ft_strcmp("env", name_func)) ||
		!(ft_strcmp("type", name_func)) ||
		!(ft_strcmp("exit", name_func)) ||
		!(ft_strcmp("export", name_func)))
		return (1);
	return (0);
}

int			cmd_name_value(char *s, int i)
{
	if (s[i] == '=')
		return (0);
	while (s[i] && s[i] != '=')
		i++;
	return (s[i] ? 1 : 0);
}

int			check_cmd(char *name_func)
{
	char buf[2];

	if (cmd_name_value(name_func, 0))
		return (1);
	write_character(buf, name_func[0]);
	if (!(ft_strcmp("t", buf)) || !(ft_strcmp("f", buf)) ||
		!(ft_strcmp("c", buf)) || !(ft_strcmp("e", buf)) ||
		!(ft_strcmp("p", buf)) || !(ft_strcmp("s", buf)) ||
		!(ft_strcmp("u", buf)))
		return (check_name_cmd(name_func));
	return (0);
}
