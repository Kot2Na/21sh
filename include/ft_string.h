/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 22:20:08 by mozzart           #+#    #+#             */
/*   Updated: 2020/12/12 02:33:38 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H
# ifndef LIBFT_H
#  include "libft.h"
# endif
# ifndef FT_TYPES_H
#  include "ft_types.h"
# endif

/*
** *
*/
char		*skip_spaces(char **str);
/*
** *
*/
char		*skip_word(char **str);
/*
** *
*/
char		*skip_word_spec(char **str, char *unskip_chars);
/*
** *
*/
char		*first_word(char *str);
/*
** *
*/
char		*ft_strndup(const char *s, size_t n);
/*
** *
*/
char		*get_next_word(char **str);
/*
** *
*/
size_t		ft_count_words(char *str);
/*
** *
*/
char		*get_quoted_string(char **str, char *quote);
/*
** *
*/
int			validate_oc_chars(char *str, char *o);
/*
** *
*/
char		*ft_str_replace_all(char *str, char *replace_from, char \
*replace_to, char *include);
/*
** Replace first acurence of replace_from to replace_to in str and returns
** fresh string.
** If no substing in string returng, then returns dulicate of str.
*/
char		*ft_str_replace(char *str, char *replace_from, char *replace_to, \
char *include);
/*
** *
*/
t_us		ft_is_quoted(char *str);
/*
** *
*/
char		*first_word_spec(char *str, t_uc include_first_char);
/*
** *
*/
t_uc		ft_is_quoted_char(char *str, char *c, t_us all_quotes);
/*
** *
*/
t_uc		ft_isspec(char c);
/*
** *
*/
char		**ft_strsplit_spec(char *str, char c);
/*
** *
*/
void		*ft_clear_splitter(char ***arr, long len);
/*
** *
*/
char		*ft_stranychr(char *str, char *anyc);
/*
** Separated by '|'
*/
t_uc		ft_strequ_any(char *haystack, char *needle_set);
/*
** *
*/
char		*ft_strjoin_free(char *s1, char *s2);
/*
** *
*/
t_us		ft_count_words_spec(char *str, char c);
/*
** Chek if first char in first arument is escaped by c passed char
** in third argument
** If third argument in 0, than '\' is used like escape character
*/
char		is_echar(char *str, char *begin, char c);
/*
**	Parse Open/Close characters passed in second argument
**	I.e. "[]{}()"""
*/
int			validate_brakets(char *str, char *o);
/*
**	Parse Open/Close characters passed in second argument
**	I.e. "[]{}()"""
*/
char		*get_quoted_substring(char *str, char o, char c);
char		*ft_skip_char(char **str, char c);

#endif
