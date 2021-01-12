/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 03:10:16 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/18 06:19:42 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_init.h"

static void	init_user(struct s_user_info *curr_user)
{
	struct passwd	*pw_user;
	char			*user_name;
	char			*home_dir;

	if (curr_user)
	{
		ft_bzero(curr_user->user, SH21_MAX_NAME);
		ft_bzero(curr_user->home_d, SH21_MAX_PATH);
		curr_user->u_pid = getuid();
		user_name = getenv("USER");
		home_dir = getenv("HOME");
		if (!user_name || !home_dir)
		{
			pw_user = getpwuid(curr_user->u_pid);
			ft_strcpy(curr_user->user, pw_user->pw_name);
			ft_strcpy(curr_user->home_d, pw_user->pw_dir);
		}
		else
		{
			ft_strcpy(curr_user->user, user_name);
			ft_strcpy(curr_user->home_d, home_dir);
		}
	}
}

static void	init_path(struct s_path *path, char *home_dir)
{
	ft_bzero(path->home_d, SH21_MAX_PATH);
	ft_bzero(path->curr_d, SH21_MAX_PATH);
	getcwd(path->curr_d, SH21_MAX_PATH);
	ft_strcpy(path->home_d, home_dir);
}

static void	fill_path_heredoc(char *path_heredoc)
{
	char	this_dir[BUFSIZ];

	getcwd(this_dir, BUFSIZ);
	ft_strcpy(path_heredoc, this_dir);
	ft_strcat(path_heredoc, NAME_HEREDOC);
}

static void	init_globals(void)
{
	g_exit_status = 0;
	g_sig_status = 0;
	g_aliases = NULL;
}

void		sh21_init(t_init *init, char **env, t_exec_lst *execlist)
{
	(void)(env);
	if (init)
	{
		init_globals();
		init_user(&init->u_inf);
		init_env(execlist, env);
		sh21_init_start_env(&init->execlist, &init->u_inf);
		init_path(&init->path, init->u_inf.home_d);
		init->inp.hist = history_init(execlist);
		init->inp.u_info = init->u_inf;
		init->inp.buf = NULL;
		input_init(&init->inp);
		init->prs.beg = NULL;
		init->prs.end = NULL;
		init->execlist.sh_term_lst.tty_name = ttyname(STDOUT_FILENO);
		fill_path_heredoc(init->execlist.path_heredoc);
	}
}
