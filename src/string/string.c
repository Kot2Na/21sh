/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 20:51:52 by mozzart           #+#    #+#             */
/*   Updated: 2020/12/09 21:55:42 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*skip_spaces(char **str)
{
	if (!str || !*str)
		return (NULL);
	while (**str && (**str == ' ' || **str == '\t'))
		++(*str);
	return (*str);
}

char	*skip_word(char **str)
{
	if (!str || !*str)
		return (NULL);
	while (**str && **str != ' ' && **str != '\t')
		++*str;
	return (*str);
}

char	*skip_word_spec(char **str, char *skip)
{
	if (!str || !*str)
		return (NULL);
	while (**str && !ft_strchr(skip, **str))
		++*str;
	return (*str);
}

char	*get_next_word(char **str)
{
	if (!str || !*str)
		return (NULL);
	if (**str == ' ' || **str == '\t')
		skip_spaces(str);
	skip_word(str);
	if (**str == ' ' || **str == '\t')
		skip_spaces(str);
	return (*str);
}

char	*first_word(char *str)
{
	char	*res;
	size_t	len;

	if (!str || !(skip_spaces(&str)))
		return (NULL);
	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '\t')
		++len;
	res = ft_strndup(str, len);
	return (res);
}
