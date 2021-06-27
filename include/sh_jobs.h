#ifndef SH_JOBS_H
# define SH_JOBS_H

# include <signal.h>

# include "gl.h"
# include "libft.h"
# include "sh_limits.h"
# include "internal_utilities.h"

int     sh42_jobs(t_job *jobs);
void    job_control(t_exec_lst *execlist, t_pars_list *list, t_job **jobs, char *str);
void    job_destroy(t_job *jobs);
void    recover_shell_signals(void);
void    put_job_in_background(t_job *job, int cont);
void    put_job_in_foreground(t_job *job, int cont);

#endif