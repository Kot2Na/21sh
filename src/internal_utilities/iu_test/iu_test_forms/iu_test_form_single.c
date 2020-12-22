#include "internal_utilities.h"

/*
** -b FILE
** FILE exists and is block special
*/

int	iu_test_b(char **cmd)
{
	if (access(cmd[2], F_OK))
		return (EXIT_FAILURE);
	else if (ft_file_objtype(cmd[2]) == 'b')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** -c FILE
** FILE exists and is character special
*/

int	iu_test_c(char **cmd)
{
	if (access(cmd[2], F_OK))
		return (EXIT_FAILURE);
	if (ft_file_objtype(cmd[2]) == 'c')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** -d FILE
** FILE exists and is a directory
*/

int	iu_test_d(char **cmd)
{
	if (access(cmd[2], F_OK))
		return (EXIT_FAILURE);
	if (ft_file_objtype(cmd[2]) == 'd')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** -e FILE
** FILE exists
*/

int	iu_test_e(char **cmd)
{
	return (access(cmd[2], F_OK));
}

/*
** -f FILE
** FILE exists and is a regular file
*/

int	iu_test_f(char **cmd)
{
	char file_type;

	if (access(cmd[2], F_OK))
		return (EXIT_FAILURE);
	file_type = ft_file_objtype(cmd[2]);
	if (file_type == 'x' || file_type == '-')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** -g FILE
** FILE exists and is set-group-ID
*/

int	iu_test_g(char **cmd)
{
	struct stat	file;

	if (lstat(cmd[2], &file))
		return (EXIT_FAILURE);
	if (S_ISGID & file.st_mode)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** -G FILE
** FILE exists and is owned by the effective group ID
*/

int	iu_test_cap_g(char **cmd)
{
	gid_t	cur_gid;
	struct stat	file;

	if (lstat(cmd[2], &file))
		return (EXIT_FAILURE);
	cur_gid = getgid();
	if (cur_gid == file.st_gid)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** -h FILE
** -L FILE
** FILE exists and is a symbolic link (same as -L)
*/

int	iu_test_h_and_cap_l(char **cmd)
{
	if (access(cmd[2], F_OK))
		return (EXIT_FAILURE);
	if (ft_file_objtype(cmd[2]) == 'l')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** -k FILE
** FILE exists and has its sticky bit set
*/

int	iu_test_k(char **cmd)
{
	struct stat	file;

	if (lstat(cmd[2], &file))
		return (EXIT_FAILURE);
	if (file.st_mode & S_ISVTX)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** -O FILE
** FILE exists and is owned by the effective user ID
*/

int	iu_test_cap_o(char **cmd)
{
	struct stat	file;
	uid_t		cur_uid;

	if (lstat(cmd[2], &file))
		return (EXIT_FAILURE);
	cur_uid = getuid();
	if (cur_uid == file.st_uid)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** -p FILE
** FILE exists and is a named pipe
*/

int	iu_test_p(char **cmd)
{
	if (access(cmd[2], F_OK))
		return (EXIT_FAILURE);
	if (ft_file_objtype(cmd[2]) == 'p')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** -r FILE
** FILE exists and read permission is granted
*/

int	iu_test_r(char **cmd)
{
	if (access(cmd[2], R_OK))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** -s FILE
** FILE exists and has a size greater than zero
*/

int	iu_test_s(char **cmd)
{
	struct stat	file;

	if (lstat(cmd[2], &file))
		return (EXIT_FAILURE);
	if (file.st_size > 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** -S FILE
** FILE exists and is a socket
*/

int	iu_test_cap_s(char **cmd)
{
	if (access(cmd[2], F_OK))
		return (EXIT_FAILURE);
	if (ft_file_objtype(cmd[2]) == 's')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** -t FD
** file descriptor FD is opened on a terminal
*/

int	iu_test_t(char **cmd)
{
	int	res;

	if ((res = isatty(ft_atoi(cmd[2]))) == 0)
		return (EXIT_FAILURE);
	if (res == 1)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** -u FILE
** FILE exists and its set-user-ID bit is set
*/

int	iu_test_u(char **cmd)
{
	struct stat file;

	if (lstat(cmd[2], &file))
		return (EXIT_FAILURE);
	if (file.st_mode & S_ISUID)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** -w FILE
** FILE exists and write permission is granted
*/

int	iu_test_w(char **cmd)
{
	if (access(cmd[2], W_OK))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** -x FILE
** FILE exists and execute (or search) permission is granted
*/

int	iu_test_x(char **cmd)
{
	if (access(cmd[2], X_OK))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** -n STRING
** the length of STRING is nonzero
*/

int	iu_test_n(char **cmd)
{
	if (ft_strlen(cmd[2]) > 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** -z STRING
** the length of STRING is zero
*/

int	iu_test_z(char **cmd)
{
	if (ft_strlen(cmd[2]) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

