/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_new_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 23:08:43 by mozzart           #+#    #+#             */
/*   Updated: 2020/12/17 18:28:08 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

static t_env	*del(t_env *env, char *n)
{
	t_env *tmp;

	if (!env || !n)
		return (env);
	if (ft_strequ(env->name, n))
	{
		tmp = env->next;
		env->next = NULL;
		env = env->destroy(env);
		return (tmp);
	}
	env->next = env->del(env->next, n);
	return (env);
}

static t_uc		add(t_env *env, char *n, char *v, t_uc scope)
{
	char	tmp[ENV_MAXLEN];
	t_uc	res;

	res = 1;
	if (!env || !n)
		return (res);
	if (env->next)
		return (env->add(env->next, n, v, scope));
	ft_strcpy(tmp, n);
	if (v)
	{
		ft_strcat(tmp, "=");
		ft_strcat(tmp, v);
	}
	if ((env->next = env_new_var(tmp, scope)))
		res = 0;
	ft_bzero(tmp, ENV_MAXLEN);
	return (res);
}

static t_uc		set(t_env *env, char *n, char *v)
{
	char	*t;
	size_t	l;

	if (!env)
		return (1);
	if (!ft_strequ(env->name, n))
		return (env->set(env->next, n, v));
	if ((l = ft_strlen(v)) == ft_strlen(env->value))
		ft_strcpy(env->value, v);
	else
	{
		ft_strdel(&(env->value));
		if (!(env->value = ft_strdup(v)))
			return (1);
	}
	ft_strdel(&(env->full_string));
	if (!(t = ft_strjoin(n, "=")))
		return (1);
	if (!(env->full_string = ft_strjoin(t, v)))
		return (1);
	ft_strdel(&t);
	return (0);
}

static char		*get(t_env *env, char *n)
{
	if (!env)
		return (NULL);
	if (!ft_strequ(env->name, n))
		return (env->get(env->next, n));
	return (env->value);
}

t_env			*env_new_var(char *ev, t_uc scope)
{
	t_env	*env;

	// if (!ev || !*ev)
	// 	return (NULL);
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	if (ev && *ev)
	{
		env->full_string = ft_strdup(ev);
		env_set_name(&(env->name), ev);
		env_set_value(&(env->value), ev);
	}
	env->scope = scope;
	env->next = NULL;
	env->set = set;
	env->get = get;
	env->add = add;
	env->del = del;
	env->all = env_all;
	env->len = env_len;
	env->export = env_export;
	env->destroy = env_destroy;
	return (env);
}
