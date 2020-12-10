# include "sh_jobs.h"

int job_set_num(t_job *jobs)
{
    int result;

    result = 1;
    while (jobs)
    {
        if (jobs->job_num != result)
            break;
        result++;
        jobs = jobs->next;
    }
    return (result);
}

t_job   *job_create(char *line, t_pars_list *list)
{
    t_job *new_job;

    new_job = NULL;
    if (list)
    {
        new_job = (t_job *)malloc(sizeof(t_job));
        new_job->next = NULL;
        new_job->command = ft_strdup(line);
        new_job->first_process = list;
        new_job->pgid = -1;
        new_job->stdinc = 0;
        new_job->stdoutc = 1;
        new_job->stderrc = 2;
    }
    return (new_job);
}


void    job_launch(t_job **jobs, t_job *new_job)
{
    t_job *cur_job;

    new_job->job_num = job_set_num(*jobs);
    if (jobs && *jobs && new_job)
    {
        cur_job = *jobs;
        while (cur_job->next)
            cur_job = cur_job->next;
        cur_job->next = new_job;
    }
    else
        *jobs = new_job;
}

void job_destroy(t_job *jobs)
{
    t_job *next_job;

    if (jobs)
    {
        next_job = jobs;
        while (next_job)
        {
            next_job = jobs->next;
            free_pars_list(&jobs->first_process);
            // free_befor_exec(jobs->first_process);
            free(jobs->command);
            free(jobs);
            jobs = next_job;
        }
    }
}

void job_control(t_exec_lst *execlist, t_pars_list *list, t_job **jobs, char *line)
{
    t_job *cur_job;

    //create job
    cur_job = job_create(line, list);
    job_launch(jobs, cur_job);
    //do job
    check_choice(execlist, list, cur_job);
    if (*jobs)
        globs()->g_first_job = *jobs;
    //close job
}

// t_job *find_job(pid_t pgid)
// {
//     t_job       *j;

//     for (j = first_job; j; j = j->next)
//         if (j->pgid == pgid)
//             return j;
//     return NULL;
// }

int job_is_stopped(t_job *job)
{
    t_pars_list   *p;

    for (p = job->first_process; p; p = p->next)
        if (!p->completed && !p->stopped)
            return 0;
    return 1;
}

// int job_is_completed(t_job *j)
// {
//     t_process   *p;

//     for (p = j->first_process; p; p = p->next)
//     if (!p->completed)
//         return 0;
//     return 1;
// }

void print_arr(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        ft_printf("%s", arr[i]);
        i++;
        if (arr[i])
            ft_printf(" ");
    }

}

int sh42_jobs(t_job *jobs)
{
    t_pars_list *iter;
    jobs = globs()->g_first_job;

    while (jobs)
    {
        ft_printf("[%d] ", jobs->job_num);
        iter = jobs->first_process;
        while (iter)
        {
            ft_printf("\t%d\t", iter->pid);
            if (iter->completed)
                ft_printf("completed\t");
            else
                ft_printf("running\t");
            print_arr(iter->pars_args);
            //ft_printf("\tcom - %s\n", iter->pars_args[0]);
            ft_printf("\n");
            iter = iter->next;
        }
        jobs = jobs->next;
    }
    return 0;
}

void        set_status(t_job *jobs, t_pars_list *p, int status)
{
    
}

int         job_set_procces_status(t_job *job, pid_t pid, int status)
{
    t_pars_list *p_iter;
    t_job       *j_iter;

	if (pid > 0)
	{
        j_iter = globs()->g_first_job;
		while (j_iter)
		{
            p_iter = j_iter->first_process;
			while (p_iter)
			{
				if (p_iter->pid == pid)
					return (set_status());
                p_iter = p_iter->next;
			}
            j_iter = j_iter->next;
		}
//		return (!ft_dprintf(globals()->fd[2],
//				"No child process %d.\n", pid) - 1);
	}
	else if (pid == 0 || errno == ECHILD)
		return (-1);
	return (-1);
}


void        job_wait(t_job *job)
{
	int			status;
	pid_t		pid;

	status = 0;
	while (1)
	{
		if (job_is_stopped(job))
			break ;
		pid = waitpid(-job->pgid, &status, WUNTRACED | WNOHANG);
		 (pid, status, job);
	}
}