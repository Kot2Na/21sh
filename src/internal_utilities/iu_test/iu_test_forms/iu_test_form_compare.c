#include "internal_utilities.h"

/*
** STRING1 = STRING2
** the strings are equal
*/

int	iu_test_equality(char **cmd)
{
	if (!ft_strcmp(cmd[1], cmd[3]))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** STRING1 != STRING2
** the strings are not equal
*/

int	iu_test_not_equality(char **cmd)
{
	if (ft_strcmp(cmd[1], cmd[3]))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** INTEGER1 -eq INTEGER2
** INTEGER1 is equal to INTEGER2
*/

int	iu_test_eq(char **cmd)
{
	if (ft_atoi(cmd[1]) == ft_atoi(cmd[3]))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** INTEGER1 -ge INTEGER2
** INTEGER1 is greater than or equal to INTEGER2
*/

int	iu_test_ge(char **cmd)
{
	if (ft_atoi(cmd[1]) >= ft_atoi(cmd[3]))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** INTEGER1 -gt INTEGER2
** INTEGER1 is greater than INTEGER2
*/

int	iu_test_gt(char **cmd)
{
	if (ft_atoi(cmd[1]) > ft_atoi(cmd[3]))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** INTEGER1 -lt INTEGER2
** INTEGER1 is less than INTEGER2
*/

int	iu_test_lt(char **cmd)
{
	if (ft_atoi(cmd[1]) < ft_atoi(cmd[3]))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** INTEGER1 -ne INTEGER2
** INTEGER1 is not equal to INTEGER2
*/

int	iu_test_ne(char **cmd)
{
	if (ft_atoi(cmd[1]) == ft_atoi(cmd[3]))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** FILE1 -ef FILE2
** FILE1 and FILE2 have the same device and inode numbers
*/

int	iu_test_ef(char **cmd)
{
	struct stat file1;
	struct stat file2;

	if (lstat(cmd[1], &file1) && lstat(cmd[3], &file2))
		return (EXIT_FAILURE);
	if ((file1.st_ino == file2.st_ino) && (file1.st_dev == file2.st_dev))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** FILE1 -nt FILE2
** FILE1 is newer (modification date) than FILE2
*/

int	iu_test_nt(char **cmd)
{
	struct stat file1;
	struct stat file2;

	if (lstat(cmd[1], &file1) && lstat(cmd[3], &file2))
		return (EXIT_FAILURE);
	if (file1.st_mtime > file2.st_mtime)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/*
** FILE1 -ot FILE2
** FILE1 is older than FILE2
*/

int	iu_test_ot(char **cmd)
{
	struct stat file1;
	struct stat file2;

	if (lstat(cmd[1], &file1) && lstat(cmd[3], &file2))
		return (EXIT_FAILURE);
	if (file1.st_mtime < file2.st_mtime)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
