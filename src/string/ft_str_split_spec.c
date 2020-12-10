/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_split_spec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 19:55:36 by mozzart           #+#    #+#             */
/*   Updated: 2020/10/04 21:22:29 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static char	*ft_split_spec_get_word(char **start, size_t len)
{
	char	*str;
	char	*res;

	if (!(str = ft_strndup(*start, len)))
		return (NULL);
	res = ft_strtrim(str);
	ft_strdel(&str);
	return (res);
}

char		**ft_strsplit_spec(char *str, char c)
{
	char	**res;
	char	*tmp;
	char	*ptr;
	t_us	i;

	if (!str || !c)
		return (NULL);
	i = ft_count_words_spec(str, c);
	if (!(res = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	tmp = str;
	i = 0;
	ptr = tmp;
	while ((tmp = ft_strchr(tmp, c)))
	{
		if ((*(tmp - 1) == '\\' || ft_is_quoted_char(str, tmp, 1)) && *(++tmp))
			continue ;
		if (!(res[i++] = ft_split_spec_get_word(&ptr, tmp - ptr)))
			return (ft_clear_splitter(&res, i));
		ptr = ft_skip_char(&tmp, c);
	}
	if (*ptr && !(res[i++] = ft_split_spec_get_word(&ptr, ft_strlen(ptr))))
		return (ft_clear_splitter(&res, i + 1));
	res[i] = NULL;
	return (res);
}
