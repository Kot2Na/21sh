/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 21:43:33 by mozzart           #+#    #+#             */
/*   Updated: 2020/10/03 19:56:28 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t	ft_count_words(char *str)
{
	size_t c;

	c = 0;
	while (*str)
	{
		// if (skip_spaces(&str) && skip_word(&str) && *str)
		if (get_next_word(&str))
			++c;
	}
	return (c);
}

/*
** Chek if first char in first arument is escaped by c passed char
** in third argument
** If third argument in 0, than '\' is used like escape character
*/
char	is_echar(char *str, char *begin, char c)
{
	if (!c)
		c = 0x5c;
	if (str - begin && *(str - 1) == c)
		return (1);
	return (0);
}

/*
**	Parse Open/Close characters passed in second argument
**	I.e. "[]{}()"""
*/
int		validate_brakets(char *str, char *o)
{
	char	brkts[256];
	char	last_brkt;
	int		i;
	char	*f;
	char	*str_begin;


	ft_bzero(brkts, 256);
	i = 0;
	str_begin = str;
	while (*str)
	{
		if ((f = ft_strchr(o, *str)) && !is_echar(str, str_begin, 0))
		{
			brkts[i] = *str;
			// last_brkt = *str < '[' ? *str + 1 : *str + 2;
			last_brkt = *(f + 1);
			++i;
		}
		else if (i > 0 && *str == last_brkt && !is_echar(str, str_begin, 0))
		{
			--i;
			brkts[i] = 0;
			// last_brkt = brkts[i - 1] < '[' ? brkts[i - 1] + 1 : brkts[i - 1] + 2;
			last_brkt = *(ft_strchr(o, brkts[i - 1]) + 1);
		}
		++str;
	}
	return (i == 0);
}

/*
**	Parse Open/Close characters passed in second argument
**	I.e. "[]{}()"""
*/
// int		validate_quottes(char *str)
// {
// 	char	*str_begin;


// 	// ft_bzero(brkts, 256);
// 	// i = 0;
// 	str_begin = str;
// 	while (*str)
// 	{
// 		if ((f = ft_strchr(o, *str)) && !is_echar(str, str_begin, 0))
// 		{
// 			// brkts[i] = *str;
// 			// last_brkt = *str < '[' ? *str + 1 : *str + 2;
// 			last_brkt = *(f + 1);
// 			++i;
// 		}
// 		else if (i > 0 && *str == last_brkt && !is_echar(str, str_begin, 0))
// 		{
// 			--i;
// 			brkts[i] = 0;
// 			// last_brkt = brkts[i - 1] < '[' ? brkts[i - 1] + 1 : brkts[i - 1] + 2;
// 			last_brkt = *(ft_strchr(o, brkts[i - 1]) + 1);
// 		}
// 		++str;
// 	}
// 	return (i == 0);
// }

/*
**	Parse Open/Close characters passed in second argument
**	I.e. "[]{}()"""
*/
char	*get_quoted_substring(char *str, char o, char c)
{
	char	*start;
	char	*str_begin;
	char	*res;

	str_begin = str;
	start = NULL;
	while (*str)
	{
		if (!start && *str == o && !is_echar(str, str_begin, 0))
			start = str + 1;
		else if (start && *str == c && !is_echar(str, str_begin, 0))
			break;
		++str;
	}
	if (!*str || !(res = ft_strndup(start + 1, (str - 1) - (start + 1))))
		return (NULL);

	return (res);
}

char	*get_quoted_string(char **str, char *quote)
{
	char	*res;

	// if (!validate_oc_chars(*str, quote))
	// 	return (NULL);
	if (!(res = get_quoted_substring(*str, *quote, *(quote + 1))))
		return (NULL);
	*str += ft_strlen(res + 2);
	return (res);
}