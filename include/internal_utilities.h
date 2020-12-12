/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_utilities.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 15:20:33 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/12 04:06:54 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_UTILITIES_H
# define INTERNAL_UTILITIES_H

# include <sys/types.h>
# include <limits.h>
# include <sys/stat.h>
# include <unistd.h>
# include <pwd.h>
# include <dirent.h>

# include "libft.h"
# include "sh_struct.h"
# include "exec.h"
# include "gl.h"

/*
**ERRORS
*/
# define S_NO_SUCH 		"no such file or directory:"
# define S_TOO_MANY 	"too many arguments"

/*
**ENV
*/
# define NO_SUCH 		"no such file or directory"
# define USG			"usage: env [-iv] [-P utilpath] [-S string] [-u name]"
# define USG_1			"[name=value ...] [utility [argument ...]]"
# define F_P			1
# define F_I			2
# define F_U 			4
# define F_S 			8

/*
**ECHO
*/
# define ECHO_OPT "n"

/*
**CD
*/
# define CD_TOO_MANY		S_TOO_MANY
# define CD_ERR				cd_error
# define EMPTY_STR 			""
# define N_TOO_LONG 		"File name too long"
# define NOT_DIR			"Not a directory:"
# define PERM				"Permission denied:"

# define MAX_UNAME		256
# define MAX_SIZE_PATH	256

enum			e_find
{
	NOT_FOUND = -1,
	FOUND_INTERNAL_CMD,
	FOUND_SHELL_DIR,
	FOUND_PATH_ENV,
	FOUND,
	FOUND_EXIT,
};

typedef struct s_argv	t_argv;

struct					s_nameval
{
	char	*name;
	char	*value;
};

typedef struct			s_cmd_env
{
	t_opts		opt;
	char		*path_exec;
	char		*cmd;
	char		**cmd_argv;
}						t_cmd_env;

void					init_env(t_exec_lst *execlist, char **env);
/*
**UTILITIES
*/
int						sh21_pwd(int argc, char **argv, char **env);
int						sh21_setenv(t_exec_lst *execlist, const char *name,
							const char *value, const int replace);
char					*sh21_getenv(t_exec_lst *execlist, const char *name);
int						sh21_unsetenv(t_exec_lst *execlist, const char *name);
int						sh21_export(t_exec_lst *execlist, const char *name);
int						sh21_echo(int argc, char **argv, char **env);
int						sh21_cd(t_exec_lst *execlist, int argc, char **argv,
							char **env);
int						sh21_env(t_exec_lst *execlist, int argc, char **argv);
int						ft_name_value(t_exec_lst *execlist, t_pars_list *list);
void					work_home_dir(const char *old_path, char *new_path);
void					work_opt(t_exec_lst *execlist, char *const *p_argv,
							t_cmd_env *env);
int						exit_with_code(t_pars_list *list);
int						iu_type(t_exec_lst *execlist, t_pars_list *list);

/*
**WORK_FLAGS
*/
char *const				*u_flag(t_exec_lst *execlist, char *const argv[]);
char					**s_flag(const char *str);
char *const				*change_value_name(t_exec_lst *execlist,
							char *const argv[], t_uc scope);
struct s_nameval		split_name_val(const char *nameval);
char					**split_s_key(const char *str);
void					cd_error(const char *error, const char *filename);

#endif
