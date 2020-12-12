/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 19:25:07 by mozzart           #+#    #+#             */
/*   Updated: 2020/12/12 03:04:21 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

size_t	env_len(t_env *env)
{
	size_t len;

	len = env ? 1 : 0;
	while (len && env->next)
	{
		++len;
		env = env->next;
	}
	return (len);
}

char	**env_all(t_env *env)
{
	char	**res;
	size_t	len;

	len = env->len(env);
	if (!(res = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	res[len] = NULL;
	len = 0;
	while (env)
	{
		res[len] = env->full_string;
		env = env->next;
		++len;
	}
	return (res);
}

t_uc	env_set_name(char **dst, char *ev)
{
	char *end;

	if (!dst || !ev)
		return (1);
	end = ft_strchr(ev, '=');
	if (!end || !*end)
		return (2);
	if (!(*dst = ft_strndup(ev, end - ev)))
		return (3);
	return (0);
}

t_uc	env_set_value(char **dst, char *ev)
{
	char *start;

	if (!dst || !ev)
		return (1);
	start = ft_strchr(ev, '=');
	if (!start || !*start)
		return (2);
	if (!(*dst = ft_strdup(start + 1)))
		return (3);
	return (0);
}
