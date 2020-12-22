#include "internal_utilities.h"

int64_t	ft_get_flags(char *const *argv, int argc, char *flags, int8_t with_args)
{
	uint64_t	res;
	char		*param;
	char		*f;

	res = 0;
	while (argc-- && !ft_strequ(*argv, "--"))
	{
		param = *argv;
		if (param[0] == '-')
		{
			++param;
			while(*param)
			{
				if (!(f = ft_strchr(flags, *param)))
					return (-1);
				res |= 1 << (f - flags);
				++param;	
			}
		}
		else if (with_args == FALSE)
			return (-1);
		++argv;
	}
	
	return (res);
}

