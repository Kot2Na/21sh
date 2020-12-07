/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:36:53 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/07 14:47:18 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

#define COLOR_DEFAULT	"\e[0m"

static void	execute_question(int v)
{
	v == 1 ? ft_printf("%d ", g_exit_status) : ft_printf("%d", g_exit_status);
}

static int	found_question(const char *s)
{
	if (ft_strequ(s, "$?"))
		return (1);
	if (ft_strequ(s, "${?}"))
		return (1);
	return (0);
}

static void	work_echo(char *const argv[])
{
	while (*argv && *(argv + 1))
	{
		if (found_question(*argv))
		{
			execute_question(1);
			++argv;
			break ;
		}
		ft_printf("%s ", *argv);
		++argv;
	}
	if (*argv && found_question(*argv))
	{
		execute_question(0);
		argv++;
	}
	ft_printf("%s", *argv ? *argv : "");
}

int			sh21_echo(int argc, char **argv, char **env)
{
	unsigned char	flag;

	(void)(env);
	flag = FLAG_OFF;
	if (argc == 1)
		ft_putendl("");
	else
	{
		++argv;
		if (*argv && !ft_strcmp(*argv, "-n"))
		{
			++argv;
			flag = FLAG_ON;
		}
		work_echo(argv);
		if (argc > 2)
			flag == FLAG_ON ? ft_printf("\e[30;47m%%%s\n", COLOR_DEFAULT)
				: ft_printf("\n");
		else if (argc == 2 && flag == FLAG_OFF)
			ft_printf("\n");
	}
	return (0);
}
