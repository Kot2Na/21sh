/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 00:11:34 by ksharlen          #+#    #+#             */
/*   Updated: 2020/03/17 13:21:00 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <sys/types.h>
# include <unistd.h>

# include "libft.h"
# include "sh_limits.h"
# include "sh_struct.h"
# include "internal_utilities.h"

int				parser(t_exec_lst *execlist, char **str_for_parse,
					t_info_parser *prs);
void			parser_add_list(t_info_parser *prs);
char			*parser_skip_quotes(char *str, char *splitter);
char			*find_delimiter(char *str);
size_t			parser_count_args(const char *str, char *splitter);
size_t			parser_get_len_arg(char *str, char *splitter);
const char		*parser_skip_word(const char *str, char *splitter);
char			**parser_fill_args(char *start_str, char *splitter,
					size_t qty_args);
char			*parser_quote_arg(char **str, char *splitter);
char			*fill_split_flag(char *splitter, int size, unsigned int
					*flags_splt);
char			*skip_splitter(char *splitter, unsigned int *flags_splt);
int				parse_not_srvc_symb(char *c);
char			*pars_find_stream(char *str, char *splitter, t_pars_list *list);
t_red_stream	*pars_add_lst_stream(t_red_stream **stream_list);
int				find_flag_stream(char *pos_stream, t_red_stream *stream_list);
char			*put_error_parse(char *str, int fd);
int				check_valid_char_name(char sym);
void			parser_fill_point_args(t_pars_list *list);
char			*parser_skipminus(char *str);
int				parse_is_quote(char c);
char			*parse_next_quote(char *str);
char			*pars_insert_tilda(t_exec_lst *execlist, char **str);
char			*pars_stream_in_list(char *str, char *splitter,
					t_red_stream *stream_list);
char			*write_prev(char *str, char *pos_stream,
					t_red_stream *stream_list);
char			*write_next_stream(char *pos_stream, char *splitter,
					t_red_stream *stream_list);
char			*write_amper_args_after_stream(char *pos_stream, char *splitter,
					t_red_stream *stream_list);
int				put_error_flags(char *pos_stream, int sz);
char			*parser_find_ampersand(char *str, t_pars_list *list);
int				parser_get_nbr_ampersand(t_pars_list *list);
void			parser_check_ampersand(char *splitter, t_pars_list *list);
void			write_flag_and_nbr_ampersand(t_pars_list *list);
size_t			parser_get_count_args_heredoc(t_pars_list *list,
					size_t count_args);
int				parser_check_dollar(char *str, t_pars_list *list,
					char *splitter);

#endif
