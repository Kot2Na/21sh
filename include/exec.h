/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:48:39 by mdelphia          #+#    #+#             */
/*   Updated: 2020/12/20 18:02:56 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include "libft.h"
# include "sh_limits.h"
# include "sh_struct.h"
# include "internal_utilities.h"
# include "input_error.h"
# include "input_parse_key.h"

/*
** exec function
*/
void			check_choice(t_exec_lst *execlist, t_pars_list *list);
int				check_run(t_exec_lst *execlist, t_pars_list **list);
int				stream_and_file(t_exec_lst *execlist, t_pars_list *list);
int				create_file(t_red_stream *stream_list);
int				redirect_stream(t_red_stream *stream_list);
int				dup_fd_and_close(int fd, int dup_fd);
int				run_ampersant(t_exec_lst *execlist, t_pars_list **list);
void			run_exec(int fd, t_pars_list *list, t_exec_lst *execlist);
void			run_pipe(t_exec_lst *execlist, t_pipe_list **pipelist,
					t_pars_list **list);
int				new_or_open_file(char *file_name, int flag_open);
t_pars_list		*free_pars_list(t_pars_list **list);
t_pipe_list		*new_pipe_list(t_exec_lst *execlist, t_pipe_list *pipelist);
void			free_pipe_list(t_pipe_list *pipelist);
int				stream_close_fd(t_red_stream *stream_list);
void			error_system(t_exec_lst *execlist, int status);
void			stream_save_std(t_red_stream *stream_list);
void			close_and_open_std(t_exec_lst *execlist,
					t_red_stream *stream_list);
int				write_this_dir(t_pars_list *list, char *name_func);
void			free_befor_exec(t_info_parser *prs);
int				exec_dup_stream(int oldfd, int newfd);
void			exec_next_list(int status, t_pars_list **list);
void			write_name_run(t_exec_lst *execlist, t_pars_list *list);
int				exec_fill_way_for_path(t_exec_lst *execlist, char *str_path,
					t_pars_list *list);
void			exec_redirect_heredoc(t_exec_lst *execlist, t_pars_list *list);
void			insert_dollar_args(t_exec_lst *execlist, t_pars_list *list);
char			*search_first_space(char *ptr);
char			*braces_dollar_realloc(t_exec_lst *execlist, char **str,
									char *ptr);
int				errors_braces(char *err_msg);
char			**pars_dollar_shift_args(char **pars_args, int i);
void			find_name_path(char *name_path, size_t *i, t_pars_list *list,
					char *name_func);
/*
** comands
*/
int				cmd_name_value(char *s, int i);
int				check_cmd(char *name_func);
int				run_cmd(t_exec_lst *execlist, t_pars_list *list);
void			exec_env(t_exec_lst *execlist, t_pars_list *list);
int				cmd_true(void);
int				cmd_false(void);
/*
** signals
*/
void			status_child(t_exec_lst *execlist, int stat_child,
					pid_t pid_child, char *path_cmd);
void			handler_child(int sig);
void			sh21_signals(void (*handler)(int));

#endif
