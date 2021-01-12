/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:28:50 by vdaemoni          #+#    #+#             */
/*   Updated: 2021/01/12 16:28:52 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

int			eq_pos(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	only_alias(void)
{
	t_aliases *tmp;

	tmp = g_aliases;
	while (tmp != NULL)
	{
		ft_printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

int			name_cmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if ((*(unsigned char *)s1) != (*(unsigned char *)s2)
				|| *s1 == '\0' || *s2 == '\0')
			return ((*(unsigned char *)s1) - (*(unsigned char *)s2));
		s1++;
		s2++;
	}
	if (*s1 == '\0' && (*s2 == '\0' || *s2 == '='))
		return (0);
	return (1);
}

char		*get_alias_value(char *name, size_t n)
{
	t_aliases	*tmp;

	tmp = g_aliases;
	while (tmp != NULL)
	{
		if (!name_cmp(tmp->name, name, n + 1))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void		add_to_g_alias(char *name, char *value, size_t n, size_t v)
{
	t_aliases	*tmp;

	tmp = g_aliases;
	if (get_alias_value(name, eq_pos(name, '=') - 1) != NULL)
	{
		while (tmp != NULL && ft_strncmp(name, tmp->name, n))
			tmp = tmp->next;
		free(tmp->value);
		tmp->value = ft_strdup(&value[v]);
	}
	else
	{
		while (tmp != NULL)
			tmp = tmp->next;
		tmp = (t_aliases *)malloc(sizeof(t_aliases));
		tmp->name = ft_strndup(name, n);
		tmp->value = ft_strdup(&value[v]);
		tmp->next = g_aliases;
		g_aliases = tmp;
	}
}

static int	alias_parser(char *s)
{
	int i;

	if (get_alias_value(s, ft_strlen(s)) != NULL)
		return (2);
	i = eq_pos(s, '=');
	if (!s[i])
		return (1);
	return (0);
}

int			iu_alias(t_exec_lst *execlist, t_pars_list *list)
{
	int		i;
	int		status;
	size_t	n;
	char	*tmp;

	i = 0;
	status = 0;
	if (!list->pars_args[1])
		return (only_alias());
	while (list->pars_args[++i])
	{
		tmp = list->pars_args[i];
		if (alias_parser(tmp) == 2)
			ft_printf("%s=%s\n", tmp, get_alias_value(tmp, ft_strlen(tmp)));
		else if (alias_parser(tmp) == 1)
			status = 1;
		else
		{
			n = 0;
			while (tmp[n] != '=')
				n++;
			add_to_g_alias(tmp, tmp, n, n + 1);
		}
	}
	return (status);
	(void)execlist;
}
