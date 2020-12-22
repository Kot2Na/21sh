#include "internal_utilities.h"

static int			write_range(char start, char stop, char *buf) 
{
	int i;

	i = 0;
	while (start < stop)
	{
		buf[i] = start;
		++start;
		++i;
	}
	return (i);
}

const char			*get_posix_options(void)
{
	char	*res;
	uint8_t	i;

	if (!(res = ft_strnew(64)))
			return (NULL);
	i = 0;
	i += write_range('0', '9' + 1, &(res[i]));
	i += write_range('A', 'Z' + 1, &(res[i]));
	i += write_range('a', 'z' + 1, &(res[i]));
	return (res);
}

