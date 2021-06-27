# include "sh_jobs.h"

void    put_job_in_background(t_job *job, int cont)
{
	struct timespec	tw;
	struct timespec	tr;

	tw = (struct timespec){0, 22000000};
	if (cont)
		if (kill(-job->pgid, SIGCONT) < 0)
			perror("kill (SIGCONT)");
	nanosleep(&tw, &tr);
}

void    put_job_in_foreground(t_job *job, int cont)
{
	tcsetpgrp(globs()->g_shell_term, job->pgid);
	if (cont)
	{
		if (kill(-job->pgid, SIGCONT) < 0)
            perror("kill (SIGCONT)");
	}
	wait_for_job(job);
	tcsetpgrp(globs() , globs()->g_shell_pgid;
	tcsetattr(0, TCSANOW, &g_saved_attr);
}
