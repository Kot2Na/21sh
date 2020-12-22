/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:37:28 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/23 07:54:58 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

int		sh21_pwd(int argc, char *argv[], char *env[])
{
	char	*pwd;
	int64_t	opts;

	(void)(argv);
	(void)(env);
	// if (argc > 1)
	// 	ft_printf("pwd: %v%s\n", STDERR_FILENO, S_TOO_MANY);
	// else
	// {
	pwd = (char[MAX_SIZE_PATH + 1]){0};
	if ((opts = ft_get_flags(argv + 1, argc - 1, (char*)POSIX_OPTIONS, FALSE)) > 0)
	{
		// Work with flags
		if (opts == (P_FLAG))
		{
			// If not contains ./|. and ../|..
			// Then write as is
			// But if $PWD < PATH_MAX
			// Then behavior is undefined by POSIX

			// Else write as with -P flag
		}
		else if (opts == P_FLAG)
		{
			// If -P flag specified
			// Than print $PWD value with resolving all simlinks and dots dot-dots
		}
		else
		{
			// If both flags specified 
			// Than work with last one
		}
		
	}
	else if (opts < 0)
		ft_printf("pwd: %v%s\n", STDERR_FILENO, S_TOO_MANY);
	else
	if (getcwd(pwd, MAX_SIZE_PATH))
	{
		ft_printf("%s\n", pwd);
		return (0);
	}
	return (1);
}
