#include "sh_jobs.h"


void recover_shell_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
    signal(SIGKILL, SIG_DFL);
    //signal(SIGCHLD, SIG_DFL);
}

void remove_shell_signals(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    //signal(SIGCHLD, SIG_IGN);

}

void    init_shell(void)
{
    globs()->g_shell_term = STDIN_FILENO;
    globs()->g_shell_interac = isatty(globs()->g_shell_term);
    if (globs()->g_shell_interac)
    {
        while (tcgetpgrp(globs()->g_shell_term) != (globs()->g_shell_pgid = getpgrp()))
        {
            kill(- globs()->g_shell_pgid, SIGTTIN);
        }
        remove_shell_signals();
        globs()->g_shell_pgid = getpid();
        if (setpgid(globs()->g_shell_pgid, globs()->g_shell_pgid) < 0)
        {
            perror ("Can't put the shell in its own process group");
            exit (1);
        }
        tcsetpgrp(0, globs()->g_shell_pgid);
    }
}