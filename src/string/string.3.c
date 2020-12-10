/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 18:59:45 by mozzart           #+#    #+#             */
/*   Updated: 2020/12/09 21:55:34 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_str_replace(char *str, char *rplc_f, char *rplc_t, char *inc)
{
	char	*res;
	char	*tmp;
	int		f;
	int		t;

	if (!str || !rplc_f || !rplc_t)
		return (NULL);
	t = ft_strlen(rplc_t);
	f = ft_strlen(rplc_f);
	if (!(tmp = ft_strstr(str, rplc_f)))
		return (ft_strdup(str));
	if (inc)
		while ((tmp = ft_strstr(tmp, rplc_f)) && *tmp)
		{
			if (!ft_strchr(inc, *tmp + 1))
				break ;
			++tmp;
		}
	if (!(res = ft_strnew(ft_strlen(str) - f + t)))
		return (NULL);
	res = ft_strncpy(res, str, tmp - str);
	res = ft_strcat(res, rplc_t);
	res = ft_strcat(res, tmp + f);
	return (res);
}

t_us	ft_is_quoted(char *str)
{
	t_us	single_q;
	t_us	double_q;

	single_q = 0;
	double_q = 0;
	while (*str)
	{
		if (*str == '\'' && *(str - 1) != '\\' && !double_q)
			single_q ^= 1;
		if (*str == '"' && *(str - 1) != '\\' && !single_q)
			double_q ^= 1;
		++str;
	}
	return (!(single_q | double_q));
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*res;

	if (!s || !(res = ft_strnew(n)))
		return (NULL);
	res = ft_strncpy(res, s, n);
	return (res);
}
