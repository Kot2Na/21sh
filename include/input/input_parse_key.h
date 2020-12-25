/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse_key.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidokin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:38:23 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/25 17:32:05 by mnidokin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_PARSE_KEY_H
# define INPUT_PARSE_KEY_H

# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>

# include "libft.h"
# include "ft_queue.h"
# include "sh_struct.h"
# include "input_macros.h"
# include "input_termcap.h"
# include "input_init.h"
# include "input_greeting.h"
# include "sh_bonus.h"
# include "history.h"

/*
**START_WORK_INPUT
*/
void			input_begin(t_exec_lst *execlist, struct s_input *inp);

/*
**KEY_PRESS_WORK
*/
ssize_t			input_read(const int fd, void *buf, const size_t nbyte);
ssize_t			input_write(int filedes, const void *buf, size_t nbyte);
t_key			input_getch(t_exec_lst *execlist, struct s_input *inp);
void			input_process_key_press(struct s_input *inp);
void			input_ctr_keys(struct s_input *inp);
t_key			input_get_key_shift_arrow(void);
t_key			input_get_key_ctr_arrow(void);
t_key			input_get_key_additional(t_byte key);
t_key			input_get_key_arrow(t_byte key);
void			input_parse_page_keys(struct s_input *inp);
void			input_parse_keys_shift_words(struct s_input *inp);
void			input_paste_to_buf(struct s_input *inp);
void			input_copy_from_buf(struct s_input *inp);
void			input_cut_from_buf(struct s_input *inp);
struct s_cursor	input_get_end_string(struct s_input *inp);

/*
**MOVE_CUROSR
*/
void			input_move_cursor(struct s_input *inp);
int				check_line_footnote_up(struct s_input *inp);
int				check_line_footnote_down(struct s_input *inp);

/*
**WORK_WINDOW
*/
void			clear_full_screen(struct s_input *inp);
void			refresh_screen(struct s_input *inp);
void			get_coor_word(struct s_input *inp, ssize_t pos);
void			input_put_new_line(struct s_input *inp);
void			input_update_rows(struct s_input *inp, struct s_win *wn);

/*
**ANOTHER
*/
void			input_history(struct s_input *inp);
int				search_double_quotes(t_queue *qu);
void			input_additional_modes(t_exec_lst *execlist,
					struct s_input *inp);
void			input_quote_mode(t_exec_lst *execlist, struct s_input *inp);
void			clean_struct_input(struct s_input *inp);
void			input_preparation(t_exec_lst *execlist, struct s_input *inp);
char			*input_heredoc(t_exec_lst *execlist, char *delimeter);

int	ft_search_backslash(char **str);

#endif
