/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 03:13:25 by ksharlen          #+#    #+#             */
/*   Updated: 2020/04/07 10:57:35 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_STRUCT_H
# define SH_STRUCT_H

# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>

# include "libft.h"
# include "gap_buf.h"
# include "sh_limits.h"

/*
** ENUMS
*/
enum						e_heredoc
{
	IS_FOUND_DELIMITER,
	IS_NOT_FOUND_DELIMITER,
	BREAK_SIGNAL
};

enum						e_greet_mode
{
	MODE_DFLT,
	MODE_QUOTE,
	MODE_DQUOTE,
	MODE_BQUOTE,
	MODE_HEREDOC
};

enum						e_key
{
	KEY_LEFT_ARROW = 1000,
	KEY_RIGHT_ARROW,
	KEY_UP_ARROW,
	KEY_DOWN_ARROW,
	KEY_HOME,
	KEY_END,
	KEY_DEL,
	KEY_PAGE_UP,
	KEY_PAGE_DOWN,
	KEY_SHIFT_L_ARROW,
	KEY_SHIFT_R_ARROW,
	KEY_SHIFT_U_ARROW,
	KEY_SHIFT_D_ARROW,
	KEY_CTR_L_ARROW,
	KEY_CTR_R_ARROW,
	KEY_CTR_U_ARROW,
	KEY_CTR_D_ARROW,
	KEY_BCKSPACE = 127,
	KEY_NEW_LINE = 13
};

/*
** INIT_STRUCT
*/
struct						s_path
{
	char					home_d[SH21_MAX_PATH];
	char					curr_d[SH21_MAX_PATH];
};

typedef struct				s_start_env
{
	char					shlvl[SH21_MAX_PATH];
	char					term[SH21_MAX_PATH];
	char					shell[SH21_MAX_PATH];
	char					pwd[SH21_MAX_PATH];
	char					old_pwd[SH21_MAX_PATH];
	char					path[SH21_MAX_PATH];
	char					home[SH21_MAX_PATH];
	char					user[SH21_MAX_PATH];
}							t_start_env;

struct						s_shell
{
	struct termios			shell_tmode;
	pid_t					shell_pgid;
	int						shell_term;
	int						shell_interac;
};

/*
** GLOBAL
*/
typedef struct				s_term_var
{
	char					*tty_name;
	int						exec_status;
	pid_t					pid_last;
	int						ret_child;
}							t_term_var;


/*
**PARSER
*/
typedef struct				s_red_stream
{
	struct s_red_stream		*next;
	struct s_red_stream		*prev;
	struct s_red_stream		*end;
	int						stream_a;
	int						stream_in;
	char					stream_name[BUFSIZ];
	int						fd_file;
	int						flag_file;
	int						flag_close;
	int						save_std;
}							t_red_stream;

typedef struct				s_pars_list
{
	t_red_stream			*stream_list;
	struct s_pars_list		*next;
	struct s_pars_list		*prev;
	pid_t					pid;
	unsigned int			f_delimiter;
	unsigned short			nbr_ampersant;
	char					*name_func;
	char					name_run_func[BUFSIZ];
	char					**pars_args;
	char					**str_status;
	char					**str_lastpid;
	char					completed;
	char					stopped;
	int						status;
	int						foreground;
}							t_pars_list;

/*
** JOBS
*/

typedef struct				s_job
{
	struct s_job			*next;
	char					*command;
	t_pars_list				*first_process;
	pid_t					pgid;
	struct termios			tmodes;
	int						job_num;
	int 					stdinc;
	int						stdoutc;
	int						stderrc;
	int						foreground;
}							t_job;

/*
** EXEC
*/

typedef struct				s_exec_lst
{
	t_term_var				sh_term_lst;
	char					**sh_environ;
	char					path_heredoc[BUFSIZ];
}							t_exec_lst;

typedef struct				s_pipe_list
{
	int						pfd[2];
	struct s_pipe_list		*next;
	struct s_pipe_list		*prev;
}							t_pipe_list;

typedef struct				s_info_parser
{
	t_pars_list				*beg;
	t_pars_list				*end;
}							t_info_parser;

/*
**HISTORY
*/
typedef struct				s_history_list
{
	char					*comand;
	struct s_history_list	*next;
	struct s_history_list	*prev;
	size_t					location;
}							t_history_list;

typedef struct				s_history
{
	t_history_list			*h_list;
	t_history_list			*beg;
	t_history_list			*end;
	size_t					size;
	int						fd;
}							t_history;

/*
**INPUT_STRUCT
*/
typedef struct				s_greet
{
	char					time[SIZE_TIME + 1];
	char					user[SIZE_NAME + 1];
	char					curr_d[SIZE_DIR + 1];
	char					mode;
	int						len;
}							t_greet;

struct						s_user_info
{
	char					user[SH21_MAX_NAME];
	char					home_d[SH21_MAX_PATH];
	pid_t					u_pid;
};

struct						s_cursor
{
	int32_t					x;
	int32_t					y;
};

struct						s_win
{
	int						cols;
	int						rows;
};

struct						s_input
{
	t_gapbuf				gap;
	char					*buf;
	char					*str_for_parse;
	struct termios			cfg_cpy;
	struct s_cursor			cr;
	struct s_cursor			save_refresh_pos;
	struct s_win			win;
	struct s_user_info		u_info;
	t_history				*hist;
	t_greet					greet;
	t_key					key;
};

typedef struct				s_init
{
	struct s_path			path;
	struct s_start_env		env;
	struct s_user_info		u_inf;
	struct s_shell			shell;
	struct s_input			inp;
	t_job					*jobs;
	t_info_parser			prs;
	t_exec_lst				execlist;
}							t_init;

#endif
