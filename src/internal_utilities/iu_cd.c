/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:37:06 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/18 06:37:19 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

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
				err = goto_path(sh21_getenv(execlist, "OLDPWD"));
			else
				err = goto_path(path);
		}
	}
	return (err);
}

int			sh21_cd(t_exec_lst *execlist, int argc, char **argv, char **env)
{
	enum e_err		err;
	char			*cwd;

	(void)(env);
	err = FAILURE;
	if (argv[0] && argc > 0)
	{
		cwd = (char[MAX_SIZE_PATH + 1]){0};
		getcwd(cwd, MAX_SIZE_PATH);
		if (argc == 1)
			err = work_cd(execlist, "");
		else if (argc > 2)
			CD_ERR(CD_TOO_MANY, EMPTY_STR);
		else
			err = work_cd(execlist, argv[1]);
		if (err == FAILURE)
			return (1);
		sh21_setenv(execlist, "OLDPWD", cwd,
			FLAG_ON);
		cwd = (char[MAX_SIZE_PATH + 1]){0};
		getcwd(cwd, MAX_SIZE_PATH);
		sh21_setenv(execlist, "PWD", cwd, FLAG_ON);
	}
	return (0);
}
