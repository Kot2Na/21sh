/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 19:25:07 by mozzart           #+#    #+#             */
/*   Updated: 2020/12/18 06:15:57 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

size_t	env_len(t_env *env, t_uc scope)
{
	size_t len;

	len = 0;
	while (env)
	{
		if (scope == V_ALL || env->scope == scope)
			++len;
		env = env->next;
	}
	return (len);
}

char	**env_all(t_env *env)
{
	char	**res;
	size_t	len;

	len = env->len(env, V_ENVIR);
	if (!(res = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	res[len] = NULL;
	len = 0;
	while (env)
	{
		if (env->scope == V_ENVIR && (res[len] = env->full_string))
			++len;
		env = env->next;
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
		end = ev + ft_strlen(ev);
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

t_uc	env_export(t_env *env, char *name)
{
	if (!env || !name)
		return (0);
	if (!ft_strequ(env->name, name))
		return (env->export(env->next, name));
	return ((env->scope = V_ENVIR));
}
