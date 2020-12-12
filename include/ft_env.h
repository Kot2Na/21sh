/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 22:20:08 by mozzart           #+#    #+#             */
/*   Updated: 2020/12/12 04:01:08 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H
# ifndef LIBFT_H
#  include "libft.h"
# endif
# ifndef FT_TYPES_H
#  include "ft_types.h"
# endif
# ifndef FT_STRING_H
#  include "ft_string.h"
# endif
# ifndef ENV_MAXLEN
#  define ENV_MAXLEN 1024
# endif

# define V_ALL 0
# define V_ENVIR 1
# define V_INTERN 2

typedef struct		s_env
{
	char			*name;
	char			*value;
	char			*full_string;
	struct s_env	*next;
	t_uc			scope;

	size_t			(*len)(struct s_env*, t_uc);
	char			**(*all)(struct s_env*);
	char			*(*get)(struct s_env*, char*);
	void			*(*destroy)(struct s_env*);
	struct s_env	*(*del)(struct s_env*, char*);
	t_uc			(*set)(struct s_env*, char*, char*);
	t_uc			(*add)(struct s_env*, char*, char*, t_uc);
	t_uc			(*export)(struct s_env*, char*);
}					t_env;

size_t				env_len(t_env *env, t_uc scope);
char				**env_all(t_env *env);
void				*env_destroy(t_env *env);
t_env				*env_new(char **environ, t_uc scope);
t_uc				env_set_name(char **dst, char *ev);
t_uc				env_set_value(char **dst, char *ev);
t_env				*env_new_var(char *ev, t_uc scope);
t_uc				env_print_all(t_env *env, t_uc scope);
t_uc				env_update_last_cmd(char *cmd, t_env **env);
char				*replace_spec(char *str, t_env *env);
t_uc				env_export(t_env *env, char *name);

#endif
