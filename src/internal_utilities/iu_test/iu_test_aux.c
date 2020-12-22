#include "internal_utilities.h"

char	ft_file_objtype(char *str)
{
	struct stat file;
	int			st_mode;

	lstat(str, &file);
	st_mode = file.st_mode;
	if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISCHR(st_mode))
		return ('c');
	else if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISFIFO(st_mode))
		return ('p');
	else if (S_ISSOCK(st_mode))
		return ('s');
	else if (S_ISREG(st_mode))
		return (st_mode & S_IXUSR ? 'x' : '-');
	else
		return ('?');
}
