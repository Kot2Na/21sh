/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:37:06 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/23 07:24:03 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

#define CD_P_FLAG 2

static int	check_file(const char *path)
{
	struct stat		st;
	enum e_err		err;

	err = FAILURE;
	stat(path, &st);
	if (st.st_mode & S_IFDIR)
		err = SUCCESS;
	else
		CD_ERR(NOT_DIR, path);
	return (err);
}

static int	goto_path(const char *path)
{
	int				ret_chdir;
	enum e_err		err;

	err = FAILURE;
	ret_chdir = access(path, F_OK);
	if (ret_chdir == FAILURE)
		CD_ERR(S_NO_SUCH, path);
	else
	{
		if (check_file(path) == FAILURE)
			return (FAILURE);
		ret_chdir = access(path, X_OK);
		if (ret_chdir == FAILURE)
			CD_ERR(PERM, path);
		else
		{
			ret_chdir = chdir(path);
			if (ret_chdir == FAILURE)
				CD_ERR(NOT_DIR, path);
			else
				err = SUCCESS;
		}
	}
	return (err);
}

static int	valid_path(const char *path)
{
	size_t		len_filename;
	size_t		len_full_path;
	const char	*p_path;

	p_path = path;
	len_full_path = 0;
	while (p_path && *p_path)
	{
		if (*p_path == '/')
			++p_path;
		len_filename = ft_strnlen(p_path, '/');
		if (len_filename > MAX_UNAME)
		{
			CD_ERR(N_TOO_LONG, EMPTY_STR);
			return (FAILURE);
		}
		len_full_path += len_filename;
		p_path += len_filename;
	}
	if (len_full_path > MAX_SIZE_PATH)
	{
		CD_ERR(N_TOO_LONG, EMPTY_STR);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	work_cd(t_exec_lst *execlist, const char *path)
{
	enum e_err		err;
	char			*buf_path;

	err = FAILURE;
	if (path)
	{
		err = valid_path(path);
		if (err != FAILURE)
		{
			if (*path == '~' || !(*path) || !ft_strcmp(path, "--"))
			{
				buf_path = (char[MAX_SIZE_PATH + 1]){0};
				work_home_dir(path, buf_path);
				err = goto_path(buf_path);
			}
			else if (!ft_strcmp(path, "-"))
			{
				err = goto_path(sh21_getenv(execlist, "OLDPWD"));
				ft_printf("%s\n", sh21_getenv(execlist, "OLDPWD"));
			}
			else
				err = goto_path(path);
		}
	}
	return (err);
}

int			get_not_resolved_cwd(char *buf, size_t len, char *pwd, char *path)
{
	char *new_path;
	char *new_pwd;

	if (*path == '/')
		ft_strcpy(buf, path);
	else if (!ft_strncmp(".." , path, 2) && (*(path + 2) == '/' || !(*(path + 2))) && *pwd)
	{
		new_pwd = ft_strrchr(pwd, '/');
		new_path = (path + 2);
		if (*new_path == '/')
			++new_path;
		// if (new_pwd != pwd)
			ft_bzero(new_pwd, ft_strlen(new_pwd));
		// else
			// ft_bzero(new_pwd + 1, ft_strlen(new_pwd + 1));
		get_not_resolved_cwd(buf, len, pwd, new_path);
	}
	else if (path[0] == '.' && (path[1] == '/' || !(path[1])))
		get_not_resolved_cwd(buf, len, pwd, path + 2);
	else
	{
		ft_strcpy(buf, pwd);
		if (*path)
			ft_strcat(buf, "/");
		if (*pwd)
			ft_strcat(buf, path);
	}
	
	return (SUCCESS);
}

int			sh21_cd(t_exec_lst *execlist, int argc, char **argv, char **env)
{
	enum e_err		err;
	char			*cwd;
	char			*path;
	int64_t			opts;

	(void)(env);
	err = FAILURE;
	if (argv[0] && argc > 0)
	{
		path = argv[argc - 1];
		if (argc == 1)
			err = work_cd(execlist, "");
		else if (argc > 2 && argv[1][0] != '-')
			CD_ERR(CD_TOO_MANY, EMPTY_STR);
		else
			err = work_cd(execlist, path);
		if (err == SUCCESS)
		{
			opts = ft_get_flags(argv, argc, "PL", TRUE);
			cwd = (char[MAX_SIZE_PATH + 1]){0};
			sh21_setenv(execlist, "OLDPWD", sh21_getenv(execlist, "PWD"),
			FLAG_ON);
			if (opts & CD_P_FLAG)
				getcwd(cwd, MAX_SIZE_PATH);
			else
				get_not_resolved_cwd(cwd, MAX_SIZE_PATH, sh21_getenv(execlist, "PWD"), path);
			sh21_setenv(execlist, "PWD", cwd, FLAG_ON);
		}
		else
			return (1);
	}
	return (0);
}
