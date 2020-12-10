/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_spec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 21:24:36 by mozzart           #+#    #+#             */
/*   Updated: 2020/10/04 21:26:10 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*replace_vars(char *str, t_env *env)
{
	char	*res;
	char	*tmp;
	char	*ename;
	char	*enval;

	tmp = ft_strdup(str);
	res = tmp;
	ft_strdel(&str);
	while ((tmp = ft_strchr(tmp, '$')))
	{
		if (ft_is_quoted_char(res, tmp, 0) || (res < tmp && *(tmp - 1) == '\\'))
		{
			tmp = tmp + 1;
			continue;
		}
		ename = first_word_spec(tmp, 1);
		if (!(enval = env->get(env, ename + 1)))
			enval = "";
		tmp = ft_str_replace(res, ename, enval, NULL);
		ft_strdel(&ename);
		ft_strdel(&res);
		res = tmp;
	}
	return (res);
}

static char		*replace_tilda(char *str, t_env *env)
{
	char	*res;
	char	*tmp;
	char	*ename;
	char	*enval;
	char	*inc;

	inc = "/ \t";
	tmp = ft_strdup(str);
	res = tmp;
	ft_strdel(&str);
	while ((tmp = ft_strchr(tmp, '~')))
	{
		if (ft_is_quoted_char(res, tmp, 1) || (res < tmp && *(tmp - 1) == '\\'))
		{
			tmp = tmp + 1;
			continue;
		}
		ename = "~";
		if (!(enval = env->get(env, "HOME")))
			enval = "";
		tmp = ft_str_replace(res, ename, enval, inc);
		ft_strdel(&res);
		res = tmp;
	}
	return (res);
}

static char		*replace_tabs(char *str)
{
	char	*res;
	char	*tmp;

	tmp = ft_strdup(str);
	res = tmp;
	ft_strdel(&str);
	while (*tmp && (tmp = ft_strchr(tmp, '\t')))
	{
		if (ft_is_quoted_char(res, tmp, 1) || (res < tmp && *(tmp - 1) == '\\'))
		{
			tmp = tmp + 1;
			continue;
		}
		tmp = ft_str_replace(res, "\t", " ", NULL);
		ft_strdel(&res);
		res = tmp;
	}
	return (res);
}

char			*replace_spec(char *str, t_env *env)
{
	str = replace_vars(str, env);
	str = replace_tilda(str, env);
	str = replace_tabs(str);
	return (str);
}
